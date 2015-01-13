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

#include <QDebug>
#include <QMatrix4x4>
#include <QThreadPool>
#include "Scene.h"
#include "SoundOfShot.h"

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent ),
    m_scale( 0.5f ),
    m_canvasHeight( 700.0f ),
    m_canvasWidth( 700.0f )
{
    QThreadPool::globalInstance()->setMaxThreadCount( 15 );

    setFocusPolicy( Qt::StrongFocus );

    connect( &m_projectileTimer, SIGNAL( timeout() ),
             this, SLOT( slotOfMovingOfProjectiles() ) );
}

Scene::~Scene()
{
    makeCurrent();
    delete m_tank;
    delete m_tank2;
    delete m_ice;

    for ( auto it = m_projectiles.begin(); it != m_projectiles.end(); ++it )
        delete it->second;

    for ( auto it = m_projectileExplosions.begin(); it != m_projectileExplosions.end(); ++it )
        delete it->second;

    for ( auto it = m_tankExplosions.begin(); it != m_tankExplosions.end(); ++it )
        delete it->second;

    doneCurrent();
}

void Scene::slotOfMovingOfProjectiles()
{
    if ( m_projectiles.size() == 0 )
        return;

    const float step = 10.0f;

    for ( auto iterOfProjectile = m_projectiles.begin(); iterOfProjectile != m_projectiles.end(); ++iterOfProjectile )
    {
        Projectile *projectile = iterOfProjectile->second;

        float x0 = projectile->x0();
        float y0 = projectile->y0();

        switch ( projectile->direction() ) {
            case Projectile::Up:
                projectile->setY0( projectile->y0() - step );
                if ( projectile->y0() <= 0.0f )
                {
                    delete projectile;
                    m_projectiles.erase( iterOfProjectile );
                    addProjectileExplosion( x0, y0 );
                }
                break;
            case Projectile::Left:
                projectile->setX0( projectile->x0() - step );
                if ( projectile->x0() < 0.0f )
                {
                    delete projectile;
                    m_projectiles.erase( iterOfProjectile );
                    addProjectileExplosion( x0, y0 );
                }
                break;
            case Projectile::Down:
                projectile->setY0( projectile->y0() + step );
                if ( projectile->y0() >= ( m_canvasHeight - projectile->height() ) )
                {
                    delete projectile;
                    m_projectiles.erase( iterOfProjectile );
                    addProjectileExplosion( x0, y0 );
                }
                break;
            case Projectile::Right:
                projectile->setX0( projectile->x0() + step );
                if ( projectile->x0() > ( m_canvasWidth - projectile->width() ) )
                {
                    delete projectile;
                    m_projectiles.erase( iterOfProjectile );
                    addProjectileExplosion( x0, y0 );
                }
                break;
        }
    }

    update();
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
    m_tank->setX0( m_tank->x0() + 350.0f );
    m_tank->setY0( m_tank->y0() + 350.0f );

    m_tank2 = new Tank( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform );
    m_tank2->setX0( m_tank2->x0() + 400.0f );
    m_tank2->setY0( m_tank2->y0() + 400.0f );

    m_ice = new Ice( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform );
    m_ice->setX0( m_ice->x0() + 500.0f );
    m_ice->setY0( m_ice->y0() + 500.0f );
}

void Scene::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT );

    if ( !m_program.bind() )
        return;

    QMatrix4x4 matrix;
    matrix.ortho( 0.0f, 700.0f, 700.0, 0.0f, -2.0f, 2.0f );
    matrix.scale( m_scale );
    m_program.setUniformValue( m_matrixUniform, matrix );

    m_ice->draw();
    m_tank2->draw();
    m_tank->draw();

    for ( auto it = m_projectiles.begin(); it != m_projectiles.end(); ++it )
        it->second->draw();

//    for ( auto it = m_projectileExplosions.begin(); it != m_projectileExplosions.end(); ++it )
//        it->second->draw();

//    for ( auto it = m_tankExplosions.begin(); it != m_tankExplosions.end(); ++it )
//        it->second->draw();

    m_program.release();
}

void Scene::resizeGL( int w, int h )
{
    glViewport( 0, 0, w, h );
}

