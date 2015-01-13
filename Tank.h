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

#ifndef TANK_H
#define TANK_H

#include <QTimer>
#include <QObject>
#include "Plane.h"
#include <vector>

class Tank : public QObject, public Plane
{
    Q_OBJECT

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

    void shot();
    bool isReloading() const;

private slots:
    void slotStopReloading();

private:
    void genTextures();

    std::vector<QOpenGLTexture*> m_upTextures;
    std::vector<QOpenGLTexture*> m_downTextures;
    std::vector<QOpenGLTexture*> m_rightTextures;
    std::vector<QOpenGLTexture*> m_leftTextures;

    Direction m_direction;

    bool m_isReloading;
    QTimer m_timerOfReloading;
};

#endif // TANK_H
