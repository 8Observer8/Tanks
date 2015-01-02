#include "Tank.h"

Tank::Tank( QOpenGLShaderProgram *program,
            int vertexAttr, int textureAttr,
            int textureUniform) :
    Plane( program, vertexAttr, textureAttr, textureUniform ),
    m_direction( Tank::Right )
{
    genTextures();
    setTexture( m_leftTextures[0] );
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
    QImage image( ":/Texture/TankSpriteSheet.png" );

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
    if ( m_direction == dir )
        return;
    else
        m_direction = dir;
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
