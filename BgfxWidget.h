#pragma once
#ifndef _BGFXWIDGET_H_
#define _BGFXWIDGET_H_

#include"bgfx/bgfx.h"
#include <QWidget>
#include <QWindow>

#include <QtWidgets>
#include <bx/bx.h>
#include <bx/filepath.h>
#include <bx/string.h>
#include <bx/readerwriter.h>

QT_BEGIN_NAMESPACE
class QOpenGLContext;
QT_END_NAMESPACE

#ifndef ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR
#	define ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR 1
#endif // ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR


class TestCubes;

//! [1]
class BGFXWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BGFXWidget(QWidget* parent = 0);
    ~BGFXWidget();

    void init();
    virtual void initBGFX();

public:
    static bx::FileReaderI* fileReader();
    static bx::AllocatorI* allocator();

protected:
    virtual void resizeEvent(QResizeEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override; // 鼠标键按下
    virtual void mouseReleaseEvent(QMouseEvent* event) override; // 鼠标键松开
    virtual void mouseMoveEvent(QMouseEvent* event) override; // 鼠标移动
    virtual void enterEvent(QEvent* event) override; // 鼠标进入窗口
    virtual void leaveEvent(QEvent* event) override; // 鼠标离开窗口
    virtual void wheelEvent(QWheelEvent* event) override; // 鼠标滚轮移动
    virtual void focusInEvent(QFocusEvent* event) override; // 获得焦点
    virtual void focusOutEvent(QFocusEvent* event) override; // 释放焦点
    virtual void paintEvent(QPaintEvent* event) override; // 窗口重绘

private:
    bool m_bgfxInitialized;
    bool m_widgetInitilized;
    TestCubes* m_tcube;

private:
    static bx::FileReaderI* s_fileReader;
    static bx::FileWriterI* s_fileWriter;
    static bx::AllocatorI* g_allocator;

};

#endif //pragm

