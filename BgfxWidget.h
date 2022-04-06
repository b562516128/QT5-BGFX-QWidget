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
    virtual void mousePressEvent(QMouseEvent* event) override; // ��������
    virtual void mouseReleaseEvent(QMouseEvent* event) override; // �����ɿ�
    virtual void mouseMoveEvent(QMouseEvent* event) override; // ����ƶ�
    virtual void enterEvent(QEvent* event) override; // �����봰��
    virtual void leaveEvent(QEvent* event) override; // ����뿪����
    virtual void wheelEvent(QWheelEvent* event) override; // �������ƶ�
    virtual void focusInEvent(QFocusEvent* event) override; // ��ý���
    virtual void focusOutEvent(QFocusEvent* event) override; // �ͷŽ���
    virtual void paintEvent(QPaintEvent* event) override; // �����ػ�

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

