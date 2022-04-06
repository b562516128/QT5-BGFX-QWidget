#include "BGFXWidget.h"

#include <QApplication>
#include <QWindow>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	QSurfaceFormat::setDefaultFormat(format);

	// show() must be called before init()
	// bgfx need a window to dealwith  view things
	BGFXWidget bgfxWidget;
	bgfxWidget.show(); 
	bgfxWidget.init();

	QWindow* window = bgfxWidget.windowHandle();
	window->setTitle("test cubes");
	window->setFormat(format);
	window->resize(1000, 480);
	
	return app.exec();
}
