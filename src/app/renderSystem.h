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

		void renderSkybox();
		void updateCamera(float deltaTime);
    private:

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

