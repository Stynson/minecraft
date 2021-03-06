#include "renderSystem.h"



namespace mc
{ 
    //UTILITY functions

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


    void debugPoint(float x, float y, float z)
    {
        ddPush();
        Sphere sphere = { { x, y, z }, 0.01f };
        //ddSetColor(0x3f50ffff);
        ddSetColor(0xA52A2AFF);
        ddSetWireframe(false);
        ddDraw(sphere);
        ddPop();
    }

    
	//bgfx::VertexDecl PosColorVertex::ms_decl;
	bgfx::VertexDecl PosNormalTangentTexcoordVertex::ms_decl;


    void App::init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height)
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
            , 0x87ceebff
            , 1.0f
            , 0
        );

        // Create vertex stream declaration.
        PosNormalTangentTexcoordVertex::init();

        // Create texture sampler uniforms.
        s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);

        // Create program from shaders.
        m_program = loadProgram("vs_cubes", "fs_cubes");
        // Load diffuse texture.
        m_textureColor = loadTexture("textures/terrain.png", BGFX_TEXTURE_MAG_POINT);

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
        for (auto i = 0; i < 6; i++)
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

        frustrumFarDistance = 200.0f;
        cameraCreate();

        const float initialPos[3] = { 5.0f, 20.0, 0.0f };
        cameraSetPosition(initialPos);
        cameraSetVerticalAngle(bx::kPi / 8.0f);
        cameraSetHorizontalAngle(-bx::kPi / 3.0f);

    }

    int App::shutdown()
    {
        cameraDestroy();
        imguiDestroy();

        // Cleanup.
        bgfx::destroy(m_program);

        // Shutdown bgfx.
        bgfx::shutdown();

        return 0;
    }

    bool App::update()
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


            setupDebugWindow();

            imguiEndFrame();

            float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));

            updateCamera(deltaTime);
            // This dummy draw call is here to make sure that view 0 is cleared
            // if no other draw calls are submitted to view 0.
            bgfx::touch(0);

            auto nearChunks = mCellSystem.getNearbyChunks(mCameraData, 1);
            RayCast rc(nearChunks);
            auto raycastResult = rc.raycast(mCameraData, 20, debugPoint);
            if (raycastResult.selected) {
                drawBlockGizmo(raycastResult.blockCoord);
                if (mMouseClicked || rMouseClicked)
                {
                    mMouseClicked = m_mouseState.m_buttons[entry::MouseButton::Left] == 1;					
                    rMouseClicked = m_mouseState.m_buttons[entry::MouseButton::Right] == 1;
                }
                else
                {
                    if (m_mouseState.m_buttons[entry::MouseButton::Left] == 1) 
                    {
                        mMouseClicked = true;
                        mCellSystem.setBlockType(BlockType::AIR, raycastResult.blockCoord);
                    }
                    if (m_mouseState.m_buttons[entry::MouseButton::Right] == 1) // place block
                    {
                        rMouseClicked = true;
                        mCellSystem.setBlockType(BlockType::DIRT, (raycastResult.blockCoord + raycastResult.face));
                    }
                }
            }


            startRender();
            //renderSkybox();

            auto meshes = mPreRenderSystem.getMeshes(mCameraData);
            auto chunkOffset = mCameraData.blockSize * mCameraData.chunkSize;
            for (auto& mesh : meshes)
            {
                auto transform = glm::mat4(1.0f);
                transform = glm::translate(transform, glm::vec3(0.5f));
                mesh->submitMesh(0, m_program, transform, s_texColor, m_textureColor);
            }


            if (mDebugData.showChunkGizmos)
            {
                drawChunkGizmos();
            }

            endRender();
            return true;
        }

        return false;
    }

    void App::setupDebugWindow()
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

    void App::drawChunkGizmos()
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

    void App::drawBlockGizmo(glm::vec3 selectedBlock)
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

    void App::startRender()
    {
        ddBegin(0);
        if (mDebugData.isFirstPerson)
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

    void App::endRender()
    {
        ddEnd();
        // Advance to next frame. Rendering thread will be kicked to
        // process submitted rendering primitives.
        bgfx::frame();
    }

    void App::drawPoint(const CameraData& cameraData)
    {
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

    void App::renderSkybox()
    {
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

    void App::updateCamera(float deltaTime)
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
}
