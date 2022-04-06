#include "TestCubes.h"
#include "BgfxWidget.h"

bgfx::VertexLayout PosColorVertex::ms_layout;

void TestCubes::init(BGFXWidget* widget)
{
	m_bgfxWidget = widget;

	m_width = widget->windowHandle()->size().width();
	m_height = widget->windowHandle()->size().height();

	// Create vertex stream declaration.
	PosColorVertex::init();

	// Create static vertex buffer.
	m_vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices))
		, PosColorVertex::ms_layout
	);

	// Create static index buffer for triangle list rendering.
	m_ibh[0] = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
	);

	// Create static index buffer for triangle strip rendering.
	m_ibh[1] = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeTriStrip, sizeof(s_cubeTriStrip))
	);

	// Create static index buffer for line list rendering.
	m_ibh[2] = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeLineList, sizeof(s_cubeLineList))
	);

	// Create static index buffer for line strip rendering.
	m_ibh[3] = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeLineStrip, sizeof(s_cubeLineStrip))
	);

	// Create static index buffer for point list rendering.
	m_ibh[4] = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubePoints, sizeof(s_cubePoints))
	);

	// Create program from shaders.
	m_shaderProgram = loadAndCreateShaderProgram(m_bgfxWidget->fileReader(), "vs_cubes", "fs_cubes");

	m_timeOffset = bx::getHPCounter(); 
}

int TestCubes::shutdown()
{
	// Cleanup.
	for (uint32_t ii = 0; ii < BX_COUNTOF(m_ibh); ++ii)
	{
		bgfx::destroy(m_ibh[ii]);
	}

	bgfx::destroy(m_vbh);
	bgfx::destroy(m_shaderProgram);
	return 0;
}

void TestCubes::onResize()
{
	m_width = m_bgfxWidget->windowHandle()->size().width();
	m_height = m_bgfxWidget->windowHandle()->size().height();
}

bool TestCubes::update()
{
	float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));

	const bx::Vec3 at = { 0.0f, 0.0f,   0.0f };
	const bx::Vec3 eye = { 0.0f, 0.0f, -35.0f };

	// Set view and projection matrix for view 0.
	{
		float view[16];
		bx::mtxLookAt(view, eye, at);

		float proj[16];
		bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
		bgfx::setViewTransform(0, view, proj);

		// Set view 0 default viewport.
		//bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));
	}

	// This dummy draw call is here to make sure that view 0 is cleared
	// if no other draw calls are submitted to view 0.
	bgfx::touch(0);

	m_pt = 0;
	bgfx::IndexBufferHandle ibh = m_ibh[m_pt];
	uint64_t state = 0
		| BGFX_STATE_WRITE_R
		| BGFX_STATE_WRITE_G
		| BGFX_STATE_WRITE_B
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_WRITE_Z
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CW
		| BGFX_STATE_MSAA
		| s_ptState[m_pt]
		;

	// Submit 11x11 cubes.
	for (uint32_t yy = 0; yy < 11; ++yy)
	{
		for (uint32_t xx = 0; xx < 11; ++xx)
		{
			float mtx[16];
			bx::mtxRotateXY(mtx, time + xx * 0.21f, time + yy * 0.37f);
			mtx[12] = -15.0f + float(xx) * 3.0f;
			mtx[13] = -15.0f + float(yy) * 3.0f;
			mtx[14] = 0.0f;

			// Set model matrix for rendering.
			bgfx::setTransform(mtx);

			// Set vertex and index buffer.
			bgfx::setVertexBuffer(0, m_vbh);
			bgfx::setIndexBuffer(ibh);

			// Set render states.
			bgfx::setState(state);

			// Submit primitive for rendering to view 0.
			bgfx::submit(0, m_shaderProgram);
		}
	}

	// Advance to next frame. Rendering thread will be kicked to
	// process submitted rendering primitives.
	bgfx::frame();

	return true;
}
