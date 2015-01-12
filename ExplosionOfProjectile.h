/*
    The Game Tanks

    Copyright (C) 2014  Enzhaev Ivan

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

#ifndef EXPLOSIONOFPROJECTILE_H
#define EXPLOSIONOFPROJECTILE_H

#include <QTimer>
#include <QObject>
#include "Plane.h"
#include <vector>

class ExplosionOfProjectile : public QObject, public Plane
{
    Q_OBJECT

public:
    ExplosionOfProjectile( QOpenGLShaderProgram *program, int vertexAttr,
                           int textureAttr, int textureUniform );
    ~ExplosionOfProjectile();

    void start();

    int id() const;

signals:
    void signalShowProjectileExplosion( int id, bool show );

private slots:
    void slotShowProjectileExplosion();

private:
    void genTextures();
    std::vector<QOpenGLTexture*> m_textures;
    QTimer m_timer;
    int m_id;
    static int m_nextId;
};

#endif // EXPLOSIONOFPROJECTILE_H
