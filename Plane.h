/*
    The Game Tanks

    Copyright (C) 2014  Enzhaev Ivan

    Email: 8observer8@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLANE_H
#define PLANE_H

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <vector>

class Plane
{
public:
    Plane( QOpenGLShaderProgram *program, int vertexAttr,
           int textureAttr, int textureUniform );
    virtual ~Plane() = 0;

    void draw();

    void setX0( float x );
    float x0() const;

    void setY0( float y );
    float y0() const;

    void setWidth( float width );
    float width() const;

    void setHeight( float height );
    float height() const;

    void setTexture( QOpenGLTexture *texture );

private:
    void initVertices();
    void initTextureCoords();

    std::vector<float> m_vertices;
    std::vector<float> m_textureCoords;

    QOpenGLTexture *m_texture;

    QOpenGLShaderProgram *m_program;
    int m_vertexAttr;
    int m_textureAttr;
    int m_textureUniform;

    float m_x0;
    float m_y0;
    float m_width;
    float m_height;
};

#endif // PLANE_H
