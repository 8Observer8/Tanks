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

#include "Tank.h"
#include <QDebug>

Tank::Tank( QOpenGLShaderProgram *program,
            int vertexAttr, int textureAttr,
            int textureUniform) :
    Plane( program, vertexAttr, textureAttr, textureUniform ),
    m_isReloading( false )
{
    genTextures();
    setDirection( Tank::Up );
}

Tank::~Tank()
{
    for ( size_t i = 0; i < m_upTextures.size(); ++i )
    {
        delete m_upTextures[i];
    }

    for ( size_t i = 0; i < m_downTextures.size(); ++i )
    {
        delete m_downTextures[i];
    }

    for ( size_t i = 0; i < m_rightTextures.size(); ++i )
    {
        delete m_rightTextures[i];
    }

    for ( size_t i = 0; i < m_leftTextures.size(); ++i )
    {
        delete m_leftTextures[i];
    }
}

void Tank::genTextures()
{
    QImage image( ":/Textures/TankSpriteSheet.png" );

    int frameHeight = image.height() / 16;
    int frameWidth = image.width() / 25;

    std::vector<QImage> frames;
    for ( int i = 0; i < 8; ++i )
    {
        QImage frame = image.copy( i * frameWidth, 0, frameWidth, frameHeight );
        QMatrix matrix;
        matrix.rotate( 180.0 );
        frame = frame.transformed( matrix );
        frame = frame.mirrored( true, false );
        frames.push_back( frame );
    }

    m_upTextures.push_back( new QOpenGLTexture( frames[0] ) );
    m_upTextures.push_back( new QOpenGLTexture( frames[1] ) );

    m_leftTextures.push_back( new QOpenGLTexture( frames[2] ) );
    m_leftTextures.push_back( new QOpenGLTexture( frames[3] ) );

    m_downTextures.push_back( new QOpenGLTexture( frames[4] ) );
    m_downTextures.push_back( new QOpenGLTexture( frames[5] ) );

    m_rightTextures.push_back( new QOpenGLTexture( frames[6] ) );
    m_rightTextures.push_back( new QOpenGLTexture( frames[7] ) );
}

Tank::Direction Tank::direction() const
{
    return m_direction;
}

void Tank::setDirection( Tank::Direction dir )
{
    m_direction = dir;

    switch( m_direction )
    {
        case Tank::Up:
            setTexture( m_upTextures[0] );
            break;
        case Tank::Left:
            setTexture( m_leftTextures[0] );
            break;
        case Tank::Down:
            setTexture( m_downTextures[0] );
            break;
        case Tank::Right:
            setTexture( m_rightTextures[0] );
            break;
    }
}

void Tank::nextFrame()
{
    static unsigned int counter = 0;

    switch( m_direction )
    {
        case Tank::Up:
            setTexture( m_upTextures[counter] );
            break;
        case Tank::Left:
            setTexture( m_leftTextures[counter] );
            break;
        case Tank::Down:
            setTexture( m_downTextures[counter] );
            break;
        case Tank::Right:
            setTexture( m_rightTextures[counter] );
            break;
    }

    ++counter;

    if ( counter >= 2 )
        counter = 0;
}

void Tank::shot()
{
    connect( &m_timerOfReloading, SIGNAL( timeout() ),
             this, SLOT( slotStopReloading() ) );
    m_timerOfReloading.start( 500 );
    m_isReloading = true;
}

bool Tank::isReloading() const
{
    return m_isReloading;
}

void Tank::slotStopReloading()
{
    m_timerOfReloading.stop();
    m_isReloading = false;
}
