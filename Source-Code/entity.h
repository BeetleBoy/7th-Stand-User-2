#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include "AnimatedSprite.hpp"
#include "PauseableClock.cpp"
#include <string.h>
#include <tgmath.h>

class MapSprite : public sf::Drawable, sf::Transformable
{
public:
    std::string mapName;
    MapSprite()
    {
        mapName = "";
        bbox.clear();
        m_vertices.clear();
        bbox.clear();
        ceil.clear();
        bboxcount = 0;
    };
    MapSprite &clear(MapSprite &container)
    {
        MapSprite empty;
        using std::swap;
        swap(empty, container);
        return container;
    }
    sf::FloatRect getbbox(int i)
    {
        sf::FloatRect bb;
        bb = bbox.at(i).getGlobalBounds();
        return bb;
    }

    int getbboxcount(void)
    {
        return bboxcount;
    }

    void drawCeil(sf::RenderWindow *target)
    {
        if (!ceil.empty())
        for (unsigned int i = 0; i < ceil.size(); i++)
        {
            target->draw(ceil[i]);
        }
    }

    bool load(const std::string& mapimage, sf::Vector2u tileSize, unsigned int width, unsigned int height)
    {
        if (!m_tileset.loadFromFile(mapimage))
            return false;

        bboxcount = 0;
        if (mapimage.compare("Maps/hirosehouse1f.png") == 0)
        {
            //1 =  32
            //2 =  64
            //3 =  96
            //4 = 128
            //5 = 160
            //6 = 192
            //7 = 224
            //8 = 256
            //9 = 288
            //10= 320
            //11= 352
            //12= 384
            //13= 416
            //14= 448
            mapName = "Hirose Residence, 1F";
            for (unsigned int i = 0; i < mapName.length(); i++)
            {
                printf("%c", mapName[i]);
            }
            printf("\n");
            int bsiz[2][36] =   {{ 448,  32,  32, 192,  64,  64, 224, 160, 192,  96,  64, 384,  32,  32,  32,  96, 128, 288, 288,  96,  32,  32, 128,  32,  32, 224,  32,  32,  32, 602,  32,  64,  32,  32,  32,  32},
                                 { 128, 288,  32,  32,  64, 160, 128, 128,  96,  96,  96, 128,  64,  32,  32, 128, 128, 128, 128, 128, 384, 192, 128,  96,  32, 128,  64, 128, 128, 128, 128,  32, 128, 224,  32, 192}};
            int bpos[2][36] =   {{  32,  32,  32, 224, 288, 416,  64, 320, 480, 480, 608, 672,1024, 640, 768,  32, 160, 320, 640, 960,  32, 192,  64, 224, 224, 224, 352, 416, 448, 448, 800, 928,1024, 192, 416, 448},
                                 {  64, 192, 512, 192, 256, 192, 352, 352, 288, 384, 384, 352, 480, 480, 512, 544, 544, 544, 544, 544, 672, 672, 928, 736, 992,1024, 864, 704, 672, 800, 672, 768, 672, 896, 992, 928}};
            bboxcount = 36;
            for (int i = 0; i < bboxcount; i++)
            {
                sf::Vector2f s, p;
                s.x = bsiz[0][i];
                s.y = bsiz[1][i];
                p.x = bpos[0][i];
                p.y = bpos[1][i];
                sf::Sprite bb;
                bb.setPosition(p);
                bb.setTextureRect(sf::IntRect(0, 0, s.x, s.y));
                bbox.push_back(bb);
            }
            int csiz[2][8] =   {{  32,  32,  32,  32,  32,  32,  32,  32},
                                {  32,  32,  32,  64,  64,  64,  64,  64}};
            int cpos[2][8] =   {{  32, 192, 576, 288, 128, 288, 608, 928},
                                { 480, 864, 384, 352, 544, 544, 544, 544}};
            for (int i = 0; i < 8; i++)
            {
                sf::Vector2f s, p;
                s.x = csiz[0][i];
                s.y = csiz[1][i];
                p.x = cpos[0][i];
                p.y = cpos[1][i];
                sf::Sprite ce;
                ce.setPosition(p);
                ce.setTexture(m_tileset);
                ce.setTextureRect(sf::IntRect(p.x, p.y, s.x, s.y));
                ceil.push_back(ce);
            }
        }
        else if (mapimage.compare("Maps/hirosehouse2f.png") == 0)
        {
            mapName = "Hirose Residence, 2F";
            for (unsigned int i = 0; i < mapName.length(); i++)
            {
                printf("%c", mapName[i]);
            }
            printf("\n");
        }
        else if (mapimage.compare("Maps/hirosehouse3f.png") == 0)
        {
            mapName = "Hirose Residence, 3F";
            for (unsigned int i = 0; i < mapName.length(); i++)
            {
                printf("%c", mapName[i]);
            }
            printf("\n");
        }
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                //int tileNumber = i + (j * width);
                // find its position in the tileset texture
                //cout << "tu = " << tu << "\ntv = " << tv << endl;
                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(floor(i * tileSize.x), floor(j * tileSize.y));
                quad[1].position = sf::Vector2f(floor((i + 1) * tileSize.x), floor(j * tileSize.y));
                quad[2].position = sf::Vector2f(floor((i + 1) * tileSize.x), floor((j + 1) * tileSize.y));
                quad[3].position = sf::Vector2f(floor(i * tileSize.x), floor((j + 1) * tileSize.y));

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(floor(i * tileSize.x), floor(j * tileSize.y));
                quad[1].texCoords = sf::Vector2f(floor((i + 1) * tileSize.x), floor(j * tileSize.y));
                quad[2].texCoords = sf::Vector2f(floor((i + 1) * tileSize.x), floor((j + 1) * tileSize.y));
                quad[3].texCoords = sf::Vector2f(floor(i * tileSize.x), floor((j + 1) * tileSize.y));
            }

