#pragma once

#include "vetor.h"
#include <QGLWidget>
#include <QMouseEvent>

#define PI 3.141592

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget* parent = 0);
    ~GLWidget();
}
