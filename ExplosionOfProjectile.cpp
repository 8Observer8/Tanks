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

#include "ExplosionOfProjectile.h"
#include <QDebug>
#include <QImage>

int ExplosionOfProjectile::m_nextId = 0;

ExplosionOfProjectile::ExplosionOfProjectile( QOpenGLShaderProgram *program,
                                              int vertexAttr, int textureAttr,
                                              int textureUniform ) :
    Plane( program, vertexAttr, textureAttr, textureUniform )
{
    m_id = m_nextId++;

    genTextures();

    setTexture( m_textures[0] );
}

ExplosionOfProjectile::~ExplosionOfProjectile()
{
    for ( size_t i = 0; i < m_textures.size(); ++i )
        delete m_textures[i];
}

void ExplosionOfProjectile::start()
{
    connect( &m_timer, SIGNAL( timeout() ),
             this, SLOT( slotShowProjectileExplosion() ) );
    m_timer.start( 50 );
}

int ExplosionOfProjectile::id() const
{
    return m_id;
}

void ExplosionOfProjectile::slotShowProjectileExplosion()
{
    static unsigned int counter = 0;

    if ( counter != m_textures.size() )
    {
        setTexture( m_textures[counter] );
        emit signalShowProjectileExplosion( m_id, true );
        ++counter;
    }
    else
    {
        emit signalShowProjectileExplosion( m_id, false );
        counter = 0;
    }
}

void ExplosionOfProjectile::genTextures()
{
    QImage image( ":/Textures/TankSpriteSheet.png" );
    image = image.mirrored( false, true );

    QImage frame;

    frame = image.copy( 257, 112, 15, 15 );
    m_textures.push_back( new QOpenGLTexture( frame ) );

    frame = image.copy( 272, 112, 16, 16 );
    m_textures.push_back( new QOpenGLTexture( frame ) );

    frame = image.copy( 287, 111, 18, 18 );
    m_textures.push_back( new QOpenGLTexture( frame ) );
}
