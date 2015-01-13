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

#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QTimer>
#include <QSoundEffect>
#include <map>
#include "Tank.h"
#include "Ice.h"
#include "Projectile.h"
#include "SmallExplosion.h"
#include "ExplosionOfProjectile.h"
#include "ExplosionOfTank.h"

class Scene : public QOpenGLWidget
{
    Q_OBJECT

public:
    Scene( QWidget *parent = 0 );
    ~Scene();

private slots:
    void slotOfMovingOfProjectiles();
    void slotShowProjectileExplosion( int id, bool show );
    void slotShowTankExplosion( int id, bool show );

private:
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    void keyPressEvent( QKeyEvent *event );

    void showProjectileExplosions();

    void addProjectileExplosion( float x0, float y0 );
    void addTankExplosion( float x0, float y0 );

    QOpenGLShaderProgram m_program;

    int m_vertexAttr;
    int m_textureAttr;
    int m_textureUniform;
    int m_matrixUniform;

    Tank *m_tank;
    Tank *m_tank2;
    Ice *m_ice;
    //SmallExplosion *m_smallExplosion;

    float m_scale;

    QTimer m_projectileTimer;

    const float m_canvasHeight;
    const float m_canvasWidth;

    QSoundEffect *m_effect;

    std::map<int, Projectile*> m_projectiles;
    std::map<int, ExplosionOfProjectile*> m_projectileExplosions;
    std::map<int, ExplosionOfTank*> m_tankExplosions;
};

#endif // SCENE_H
