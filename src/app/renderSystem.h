/*
* Copyright 2011-2018 Branimir Karadzic. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "common.h"
#include "camera.h"
#include "cameraData.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "preRenderSystem.h"
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mc
{
	inline glm::tmat4x4<float, glm::defaultp> perspective(float fovy, float aspect, float zNear, float zFar)
	{
		glm::tmat4x4<float, glm::defaultp> mtx;
		//Dunno why this works this way...
#	if GLM_COORDINATE_SYSTEM != GLM_LEFT_HANDED
		bx::mtxProjLh(&mtx[0][0], glm::degrees(fovy), aspect, zNear, zFar, bgfx::getCaps()->homogeneousDepth);
#	else
		bx::mtxProjRh(&mtx[0][0], glm::degrees(fovy), aspect, zNear, zFar, bgfx::getCaps()->homogeneousDepth);
#	endif
		return mtx;
	}

	//struct PosColorVertex
	//{
	//	float m_x;
	//	float m_y;
	//	float m_z;
	//	uint32_t m_abgr;

	//	static void init()
	//	{
	//		ms_decl
	//			.begin()
	//			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
	//			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
	//			.end();
	//	};

	//	static bgfx::VertexDecl ms_decl;
	//};


	//static PosColorVertex s_cubeVertices[] =
	//{
	//	{ -1.0f,  1.0f,  1.0f, 0xff000000 },
	//{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	//{ -1.0f, -1.0f,  1.0f, 0xff00ff00 },
	//{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	//{ -1.0f,  1.0f, -1.0f, 0xffff0000 },
	//{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	//{ -1.0f, -1.0f, -1.0f, 0xffffff00 },
	//{ 1.0f, -1.0f, -1.0f, 0xffffffff },
	//};

	//static const uint16_t s_cubeTriList[] =
	//{
	//	0, 1, 2, // 0
	//	1, 3, 2,
	//	4, 6, 5, // 2
	//	5, 6, 7,
	//	0, 2, 4, // 4
	//	4, 2, 6,
	//	1, 5, 3, // 6
	//	5, 7, 3,
	//	0, 4, 1, // 8
	//	4, 5, 1,
	//	2, 3, 6, // 10
	//	6, 3, 7,
	//};

	//static const uint16_t s_cubeTriStrip[] =
	//{
	//	0, 1, 2,
	//	3,
	//	7,
	//	1,
	//	5,
	//	0,
	//	4,
	//	2,
	//	6,
	//	7,
	//	4,
	//	5,
	//};

	class ExampleCubes : public entry::AppI
	{
	public:
		ExampleCubes(const char* _name, const char* _description)
			: entry::AppI(_name, _description)
		{
		}

		void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
		{

			Args args(_argc, _argv);

			m_width = _width;
			m_height = _height;
			m_debug = BGFX_DEBUG_NONE;
			m_reset = BGFX_RESET_VSYNC;

			bgfx::init(args.m_type, args.m_pciId);
			bgfx::reset(m_width, m_height, m_reset);

			// Enable debug text.
			bgfx::setDebug(m_debug);

			// Set view 0 clear state.
			bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
			);

			// Create vertex stream declaration.
			PosColorVertex::init();



			// Create program from shaders.
			m_program = loadProgram("vs_cubes", "fs_cubes");

			m_timeOffset = bx::getHPCounter();


			imguiCreate();

			cameraCreate();

			const float initialPos[3] = { 5.0f, 3.0, 0.0f };
			cameraSetPosition(initialPos);
			cameraSetVerticalAngle(bx::kPi / 8.0f);
			cameraSetHorizontalAngle(-bx::kPi / 3.0f);

		}

		virtual int shutdown() override
		{
			cameraDestroy();
			imguiDestroy();

			// Cleanup.
			bgfx::destroy(m_program);

			// Shutdown bgfx.
			bgfx::shutdown();

			return 0;
		}

		bool update() override
		{
			if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
			{
				int64_t now = bx::getHPCounter();
				static int64_t last = now;
				const int64_t frameTime = now - last;
				last = now;
				const double freq = double(bx::getHPFrequency());
				const float deltaTime = float(frameTime / freq);

				imguiBeginFrame(m_mouseState.m_mx
					, m_mouseState.m_my
					, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
					, m_mouseState.m_mz
					, uint16_t(m_width)
					, uint16_t(m_height)
				);

				showExampleDialog(this);

				imguiEndFrame();

				float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));

				updateCamera(deltaTime);

				auto proj = perspective(mCameraData.fov, mCameraData.ratio, mCameraData.nearDist, mCameraData.farDist);
				bgfx::setViewTransform(0, &mCameraData.view[0][0], &proj[0][0]);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

				// This dummy draw call is here to make sure that view 0 is cleared
				// if no other draw calls are submitted to view 0.
				bgfx::touch(0);

				auto meshes = mPreRenderSystem.getMeshes(mCameraData);

				auto chunkOffset = mCameraData.blockSize * mCameraData.chunkSize;
				for (auto& mesh : meshes)
				{
					auto transform = glm::mat4(1.0f);
					transform = glm::translate(transform, glm::vec3((float)mesh->x*chunkOffset, 0, (float)mesh->z*chunkOffset));
					bgfx::setTransform(&transform[0][0]);

					bgfx::setVertexBuffer(0, mesh->getVertexBufferHandle());
					bgfx::setIndexBuffer(mesh->getIndexBufferHandle());

					bgfx::setState(0
						| BGFX_STATE_DEFAULT
						| BGFX_STATE_CULL_CW
					); 
					bgfx::submit(0, m_program);
				}

				// Advance to next frame. Rendering thread will be kicked to
				// process submitted rendering primitives.
				bgfx::frame();

				return true;
			}

			return false;
		}
		void updateCamera(float deltaTime)
		{
			cameraUpdate(deltaTime, m_mouseState);

			float view[16];
			cameraGetViewMtx(view);
			mCameraData.view = glm::mat4(1.0f);
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					mCameraData.view[i][j] = view[i * 4 + j];

			float pos[3];
			cameraGetPosition(pos);
			mCameraData.pos = glm::vec3(pos[0], pos[1], pos[2]);

			float at[3];
			cameraGetAt(at);
			mCameraData.lookAt = glm::vec3(at[0], at[1], at[2]);

			mCameraData.ratio = (float)m_width / (float)m_height;
			mCameraData.farDist = (mCameraData.viewDistance - 1) * mCameraData.chunkSize * mCameraData.blockSize;
		}

		entry::MouseState m_mouseState;

		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_debug;
		uint32_t m_reset;
		bgfx::VertexBufferHandle m_vbh;
		bgfx::IndexBufferHandle m_ibh;
		bgfx::ProgramHandle m_program;
		int64_t m_timeOffset;

		CellSystem mCellSystem = MapGenerator{ 0 };
		CullingSystem mCullingSystem = mCellSystem;
		PreRenderSystem mPreRenderSystem = mCullingSystem;

		CameraData mCameraData;
	};


} // namespace

