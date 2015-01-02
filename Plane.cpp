#include "Plane.h"

Plane::Plane( QOpenGLShaderProgram *program, int vertexAttr,
              int textureAttr, int textureUniform) :
    m_program( program ),
    m_vertexAttr( vertexAttr ),
    m_textureAttr( textureAttr ),
    m_textureUniform( textureUniform ),
    m_x0( -0.5f ),
    m_y0( -0.5f ),
    m_size( 1.0f )
{
    initVertices();
    initTextureCoords();
}

Plane::~Plane()
{

}

void Plane::draw()
{
    m_texture->bind();

    m_program->setAttributeArray( m_vertexAttr, m_vertices.data(), 3 );
    m_program->setAttributeArray( m_textureAttr, m_textureCoords.data(), 2 );
    m_program->setUniformValue( m_textureUniform, 0 );

    m_program->enableAttributeArray( m_vertexAttr );
    m_program->enableAttributeArray( m_textureAttr );

    glDrawArrays( GL_TRIANGLES, 0, 6 );

    m_program->disableAttributeArray( m_vertexAttr );
    m_program->disableAttributeArray( m_textureAttr );
}

void Plane::setX0( float x )
{
    m_x0 = x;
    initVertices();
}

void Plane::setY0( float y )
{
    m_y0 = y;
    initVertices();
}

float Plane::x0() const
{
    return m_x0;
}

float Plane::y0() const
{
    return m_y0;
}

void Plane::initVertices()
{
    m_vertices.resize( 18 );

    // 0
    m_vertices[0] = m_x0;
    m_vertices[1] = m_y0;
    m_vertices[2] = 0.0f;

    // 1
    m_vertices[3] = m_x0 + m_size;
    m_vertices[4] = m_y0;
    m_vertices[5] = 0.0f;

    // 2
    m_vertices[6] = m_x0;
    m_vertices[7] = m_y0 + m_size;
    m_vertices[8] = 0.0f;

    // 3
    m_vertices[9] = m_x0;
    m_vertices[10] = m_y0 + m_size;
    m_vertices[11] = 0.0f;

    // 4
    m_vertices[12] = m_x0 + m_size;
    m_vertices[13] = m_y0;
    m_vertices[14] = 0.0f;

    // 5
    m_vertices[15] = m_x0 + m_size;
    m_vertices[16] = m_y0 + m_size;
    m_vertices[17] = 0.0f;
}

void Plane::initTextureCoords()
{
    m_textureCoords.resize( 12 );

    // 0
    m_textureCoords[0] = 0.0f;
    m_textureCoords[1] = 0.0f;

    // 1
    m_textureCoords[2] = 1.0f;
    m_textureCoords[3] = 0.0f;

    // 2
    m_textureCoords[4] = 0.0f;
    m_textureCoords[5] = 1.0f;

    // 3
    m_textureCoords[6] = 0.0f;
    m_textureCoords[7] = 1.0f;

    // 4
    m_textureCoords[8] = 1.0f;
    m_textureCoords[9] = 0.0f;

    // 5
    m_textureCoords[10] = 1.0f;
    m_textureCoords[11] = 1.0f;
}

void Plane::setTexture( QOpenGLTexture *texture )
{
    m_texture = texture;
}
