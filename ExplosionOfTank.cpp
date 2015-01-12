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

#include "ExplosionOfTank.h"
#include <QImage>

int ExplosionOfTank::m_nextId = 0;

ExplosionOfTank::ExplosionOfTank( QOpenGLShaderProgram *program,
                                  int vertexAttr, int textureAttr,
                                  int textureUniform ) :
    Plane( program, vertexAttr, textureAttr, textureUniform )
{
    m_id = m_nextId++;

    genTextures();

    setTexture( m_textures[0] );
}

ExplosionOfTank::~ExplosionOfTank()
{
    for ( size_t i = 0; i < m_textures.size(); ++i )
        delete m_textures[i];
}

void ExplosionOfTank::start()
{
    connect( &m_timer, SIGNAL( timeout() ),
             this, SLOT( slotShowTankExplosion() ) );
    m_timer.start( 50 );
}

int ExplosionOfTank::id() const
{
    return m_id;
}

void ExplosionOfTank::slotShowTankExplosion()
{
    static unsigned int counter = 0;

    if ( counter != m_textures.size() )
    {
        setTexture( m_textures[counter] );
        emit signalShowTankExplosion( m_id, true );
        ++counter;
    }
    else
    {
        emit signalShowTankExplosion( m_id, false );
        counter = 0;
    }
}

void ExplosionOfTank::genTextures()
{
    QImage image( ":/Texture/TankSpriteSheet.png" );
    image = image.mirrored( false, true );

    QImage frame;

    frame = image.copy( 257, 112, 15, 15 );
    m_textures.push_back( new QOpenGLTexture( frame ) );

    frame = image.copy( 272, 112, 16, 16 );
    m_textures.push_back( new QOpenGLTexture( frame ) );

    frame = image.copy( 287, 111, 18, 18 );
    m_textures.push_back( new QOpenGLTexture( frame ) );
}
