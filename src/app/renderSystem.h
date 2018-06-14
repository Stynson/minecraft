/*
* Copyright 2011-2018 Branimir Karadzic. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "common.h"
#include "camera.h"
#include "cameraData.h"
#include "rayCast.h"

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
	class App : public entry::AppI
	{
	public:
		App(const char* _name, const char* _description)
			: entry::AppI(_name, _description)
		{
		}
    protected: 
		void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override; 
		virtual int shutdown() override; 
		bool update() override; 
		void setupDebugWindow();

		void drawChunkGizmos(); 
		void drawBlockGizmo(glm::vec3 selectedBlock); 

		void startRender();
		void endRender();

		void drawPoint(const CameraData& cameraData);

<<<<<<< HEAD
				endRender();
				return true;
			}

			return false;
		}

		void setupDebugWindow()
		{
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
			ImGui::Text("CameraPos: %f, %f, %f\n", mCameraData.pos.x, mCameraData.pos.y, mCameraData.pos.z);
			ImGui::SliderFloat("Custom", &frustrumFarDistance, 0.0f, 100.0f);
			if (ImGui::Button("FPS View", { 0, 30 }))
				mDebugData.isFirstPerson = !mDebugData.isFirstPerson;
			if (ImGui::Button("Chunk WireFrame", { 0, 30 }))
				mDebugData.showChunkGizmos = !mDebugData.showChunkGizmos;
			ImGui::End();
		}

		void drawChunkGizmos()
		{
			ddPush();
			Aabb aabb;
			auto chunkOffset = mCameraData.chunkSize*mCameraData.blockSize;
			aabb.m_min[0] = 0;
			aabb.m_min[1] = 0;
			aabb.m_min[2] = 0;
			aabb.m_max[0] = chunkOffset;
			aabb.m_max[1] = chunkOffset * 2;
			aabb.m_max[2] = chunkOffset;
			ddSetColor(0xfff0c0ff);
			ddSetWireframe(true);
			ddDraw(aabb);
			ddPop();
		}

		void drawBlockGizmo(glm::vec3 selectedBlock)
		{
			ddPush();
			Aabb aabb;
			aabb.m_min[0] = std::floor(selectedBlock.x);
			aabb.m_min[1] = std::floor(selectedBlock.y);
			aabb.m_min[2] = std::floor(selectedBlock.z);
			aabb.m_max[0] = std::floor(selectedBlock.x) + 1.0f;
			aabb.m_max[1] = std::floor(selectedBlock.y) + 1.0f;
			aabb.m_max[2] = std::floor(selectedBlock.z) + 1.0f;
			ddSetColor(0xfff0c0ff);
			ddSetWireframe(true);
			ddDraw(aabb);
			ddPop();
		}

		void startRender()
		{
			ddBegin(0);
			if (!mDebugData.isFirstPerson)
			{
				glm::mat4 debugCameraView;
				glm::vec3 zero(0.0f);
				glm::vec3 eye(25.0f, 35.0f, 25.0f);
				bx::mtxLookAt(&debugCameraView[0][0], &eye[0], &zero[0]);
				auto debugCameraProj = perspective(mCameraData.fov, mCameraData.ratio, mCameraData.nearDist, mCameraData.farDist);

				bgfx::setViewTransform(0, &debugCameraView[0][0], &debugCameraProj[0][0]);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

				cameraGetViewMtx(&mCameraData.view[0][0]);
				auto frustrumCameraProj = perspective(mCameraData.fov, mCameraData.ratio, mCameraData.nearDist, frustrumFarDistance);
				auto mtxVp = frustrumCameraProj * mCameraData.view;

				ddDrawAxis(0.0f, 0.0f, 0.0f);
				ddSetTransform(NULL);
				ddDrawFrustum(&mtxVp[0][0]);
				drawPoint(mCameraData);
			}
			else
			{
				auto proj = perspective(mCameraData.fov, mCameraData.ratio, mCameraData.nearDist, mCameraData.farDist);
				bgfx::setViewTransform(0, &mCameraData.view[0][0], &proj[0][0]);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

				auto ppp = mCameraData.pos + glm::normalize(mCameraData.lookAt - mCameraData.pos);
				ddDrawAxis(ppp[0], ppp[1], ppp[2]);
			}
		}
		void endRender()
		{
			ddEnd();
			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();
		}

		void drawPoint(const CameraData& cameraData) {
			float tanRatio = 2 * tan(cameraData.fov / 2);
			float nearHeight = tanRatio * cameraData.nearDist;
			float nearWidth = nearHeight * cameraData.ratio;
			float farHeight = tanRatio * cameraData.farDist;
			float farWidth = farHeight * cameraData.ratio;
			glm::vec3 ray = glm::normalize(cameraData.lookAt - cameraData.pos);
			glm::vec3 rightVector = glm::normalize(glm::cross(ray, cameraData.up));

			glm::vec3 farCenterPoint = cameraData.pos + ray * cameraData.farDist;
			glm::vec3 nearCenterPoint = cameraData.pos + ray * cameraData.nearDist / 2.0f;

			glm::vec3 rightPlanePoint = nearCenterPoint + rightVector * nearWidth / 2.0f * -1.0f;
			glm::vec3 rightPlaneNormal = glm::cross(cameraData.up, glm::normalize(rightPlanePoint - cameraData.pos)) * -1.0f;

			glm::vec3 leftPlanePoint = nearCenterPoint + rightVector * nearWidth / 2.0f;
			glm::vec3 leftPlaneNormal = glm::cross(cameraData.up, glm::normalize(leftPlanePoint - cameraData.pos));

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
			transform = glm::scale(transform, glm::vec3(mCameraData.farDist*0.6f));
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
=======
		void renderSkybox();
		void updateCamera(float deltaTime);
    private:
>>>>>>> 43f0a9e3034747384b2a6a297a55a378bf825b25

		entry::MouseState m_mouseState;
		entry::MouseState r_mouseState;

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

		struct DebugData
		{
			bool isFirstPerson = true;
			bool showChunkGizmos = false;
		};
		DebugData mDebugData;

		float frustrumFarDistance;
		bool mMouseClicked = false;
		bool rMouseClicked = false;
	}; 

} // namespace

