#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "Tank.h"
#include "Ice.h"

class Scene : public QOpenGLWidget
{
    Q_OBJECT

public:
    Scene( QWidget *parent = 0 );
    ~Scene();

private:
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    void keyPressEvent( QKeyEvent *event );

    QOpenGLShaderProgram m_program;

    int m_vertexAttr;
    int m_textureAttr;
    int m_textureUniform;
    int m_matrixUniform;

    Tank *m_tank;
    Tank *m_tank2;
    Ice *m_ice;

    float m_scale;
};

#endif // SCENE_H