        return true;
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    std::vector<sf::Sprite> bbox;
    std::vector<sf::Sprite> ceil;
    int bboxcount;
};

class Entity
{
public:
    sf::Texture texture;
    int x;
    int y;
    int w;
    int h;

    void setTexture(std::string);
    void setPos(int, int);
    void setSize(int, int);
};

class MovingSprite : public Entity, public AnimatedSprite
{
public:
    int xOffset;
    int yOffset;
    Animation walkU;
    Animation walkD;
    Animation walkL;
    Animation walkR;
    Animation *currentAnimation;
    float speed;
    bool noKeyWasPressed;
    bool walking;
    bool moving[4];
    int nextSpot;
    int holdCount;
    sf::Vector2f old_pos;
    sfuser::PauseableClock frameClock;
    void setOffset(int, int);
    void setAnimations(void);
    void move_overworld(MapSprite&);
};

class StaticSprite : public Entity
{
public:
    sf::Sprite sprite;
};

void Entity::setTexture(std::string filename)
{
    texture.loadFromFile(filename);
}

void Entity::setSize(int wS, int hS)
{
    w = wS;
    h = hS;
}

void MovingSprite::setOffset(int xO, int yO)
{
    xOffset = w+(w*3*xO);
    yOffset = h*4*yO;
}

void MovingSprite::setAnimations(void)
{
    walkD = Animation();
    walkD.setSpriteSheet(texture);
    walkD.addFrame(sf::IntRect( xOffset+1,    yOffset,     w, h));
    walkD.addFrame(sf::IntRect( xOffset+w+1, yOffset,     w, h));
    walkD.addFrame(sf::IntRect( xOffset+1,    yOffset,     w, h));
    walkD.addFrame(sf::IntRect( xOffset-w+1, yOffset,     w, h));
    walkL = Animation();
    walkL.setSpriteSheet(texture);
    walkL.addFrame(sf::IntRect( xOffset,    yOffset+h,  w, h));
    walkL.addFrame(sf::IntRect( xOffset+w, yOffset+h,  w, h));
    walkL.addFrame(sf::IntRect( xOffset,    yOffset+h,  w, h));
    walkL.addFrame(sf::IntRect( xOffset-w, yOffset+h,  w, h));
    walkR = Animation();
    walkR.setSpriteSheet(texture);
    walkR.addFrame(sf::IntRect(xOffset,    yOffset+(2*h),  w, h));
    walkR.addFrame(sf::IntRect(xOffset+w, yOffset+(2*h),  w, h));
    walkR.addFrame(sf::IntRect(xOffset,    yOffset+(2*h),  w, h));
    walkR.addFrame(sf::IntRect(xOffset-w, yOffset+(2*h),  w, h));
    walkU = Animation();
    walkU.setSpriteSheet(texture);
    walkU.addFrame(sf::IntRect(   xOffset,    yOffset+(3*h), w, h));
    walkU.addFrame(sf::IntRect(   xOffset+w, yOffset+(3*h), w, h));
    walkU.addFrame(sf::IntRect(   xOffset,    yOffset+(3*h), w, h));
    walkU.addFrame(sf::IntRect(   xOffset-w, yOffset+(3*h), w, h));

    speed = 96.0f;
    currentAnimation = &walkD;
    setAnimation(walkD);
    setFrameTime(sf::seconds(0.16f));
    noKeyWasPressed = true;
    walking = false;
    moving[0] = false;
    moving[1] = false;
    moving[2] = false;
    moving[3] = false;
    holdCount = 0;
    frameClock.start();
    nextSpot = 0;
}

