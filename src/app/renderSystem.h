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

#include <debugdraw/debugdraw.h>

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
			PosNormalTangentTexcoordVertex::init();

			// Create texture sampler uniforms.
			s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);

			// Create program from shaders.
			m_program = loadProgram("vs_bump", "fs_bump");
			// Load diffuse texture.
			m_textureColor = loadTexture("textures/dirt.dds");

			//m_skybox = loadTexture("textures/fieldstone-rgba.dds");
			m_skybox = loadTexture("textures/skybox.dds");

			core::Vector<PosNormalTangentTexcoordVertex> skyboxVert;
			core::Vector<uint16_t> skyboxIndices;
			for (auto i = 0; i < 24; i++)
			{
				PosNormalTangentTexcoordVertex clone = s_cubeVertices[i];
				clone.m_x += 2;
				clone.m_y += 2;
				clone.m_z += 2;
				skyboxVert.push_back(clone);
			}
			for (auto i = 0; i < 6; i ++)
			{
				skyboxIndices.push_back(i * 4 + 0);
				skyboxIndices.push_back(i * 4 + 1);
				skyboxIndices.push_back(i * 4 + 2);
				skyboxIndices.push_back(i * 4 + 2);
				skyboxIndices.push_back(i * 4 + 1);
				skyboxIndices.push_back(i * 4 + 3);
			}
			auto vMem = bgfx::copy(skyboxVert.data(), sizeof(skyboxVert[0])*skyboxVert.size());
			skyboxVbh = bgfx::createVertexBuffer(vMem, PosNormalTangentTexcoordVertex::ms_decl);
			skyboxVert.clear();

			auto iMem = bgfx::copy(skyboxIndices.data(), sizeof(skyboxIndices[0])*skyboxIndices.size());
			skyboxIbh = bgfx::createIndexBuffer(iMem);
			skyboxIndices.clear();

			m_timeOffset = bx::getHPCounter();

			ddInit();

			imguiCreate();

			slider = 236.0f;

			cameraCreate();

			const float initialPos[3] = { 5.0f, 20.0, 0.0f };
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

				ImGui::SetNextWindowPos(
					ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
					, ImGuiCond_FirstUseEver
				);
				ImGui::SetNextWindowSize(
					ImVec2(m_width / 5.0f, m_height / 2.0f)
					, ImGuiCond_FirstUseEver
				);
				ImGui::Begin("Settings"
					, NULL
					, 0
				);
				ImGui::SliderFloat("Custom", &slider, 0.0f, 1000.0f);
				ImGui::End();



				imguiEndFrame();

				float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));

				updateCamera(deltaTime);

				//auto proj = perspective(mCameraData.fov, mCameraData.ratio, mCameraData.nearDist, mCameraData.farDist);
				//bgfx::setViewTransform(0, &mCameraData.view[0][0], &proj[0][0]);
				//bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));
				//bgfx::setViewTransform(1, &mCameraData.view[0][0], &proj[0][0]);
				//bgfx::setViewRect(1, 0, 0, uint16_t(m_width), uint16_t(m_height));

				// This dummy draw call is here to make sure that view 0 is cleared
				// if no other draw calls are submitted to view 0.
				bgfx::touch(0);

				float view[16];
				//cameraGetViewMtx(view);
				float zero[3] = {};
				//float eye[3];
				//cameraGetPosition(eye);
				float eye[] = { 30.0f, 50.0f, 30.0f };
				bx::mtxLookAt(view, eye, zero);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

				bgfx::setViewTransform(0, view, proj);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));



				float mtxVp[16];
				bx::mtxMul(mtxVp, view, proj);

				float mtxInvVp[16];
				bx::mtxInverse(mtxInvVp, mtxVp);

				//float eye2[] = { 0.0f, 10.0f, 0.0f };
				//float eye[3];
				//cameraGetPosition(eye);
				//bx::mtxLookAt(view, eye2, zero);
				cameraGetViewMtx(view);
				bx::mtxProj(proj, 45.0f, float(m_width) / float(m_height), 1.0f, 15.0f, bgfx::getCaps()->homogeneousDepth);
				bx::mtxMul(mtxVp, view, proj);

				ddBegin(0);
				ddDrawAxis(0.0f, 0.0f, 0.0f);

				ddSetTransform(NULL);
				ddDrawFrustum(mtxVp);

				drawPoint(mCameraData);

				//renderSkybox();

				auto meshes = mPreRenderSystem.getMeshes(mCameraData);
				auto chunkOffset = mCameraData.blockSize * mCameraData.chunkSize;
				for (auto& mesh : meshes)
				{
					auto transform = glm::mat4(1.0f);
					mesh->submitMesh(0, m_program, transform, s_texColor, m_textureColor);
				}

				ddEnd();
				// Advance to next frame. Rendering thread will be kicked to
				// process submitted rendering primitives.
				bgfx::frame();

				return true;
			}

			return false;
		}

		void drawPoint(const CameraData& cameraData) {
			float tanRatio = 2 * tan(cameraData.fov / 2);
			float nearHeight = tanRatio * cameraData.nearDist;
			float nearWidth = nearHeight * cameraData.ratio;
			float farHeight = tanRatio * cameraData.farDist;
			float farWidth = farHeight * cameraData.ratio;
			glm::vec3 ray = glm::normalize(cameraData.lookAt - cameraData.pos);
			glm::vec3 rightVector = glm::cross(ray, cameraData.up);

			glm::vec3 farCenterPoint = cameraData.pos + ray * cameraData.farDist;
			glm::vec3 nearCenterPoint = cameraData.pos + ray * cameraData.nearDist;

			glm::vec3 rightPlanePoint = nearCenterPoint + rightVector * nearWidth / 2.0f * -1.0f;
			glm::vec3 rightPlaneNormal = glm::cross(cameraData.up, glm::normalize(rightPlanePoint - cameraData.pos));

			glm::vec3 leftPlanePointNear = nearCenterPoint + rightVector * nearWidth / 2.0f * -1.0f;
			glm::vec3 leftPlanePointFar = glm::normalize(farCenterPoint + rightVector) * farWidth / 2.0f * -1.0f;
			glm::vec3 leftPlaneNormal = glm::cross(glm::normalize(leftPlanePointNear - leftPlanePointFar), cameraData.up);

			glm::vec3 leftPlanePoint = nearCenterPoint + rightVector * nearWidth / 2.0f;
			//ddPush();
			//	Sphere sphere = { { nearCenterPoint[0], nearCenterPoint[1], nearCenterPoint[2] }, 1.0f };
			//	ddSetColor(0xfff0c0ff);
			//	ddSetWireframe(true);
			//	ddSetLod(3);
			//	ddDraw(sphere);
			//ddPop();
			ddPush();
				Sphere sphere = { { leftPlanePoint[0], leftPlanePoint[1], leftPlanePoint[2] }, 0.1f };
				ddSetColor(0xfff0c0ff);
				ddSetWireframe(false);
				ddDraw(sphere);

				Sphere sphere2 = { { rightPlanePoint[0], rightPlanePoint[1], rightPlanePoint[2] }, 0.1f };
				ddSetColor(0xfff0c0ff);
				ddSetWireframe(false);
				ddDraw(sphere2);

				Sphere sphere3 = { { nearCenterPoint[0], nearCenterPoint[1], nearCenterPoint[2] }, 0.1f };
				ddSetColor(0xfff0c0ff);
				ddSetWireframe(false);
				ddDraw(sphere3);
			ddPop();
		}

		void renderSkybox() {
			auto transform = glm::mat4(1.0f);
			transform = glm::translate(transform, mCameraData.pos);
			transform = glm::scale(transform, glm::vec3(slider));
			transform = glm::translate(transform, glm::vec3(-2.0f));
			bgfx::setTransform(&transform[0][0]);

			bgfx::setVertexBuffer(0, skyboxVbh);
			bgfx::setIndexBuffer(skyboxIbh);

			// Bind textures.
			bgfx::setTexture(0, s_texColor, m_skybox);

			// Set render states.
			bgfx::setState(0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_WRITE
				| BGFX_STATE_DEPTH_TEST_LESS
				| BGFX_STATE_MSAA
			);
			bgfx::submit(0, m_program);
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

			//mCameraData.up = glm::vec3(mCameraData.view[1][2], mCameraData.view[2][2], mCameraData.view[3][2]);

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
		bgfx::UniformHandle s_texColor;
		bgfx::ProgramHandle m_program;
		bgfx::TextureHandle m_textureColor;

		bgfx::TextureHandle m_skybox;
		bgfx::VertexBufferHandle skyboxVbh;
		bgfx::IndexBufferHandle skyboxIbh;

		int64_t m_timeOffset;

		CellSystem mCellSystem = MapGenerator{ 0 };
		CullingSystem mCullingSystem = mCellSystem;
		PreRenderSystem mPreRenderSystem = mCullingSystem;

		CameraData mCameraData;

		float slider;
	};


} // namespace

