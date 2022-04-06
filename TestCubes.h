#pragma once
#ifndef _TESTCUBES_H_
#define _TESTCUBES_H_

#include "common.h"
#include "bgfx_utils.h"
#include "DataStructs.h"

class BGFXWidget;

class TestCubes
{
public:
	void init(BGFXWidget* widget);

	int shutdown();

	bool update();

	void onResize();

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh[BX_COUNTOF(s_ptState)];
	bgfx::ProgramHandle m_shaderProgram;
	int64_t m_timeOffset;
	int32_t m_pt;

	BGFXWidget* m_bgfxWidget;
};

#endif //pragma once