void MovingSprite::move_overworld (MapSprite &map)
{
    sf::Time frameTime = frameClock.restart();
    // if a key was pressed set the correct animation and move correctly
    sf::Vector2f movement(0.f, 0.f);
    if (!walking)
    {
        old_pos = getPosition();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (walking == false)
        {
            if (currentAnimation == &walkU)
            {
                if (holdCount > 60)
                {
                    nextSpot = getPosition().y - 32;
                    moving[0] = true;
                    walking = true;
                    movement.y -= speed;
                }
                holdCount++;
            }
            else
            {
                currentAnimation = &walkU;
                holdCount = 0;
            }
        }
        noKeyWasPressed = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (walking == false)
        {
            if (currentAnimation == &walkD)
            {
                if (holdCount > 60)
                {
                    nextSpot = getPosition().y + 32;
                    moving[1] = true;
                    walking = true;
                    movement.y += speed;
                }
                holdCount++;
            }
            else
            {
                currentAnimation = &walkD;
                holdCount = 0;
            }
        }
        noKeyWasPressed = false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (walking == false)
        {
            if (currentAnimation == &walkL)
            {
                if (holdCount > 60)
                {
                    nextSpot = getPosition().x - 32;
                    moving[2] = true;
                    walking = true;
                    movement.x -= speed;
                }
                holdCount++;
            }
            else
            {
                currentAnimation = &walkL;
                holdCount = 0;
            }
        }
        noKeyWasPressed = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (walking == false)
        {
            if (currentAnimation == &walkR)
            {
                if (holdCount > 60)
                {
                    nextSpot = getPosition().x + 32;
                    moving[3] = true;
                    walking = true;
                    movement.x += speed;
                }
                holdCount++;
            }
            else
            {
                currentAnimation = &walkR;
                holdCount = 0;
            }
        }
        noKeyWasPressed = false;
    }
    play(*currentAnimation);
    if (walking == true)
    {
        if (moving[0] == true)
        {
            movement.y -= speed;
            movement *= frameTime.asSeconds();
            move(movement.x, movement.y);
            if (getPosition().y <= nextSpot)
            {
                setPosition(getPosition().x, nextSpot);
                walking = false;
                moving[0] = false;
            }
            for (int i = 0; i < map.getbboxcount(); i++)
            {
                if (getGlobalBounds().intersects(map.getbbox(i)))
                {
                    setPosition(old_pos);
                    walking = false;
                    noKeyWasPressed = true;
                    moving[0] = false;
                }
            }
        }
        if(moving[1] == true)
        {
            movement.y = speed;
            movement *= frameTime.asSeconds();
            move(movement);
            if(getPosition().y >= nextSpot)
            {
                setPosition(getPosition().x, nextSpot);
                walking = false;
                moving[1] = false;
            }
            for (int i = 0; i < map.getbboxcount(); i++)
            {
                if (getGlobalBounds().intersects(map.getbbox(i)))
                {
                    setPosition(old_pos);
                    walking = false;
                    noKeyWasPressed = true;
                    moving[1] = false;
                }
            }
        }
        if(moving[2] == true)
        {
            movement.x -= speed;
            movement *= frameTime.asSeconds();
            move(movement);
            if(getPosition().x <= nextSpot)
            {
                setPosition(nextSpot, getPosition().y);
                walking = false;
                moving[2] = false;
            }
            for (int i = 0; i < map.getbboxcount(); i++)
            {
                if (getGlobalBounds().intersects(map.getbbox(i)))
                {
                    setPosition(old_pos);
                    walking = false;
                    noKeyWasPressed = true;
                    moving[2] = false;
                }
            }
        }
        if(moving[3] == true)
        {
            movement.x = speed;
            movement *= frameTime.asSeconds();
            move(movement);
            if(getPosition().x >= nextSpot)
            {
                setPosition(nextSpot, getPosition().y);
                walking = false;
                moving[3] = false;
            }
            for (int i = 0; i < map.getbboxcount(); i++)
            {
                if (getGlobalBounds().intersects(map.getbbox(i)))
                {
                    setPosition(old_pos);
                    walking = false;
                    noKeyWasPressed = true;
                    moving[3] = false;
                }
            }
        }
    }

    if (!walking)
    {
        moving[0] = false;
        moving[1] = false;
        moving[2] = false;
        moving[3] = false;
    }
    if (noKeyWasPressed && !walking)
    {
        stop();
    }
    noKeyWasPressed = true;
    // update AnimatedSprite
    update(frameTime);
    return;
}


#endif // ENTITY_H_INCLUDED
