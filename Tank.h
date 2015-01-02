#ifndef TANK_H
#define TANK_H

#include "Plane.h"
#include <vector>

class Tank : public Plane
{
public:
    Tank( QOpenGLShaderProgram *program,
          int vertexAttr,
          int textureAttr,
          int textureUniform );
    ~Tank();

    enum Direction { Up, Down, Left, Right };

    Direction direction() const;
    void setDirection( Direction dir );

    void nextFrame();

private:
    void genTextures();

    std::vector<QOpenGLTexture*> m_upTextures;
    std::vector<QOpenGLTexture*> m_downTextures;
    std::vector<QOpenGLTexture*> m_rightTextures;
    std::vector<QOpenGLTexture*> m_leftTextures;

    Direction m_direction;
};

#endif // TANK_H