void Scene::keyPressEvent( QKeyEvent *event )
{
    const float step = 10.0f;

    switch( event->key() )
    {
        case Qt::Key_Up:
            m_tank->setY0( m_tank->y0() - step );
            m_tank->setDirection( Tank::Up );
            m_tank->nextFrame();
            break;
        case Qt::Key_Left:
            m_tank->setX0( m_tank->x0() - step );
            m_tank->setDirection( Tank::Left );
            m_tank->nextFrame();
            break;
        case Qt::Key_Right:
            m_tank->setX0( m_tank->x0() + step );
            m_tank->setDirection( Tank::Right );
            m_tank->nextFrame();
            break;
        case Qt::Key_Down:
            m_tank->setY0( m_tank->y0() + step );
            m_tank->setDirection( Tank::Down );
            m_tank->nextFrame();
            break;
        case Qt::Key_Space:
            if ( !m_tank->isReloading() )
            {
                m_tank->shot();

                Projectile *projectile = new Projectile( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform );
                float x0, y0;

                switch( m_tank->direction() )
                {
                    case Tank::Up:
                        x0 = m_tank->x0();
                        y0 = m_tank->y0() - projectile->height();
                        projectile->setDirection( Projectile::Up );
                        break;
                    case Tank::Left:
                        x0 = m_tank->x0() - projectile->width();
                        y0 = m_tank->y0();
                        projectile->setDirection( Projectile::Left );
                        break;
                    case Tank::Down:
                        x0 = m_tank->x0();
                        y0 = m_tank->y0() + projectile->height();
                        projectile->setDirection( Projectile::Down );
                        break;
                    case Tank::Right:
                        x0 = m_tank->x0() + m_tank->width();
                        y0 = m_tank->y0();
                        projectile->setDirection( Projectile::Right );
                        break;
                }

                projectile->setX0( x0 );
                projectile->setY0( y0 );
                m_projectileTimer.start( 20 );
                m_projectiles[projectile->id()] = projectile;

//                SoundOfShot *sound = new SoundOfShot;
//                sound->setAutoDelete( true );
//                QThreadPool::globalInstance()->start( sound );
            }

//            if ( m_projectile == 0 )
//            {
//                m_projectile = new Projectile( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform );
//                float x0, y0;

//                switch( m_tank->direction() )
//                {
//                    case Tank::Up:
//                        x0 = m_tank->x0();
//                        y0 = m_tank->y0() - m_projectile->height();
//                        m_projectile->setDirection( Projectile::Up );
//                        break;
//                    case Tank::Left:
//                        x0 = m_tank->x0() - m_projectile->width();
//                        y0 = m_tank->y0();
//                        m_projectile->setDirection( Projectile::Left );
//                        break;
//                    case Tank::Down:
//                        x0 = m_tank->x0();
//                        y0 = m_tank->y0() + m_projectile->height();
//                        m_projectile->setDirection( Projectile::Down );
//                        break;
//                    case Tank::Right:
//                        x0 = m_tank->x0() + m_tank->width();
//                        y0 = m_tank->y0();
//                        m_projectile->setDirection( Projectile::Right );
//                        break;
//                }

//                m_projectile->setX0( x0 );
//                m_projectile->setY0( y0 );

//                m_projectileTimer.start( 5 );

//                // Add timer for reloading

//                SoundOfShot *sound = new SoundOfShot;
//                sound->setAutoDelete( true );
//                QThreadPool::globalInstance()->start( sound );

//                m_effect = new QSoundEffect;
//                m_effect->setSource( QUrl::fromLocalFile( ":/Sounds/Explosion.wav" ) );
                //effect.setLoopCount( QSoundEffect::Infinite) ;
//                m_effect->setVolume( 0.3f );
//                m_effect->play();
//            }
            break;
    }

    update();
}

void Scene::addProjectileExplosion( float x0, float y0 )
{
    ExplosionOfProjectile *explosion = new ExplosionOfProjectile( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform );
    explosion->setX0( x0 );
    explosion->setY0( y0 );
    connect( explosion, SIGNAL( signalShowProjectileExplosion( int, bool ) ),
             this, SLOT( slotShowProjectileExplosion( int, bool ) ) );
    m_projectileExplosions[explosion->id()] = explosion;
    explosion->start();

    update();
}

void Scene::addTankExplosion( float x0, float y0 )
{
    ExplosionOfTank *explosion = new ExplosionOfTank( &m_program, m_vertexAttr, m_textureAttr, m_textureUniform );
    explosion->setX0( x0 );
    explosion->setY0( y0 );
    connect( explosion, SIGNAL( signalShowTankExplosion( int, bool ) ),
             this, SLOT( slotShowTankExplosion( int, bool ) ) );
    m_tankExplosions[explosion->id()] = explosion;
    explosion->start();

    update();
}

void Scene::slotShowProjectileExplosion( int id, bool show )
{
    auto it = m_projectileExplosions.find( id );

    if ( show == false )
    {
        delete it->second;
        m_projectileExplosions.erase( it );
    }

    update();
}

void Scene::slotShowTankExplosion( int id, bool show )
{
    auto it = m_tankExplosions.find( id );

    if ( show == false )
    {
        delete it->second;
        m_tankExplosions.erase( it );
    }

    update();
}
