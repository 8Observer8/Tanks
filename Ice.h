#ifndef ICE_H
#define ICE_H

#include "Plane.h"

class Ice : public Plane
{
public:
    Ice( QOpenGLShaderProgram *program,
         int vertexAttr,
         int textureAttr,
         int textureUniform );
    ~Ice();

private:
    QOpenGLTexture *m_texture;
};

#endif // ICE_H
