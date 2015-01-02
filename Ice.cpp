#include <QPixmap>
#include "Ice.h"

Ice::Ice( QOpenGLShaderProgram *program,
          int vertexAttr, int textureAttr,
          int textureUniform ) :
    Plane( program, vertexAttr, textureAttr, textureUniform )
{
    m_texture = new QOpenGLTexture( QImage( ":/Texture/Ice.jpg" ) );
    setTexture( m_texture );
}

Ice::~Ice()
{
    delete m_texture;
}
