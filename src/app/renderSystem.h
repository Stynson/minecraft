/*
* Copyright 2011-2018 Branimir Karadzic. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "common.h"
#include "camera.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "preRenderSystem.h"

namespace mc
{

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

				float at[3] = { 0.0f, 0.0f,   0.0f };
				float eye[3] = { -50.0f, 30.0f, -50.0f };

				float view[16];
////////				bx::mtxLookAt(view, eye, at);


				cameraUpdate(deltaTime, m_mouseState);
				cameraGetViewMtx(view);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 500.0f, bgfx::getCaps()->homogeneousDepth);
				bgfx::setViewTransform(0, view, proj);



				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

				// This dummy draw call is here to make sure that view 0 is cleared
				// if no other draw calls are submitted to view 0.
				bgfx::touch(0);

				auto meshes = mPreRenderSystem.getMeshes(0, 0, 1, 2);

				for (auto& mesh : meshes)
				{
					float mtx[16];
					bx::mtxRotateXY(mtx, 0, 0);
					mtx[12] = float(mesh->x)*2.0f*16.0f;
					mtx[13] = 0.0f;
					mtx[14] = float(mesh->z)*2.0f*16.0f;
					bgfx::setTransform(mtx); 

					// Set vertex and index buffer.
					bgfx::setVertexBuffer(0, mesh->getVertexBufferHandle());
					bgfx::setIndexBuffer(mesh->getIndexBufferHandle());

					// Set render states.
					bgfx::setState(0
						| BGFX_STATE_DEFAULT
						| BGFX_STATE_PT_TRISTRIP
					);

					// Submit primitive for rendering to view 0.
					bgfx::submit(0, m_program);
				}

				// Advance to next frame. Rendering thread will be kicked to
				// process submitted rendering primitives.
				bgfx::frame();

				return true;
			}

			return false;
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

		CellSystem mCellSystem = MapGenerator{0};
		CullingSystem mCullingSystem = mCellSystem;
		PreRenderSystem mPreRenderSystem = mCullingSystem;
	};

} // namespace

