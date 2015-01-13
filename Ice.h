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
