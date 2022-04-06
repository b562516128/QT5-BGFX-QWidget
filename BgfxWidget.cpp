#include "BgfxWidget.h"
#include "bgfx/platform.h"

#include <QtCore/QCoreApplication>

#include <bx/bx.h>
#include <bx/file.h>
#include <bx/sort.h>

#include "TestCubes.h"
#include <bx/os.h>

bx::FileReaderI* BGFXWidget::s_fileReader = NULL;
bx::FileWriterI* BGFXWidget::s_fileWriter = NULL;

extern bx::AllocatorI* getDefaultAllocator();
bx::AllocatorI* BGFXWidget::g_allocator = getDefaultAllocator();;

#if ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR
bx::AllocatorI* getDefaultAllocator()
{
    BX_PRAGMA_DIAGNOSTIC_PUSH();
    BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4459); // warning C4459: declaration of 's_allocator' hides global declaration
    BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow");
    static bx::DefaultAllocator s_allocator;
    return &s_allocator;
    BX_PRAGMA_DIAGNOSTIC_POP();
}
#endif // ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR


bx::FileReaderI* BGFXWidget::fileReader()
{
    return s_fileReader;
}
bx::AllocatorI* BGFXWidget::allocator()
{
    return g_allocator;
}

BGFXWidget::BGFXWidget(QWidget * parent)
    : QWidget(parent)
    , m_widgetInitilized(false)
    , m_bgfxInitialized(false)
{

}

BGFXWidget::~BGFXWidget()
{
    m_tcube->shutdown();
    bgfx::shutdown();
}

void BGFXWidget::resizeEvent(QResizeEvent* event)
{
    if (!m_widgetInitilized || !m_bgfxInitialized)
        return;

    auto w = static_cast<uint16_t>(windowHandle()->size().width());
    auto h = static_cast<uint16_t>(windowHandle()->size().height());

    bgfx::setViewRect(0, 0, 0, w, h);

    // Set view 0 clear state.
   bgfx::setViewClear(0
        , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
        , 0x30ff30ff
        , 1.0f
        , 0
    );

    bgfx::reset(w, h, BGFX_RESET_NONE);

    m_tcube->onResize();
}


void BGFXWidget::paintEvent(QPaintEvent* event)
{
    if (!m_widgetInitilized || !m_bgfxInitialized)
        return;

    m_tcube->update();
}

void BGFXWidget::initBGFX()
{
    const auto width = windowHandle()->size().width();
    const auto height = windowHandle()->size().height();

    const auto debug = BGFX_DEBUG_NONE;
    const auto reset = BGFX_RESET_VSYNC;

    bgfx::Init init;
    init.vendorId = BGFX_PCI_ID_NONE;
    init.profile = true;
    init.debug = debug;
    init.resolution.width = unsigned(width);
    init.resolution.height = unsigned(height);
    init.resolution.reset = reset;
    init.platformData.nwh = reinterpret_cast<void*>(windowHandle()->winId());
    init.type = bgfx::RendererType::OpenGL;//  Direct3D11;

    m_bgfxInitialized = bgfx::init(init);
    if (!m_bgfxInitialized)
    {
        throw("Initialization of BGFX failed");
    }

    // Enable debug text.
    bgfx::setDebug(debug);
    bgfx::setViewRect(0, 0, 0, width, height);

    // Set view 0 clear state.
    bgfx::setViewClear(0
        , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
        , 0x303030ff
        , 1.0f
        , 0
    );

    // init out test scene
    m_tcube = new TestCubes();
    m_tcube->init(this);
}

void BGFXWidget::init()
{
    s_fileReader = BX_NEW(g_allocator, bx::FileReader);
    s_fileWriter = BX_NEW(g_allocator, bx::FileWriter);

    initBGFX();
    m_widgetInitilized = true;
}

void BGFXWidget::mousePressEvent(QMouseEvent* event)
{
}
void BGFXWidget::mouseReleaseEvent(QMouseEvent* event)
{

}
void BGFXWidget::mouseMoveEvent(QMouseEvent* event)
{

}
void BGFXWidget::enterEvent(QEvent* event)
{

}
void BGFXWidget::leaveEvent(QEvent* event)
{
}
void BGFXWidget::wheelEvent(QWheelEvent* event)
{
}

void BGFXWidget::focusInEvent(QFocusEvent* event)
{
}
void BGFXWidget::focusOutEvent(QFocusEvent* event)
{
}