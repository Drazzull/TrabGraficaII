#include <GL/glew.h>
#include "GLWidget.h"
#include <iostream>
#include <cmath>
#include <QKeyEvent>
#include <QTimer>

static GLuint texName;

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent), width(1920), height(1080), max_fps(60)
{
    resize(this->width, this->height);
    QTimer::singleShot(1000/max_fps, this, SLOT(tick()));
}
