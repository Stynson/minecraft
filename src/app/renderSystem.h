#pragma once
#include "chunk.h"
#include "cullingSystem.h"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
};

/*
* Copyright 2011-2018 Branimir Karadzic. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "camera.h"
#include "bounds.h"

#include <bx/allocator.h>
#include <bx/debug.h>
#include <bx/math.h>
#include <bx/rng.h>



namespace mc
{
	static float s_texelHalf = 0.0f;

	struct PosColorVertex
	{
		float m_x;
		float m_y;
		float m_z;
		uint32_t m_abgr;

		static void init()
		{
			ms_decl
				.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
				.end();
		};

		static bgfx::VertexDecl ms_decl;
	};


	static PosColorVertex s_cubeVertices[8] =
	{
		{ -1.0f,  1.0f,  1.0f, 0xff000000 }
		, { 1.0f,  1.0f,  1.0f, 0xff0000ff }
		, { -1.0f, -1.0f,  1.0f, 0xff00ff00 }
		, { 1.0f, -1.0f,  1.0f, 0xff00ffff }
		, { -1.0f,  1.0f, -1.0f, 0xffff0000 }
		, { 1.0f,  1.0f, -1.0f, 0xffff00ff }
		, { -1.0f, -1.0f, -1.0f, 0xffffff00 }
		, { 1.0f, -1.0f, -1.0f, 0xffffffff }
	};

	static const uint16_t s_cubeIndices[36] =
	{
		0, 1, 2, // 0
		1, 3, 2,
		4, 6, 5, // 2
		5, 6, 7,
		0, 2, 4, // 4
		4, 2, 6,
		1, 5, 3, // 6
		5, 7, 3,
		0, 4, 1, // 8
		4, 5, 1,
		2, 3, 6, // 10
		6, 3, 7,
	};
	//struct PosColorTexCoord0Vertex
	//{
	//	float m_x;
	//	float m_y;
	//	float m_z;
	//	uint32_t m_rgba;
	//	float m_u;
	//	float m_v;

	//	static void init()
	//	{
	//		ms_decl
	//			.begin()
	//			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
	//			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
	//			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
	//			.end();
	//	}

	//	static bgfx::VertexDecl ms_decl;
	//};



	//bgfx::VertexDecl PosColorTexCoord0Vertex::ms_decl;

	//void screenSpaceQuad(float _textureWidth, float _textureHeight, bool _originBottomLeft = false, float _width = 1.0f, float _height = 1.0f)
	//{
	//	if (3 == bgfx::getAvailTransientVertexBuffer(3, PosColorTexCoord0Vertex::ms_decl))
	//	{
	//		bgfx::TransientVertexBuffer vb;
	//		bgfx::allocTransientVertexBuffer(&vb, 3, PosColorTexCoord0Vertex::ms_decl);
	//		PosColorTexCoord0Vertex* vertex = (PosColorTexCoord0Vertex*)vb.data;

	//		const float zz = 0.0f;

	//		const float minx = -_width;
	//		const float maxx = _width;
	//		const float miny = 0.0f;
	//		const float maxy = _height * 2.0f;

	//		const float texelHalfW = s_texelHalf / _textureWidth;
	//		const float texelHalfH = s_texelHalf / _textureHeight;
	//		const float minu = -1.0f + texelHalfW;
	//		const float maxu = 1.0f + texelHalfW;

	//		float minv = texelHalfH;
	//		float maxv = 2.0f + texelHalfH;

	//		if (_originBottomLeft)
	//		{
	//			float temp = minv;
	//			minv = maxv;
	//			maxv = temp;

	//			minv -= 1.0f;
	//			maxv -= 1.0f;
	//		}

	//		vertex[0].m_x = minx;
	//		vertex[0].m_y = miny;
	//		vertex[0].m_z = zz;
	//		vertex[0].m_rgba = 0xffffffff;
	//		vertex[0].m_u = minu;
	//		vertex[0].m_v = minv;

	//		vertex[1].m_x = maxx;
	//		vertex[1].m_y = miny;
	//		vertex[1].m_z = zz;
	//		vertex[1].m_rgba = 0xffffffff;
	//		vertex[1].m_u = maxu;
	//		vertex[1].m_v = minv;

	//		vertex[2].m_x = maxx;
	//		vertex[2].m_y = maxy;
	//		vertex[2].m_z = zz;
	//		vertex[2].m_rgba = 0xffffffff;
	//		vertex[2].m_u = maxu;
	//		vertex[2].m_v = maxv;

	//		bgfx::setVertexBuffer(0, &vb);
	//	}
	//}

	class RenderSystem
	{
	public:
		void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height, uint32_t& reset)
		{
			Args args(_argc, _argv);

			mWidth = _width;
			mHeight = _height;
			m_debug = BGFX_DEBUG_TEXT;
			reset = BGFX_RESET_VSYNC;

			bgfx::init(args.m_type, args.m_pciId);
			bgfx::reset(mWidth, mHeight, reset);
			//PosColorTexCoord0Vertex::init();


			// Enable debug text.
			bgfx::setDebug(m_debug);

			// Set view 0 clear state.
			bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
			);

			m_uffizi = loadTexture("textures/uffizi.dds"
				, 0
				| BGFX_TEXTURE_U_CLAMP
				| BGFX_TEXTURE_V_CLAMP
				| BGFX_TEXTURE_W_CLAMP
			);
			s_texCube = bgfx::createUniform("s_texCube", bgfx::UniformType::Int1);
			u_mtx = bgfx::createUniform("u_mtx", bgfx::UniformType::Mat4);



			// Create vertex stream declaration.
			PosColorVertex::init();

			// Create static vertex buffer.
			m_vbh = bgfx::createVertexBuffer(
				bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices))
				, PosColorVertex::ms_decl
			);

			// Create static index buffer.
			m_ibh = bgfx::createIndexBuffer(
				bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices))
			);

			// Create program from shaders.
			m_program = loadProgram("vs_instancing", "fs_instancing");
			//m_skyProgram = loadProgram("vs_hdr_skybox", "fs_hdr_skybox");

			//m_fbh.idx = bgfx::kInvalidHandle;



			m_timeOffset = bx::getHPCounter();

			cameraCreate();

			const float initialPos[3] = { 0, 0, -20.0f };
			cameraSetPosition(initialPos);
			cameraSetVerticalAngle(0);// -bx::kPi / 4.0f);

			imguiCreate();
		}
		int shutdown()
		{
			imguiDestroy();

			// Cleanup.
			bgfx::destroy(m_ibh);
			bgfx::destroy(m_vbh);
			bgfx::destroy(m_program);
			//bgfx::destroy(m_skyProgram);


			// Shutdown bgfx.
			bgfx::shutdown();

			return 0;
		}

		bool update(uint32_t width, uint32_t height, uint32_t reset, entry::MouseState m_mouseState)
		{
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency());
			const float deltaTime = float(frameTime / freq);


			imguiEndFrame();

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(mWidth), uint16_t(mHeight));

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);


			//bgfx::ViewId shuffle[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			//bx::shuffle(&m_rng, shuffle, BX_COUNTOF(shuffle));


			//bgfx::ViewId hdrSkybox = shuffle[0];
			//bgfx::ViewId hdrMesh = shuffle[1];


			//bgfx::ViewId order[] =
			//{
			//	hdrSkybox,
			//	hdrMesh,
			//};

			//bgfx::setViewOrder(0, BX_COUNTOF(order), order);
			//float proj[16];

			//// Set view and projection matrix for view 0.
			//for (uint8_t ii = 0; ii < BX_COUNTOF(order); ++ii)
			//{
			//	bgfx::setViewTransform(ii, NULL, proj);
			//} 

			// Set views.
			//bgfx::setViewName(hdrSkybox, "Skybox");
			//bgfx::setViewClear(hdrSkybox, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
			//bgfx::setViewRect(hdrSkybox, 0, 0, bgfx::BackbufferRatio::Equal);
			//bgfx::setViewFrameBuffer(hdrSkybox, m_fbh);

			//bgfx::setViewName(hdrMesh, "Mesh");
			//bgfx::setViewClear(hdrMesh, BGFX_CLEAR_DISCARD_DEPTH | BGFX_CLEAR_DISCARD_STENCIL);
			//bgfx::setViewRect(hdrMesh, 0, 0, bgfx::BackbufferRatio::Equal);
			//bgfx::setViewFrameBuffer(hdrMesh, m_fbh);

			// Render skybox into view hdrSkybox.
			//bgfx::setTexture(0, s_texCube, m_uffizi);
			//bgfx::setState(BGFX_STATE_RGB_WRITE | BGFX_STATE_ALPHA_WRITE);
			//bgfx::setUniform(u_mtx, m_viewMtx);
			//screenSpaceQuad((float)m_width, (float)m_height, true);
			//bgfx::submit(hdrSkybox, m_skyProgram);


			float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));

			// Get renderer capabilities info.
			const bgfx::Caps* caps = bgfx::getCaps();

			// Check if instancing is supported.
			if (0 == (BGFX_CAPS_INSTANCING & caps->supported))
			{
				// When instancing is not supported by GPU, implement alternative
				// code path that doesn't use instancing.
				bool blink = uint32_t(time*3.0f) & 1;
				bgfx::dbgTextPrintf(0, 0, blink ? 0x1f : 0x01, " Instancing is not supported by GPU. ");
			}
			else
			{

				if (!ImGui::MouseOverArea())
				{
					cameraUpdate(deltaTime, m_mouseState);
					//if (!!m_mouseState.m_buttons[entry::MouseButton::Left])
				}
				//				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(mWidth), uint16_t(mHeight));

				cameraGetViewMtx(m_viewMtx);

				for (auto& chunk : mCullingSystem.getCulledChunks(0, 0, 1.0, 5))
				{
					renderChunk(*chunk);
				}
			}

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();
			return true;
		}
		void renderChunk(const Chunk& chunk)
		{
			bx::mtxProj(m_projMtx, 60.0f, float(mWidth) / float(mHeight), 0.1f, 2000.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, m_viewMtx, m_projMtx);
			//TODO
			float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));

			// 80 bytes stride = 64 bytes for 4x4 matrix + 16 bytes for RGBA color.
			const uint16_t instanceStride = 80;
			const uint32_t numInstances = 16 * 16 * 256;

			if (numInstances == bgfx::getAvailInstanceDataBuffer(numInstances, instanceStride))
			{
				bgfx::InstanceDataBuffer idb;
				bgfx::allocInstanceDataBuffer(&idb, numInstances, instanceStride);

				uint8_t* data = idb.data;

				for (uint32_t y = 0; y < 256; ++y)
				{
					for (uint32_t z = 0; z < 16; ++z)
					{
						for (uint32_t x = 0; x < 16; ++x)
						{
							if (chunk.getBlock(x, z, y).type == BlockType::DIRT)
							{
								float* mtx = (float*)data;
								//bx::mtxRotateXY(mtx, time + x*0.21f, time + y*0.37f);
								bx::mtxRotateXY(mtx, 0, 0);
								mtx[12] = -15.0f + float(x)*2.0f;
								mtx[13] = -15.0f + float(y)*2.0f;
								mtx[14] = float(z)*2.0f;

								float* color = (float*)&data[64];
								color[0] = 0.0f;// bx::sin(time + float(x) / 11.0f)*0.5f + 0.5f;
								color[1] = 1.0f;// bx::cos(time + float(y) / 11.0f)*0.5f + 0.5f;
								color[2] = 0.0f;//bx::sin(time*3.0f)*0.5f + 0.5f;
								color[3] = 1.0f;

								data += instanceStride;
							}
						}
					}
				}

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(0, m_vbh);
				bgfx::setIndexBuffer(m_ibh);

				// Set instance data buffer.
				bgfx::setInstanceDataBuffer(&idb);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 0.
				bgfx::submit(0, m_program);

			}
		}
	private:
		CellSystem mCellSystem = MapGenerator{ 0 };
		CullingSystem mCullingSystem = mCellSystem;
		bgfx::TextureHandle m_uffizi;
		bgfx::UniformHandle s_texCube;
		bgfx::UniformHandle u_mtx;

		bx::RngMwc m_rng;

		bgfx::FrameBufferHandle m_fbh;


		uint32_t m_debug;
		bgfx::VertexBufferHandle m_vbh;
		bgfx::IndexBufferHandle  m_ibh;
		bgfx::ProgramHandle m_program;
		bgfx::ProgramHandle m_skyProgram;

		uint32_t mWidth;
		uint32_t mHeight;

		int64_t m_timeOffset;

		float m_viewMtx[16];
		float m_projMtx[16];
	};

	class ExampleInstancing : public entry::AppI
	{
	public:
		ExampleInstancing(const char* _name, const char* _description)
			: entry::AppI(_name, _description)
		{
		}

		void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
		{
			mRenderSystem.init(_argc, _argv, _width, _height, m_reset);
		}

		int shutdown() override
		{
			return mRenderSystem.shutdown();
		}

		bool update() override
		{
			if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
			{
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
				return mRenderSystem.update(m_width, m_height, m_reset, m_mouseState);
			}
			return false;
		}

		RenderSystem mRenderSystem;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_debug;
		uint32_t m_reset;
		entry::MouseState m_mouseState;
	};

} // namespace
