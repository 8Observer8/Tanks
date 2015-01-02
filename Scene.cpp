#include <QMatrix4x4>
#include "Scene.h"

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent ),
    m_scale( 0.5f )
{
    setFocusPolicy( Qt::StrongFocus );
}

Scene::~Scene()
{
    makeCurrent();
    delete m_tank;
    delete m_tank2;
    doneCurrent();
}

void Scene::initializeGL()
{
    glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );
    //glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_BLEND );

    QOpenGLShader vShader( QOpenGLShader::Vertex );
    vShader.compileSourceFile( ":/Shaders/vShader.glsl" );

    QOpenGLShader fShader( QOpenGLShader::Fragment );
    fShader.compileSourceFile( ":/Shaders/fShader.glsl" );

    m_program.addShader( &vShader );
    m_program.addShader( &fShader );
    if ( !m_program.link() )
    {
        qWarning( "Error: unable to link a shader program." );
        return;
    }

    m_vertexAttr = m_program.attributeLocation( "vertexAttr" );
    m_textureAttr = m_program.attributeLocation( "textureAttr" );
    m_textureUniform = m_program.uniformLocation( "textureUniform" );
    m_matrixUniform = m_program.uniformLocation( "matrix" );

    m_tank = new Tank( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform );

    m_tank2 = new Tank( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform );

    m_ice = new Ice( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform );
    m_ice->setX0( m_ice->x0() + 1.0f );
}

void Scene::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT );

    if ( !m_program.bind() )
        return;

    QMatrix4x4 matrix;
    matrix.ortho( -2.0f, 2.0f, -2.0f, 2.0f, 2.0f, -2.0f );
    matrix.scale( m_scale );
    m_program.setUniformValue( m_matrixUniform, matrix );

    m_ice->draw();
    m_tank2->draw();
    m_tank->draw();

    m_program.release();
}

void Scene::resizeGL( int w, int h )
{
    glViewport( 0, 0, w, h );
}

void Scene::keyPressEvent( QKeyEvent *event )
{
    const float step = 0.1f;

    switch( event->key() )
    {
        case Qt::Key_Up:
            m_tank->setY0( m_tank->y0() + step );
            m_tank->setDirection( Tank::Up );
            break;
        case Qt::Key_Left:
            m_tank->setX0( m_tank->x0() - step );
            m_tank->setDirection( Tank::Left );
            break;
        case Qt::Key_Right:
            m_tank->setX0( m_tank->x0() + step );
            m_tank->setDirection( Tank::Right );
            break;
        case Qt::Key_Down:
            m_tank->setY0( m_tank->y0() - step );
            m_tank->setDirection( Tank::Down );
            break;
    }

    m_tank->nextFrame();
    update();
}
