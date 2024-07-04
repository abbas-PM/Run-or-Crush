#include "Entity.hpp"

Entity::Entity(float px, float py, SDL_Texture* ptex, bool pFalling)
    :x(px), y(py), tex(ptex), falling(pFalling)
{
        jumping = false;
        deleted = false; 
}

float Entity::getX()
{
        return x; 
}

float Entity::getY()
{
        return y; 
}

float Entity::getVelX()
{
        return velX; 
}

float Entity::getVelY()
{
        return velY; 
}

bool Entity::getJumping()
{
        return jumping; 
}

bool Entity::getFalling()
{
        return falling; 
}


bool Entity::getDeleted()
{
        return deleted; 
}

int Entity::getType()
{
        return type;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

void Entity::setX(float px)
{
        x = px; 
}

void Entity::setY(float py)
{
        y = py; 
}

void Entity::setVelX(float px)
{
        velX = px; 
}

void Entity::setVelY(float py)
{
        velY = py; 
}

void Entity::setJumping(bool pJumping)
{
	jumping = pJumping;
}

void Entity::setFalling(bool pFalling)
{
	falling = pFalling;
}

void Entity::setDeleted(bool del)
{
        deleted = del;
}

void Entity::setType(int ptype)
{
        type = ptype;
}

float Entity::clamp(float value, float min, float max)
{
        if (value < min)
        {
            value = min; 
        }

        if(value > max)
        {
            value = max; 
        }

        return value; 
}

bool Entity::intersect(SDL_Rect a, SDL_Rect b)
{
	return !(b.x > (a.x + a.w) || (b.x + b.w) < a.x || b.y > (a.y + a.h) || (b.y + b.h) < a.y);
}