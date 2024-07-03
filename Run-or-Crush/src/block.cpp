#include "Block.hpp"

Block::Block(float px, float py, SDL_Texture* ptex, bool pFalling)
    :Entity{px, py, ptex, pFalling}
{
    setType(1);
}

//Update function.
void Block::update()
{
    setY(getY() + getVelY());
    setY(clamp(getY(), -96, 672));

    if(getY() == 672)
    {
        setFalling(false); 
        setVelY(0);
    }

    if(getFalling())
    {
        setVelY(6);
    }
}

//Render function.
void Block::render(SDL_Renderer* renderer)
{
    SDL_Rect src; 
	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;

	SDL_Rect dst;
	dst.x = getX();
	dst.y = getY();
	dst.w = src.w * 3;
	dst.h = src.h * 3;

	SDL_RenderCopy(renderer, getTex(), &src, &dst);
}

//Hitboxes.
SDL_Rect Block::getBounds()
{
	int width = 96; 
	int height = 96; 

	SDL_Rect rect; 
	rect.x = (int)(getX()+(width/2)-((width/2)/2))-19;
    rect.y = (int)getY()+(height/2);
    rect.w = width-11; 
    rect.h = height/2;

	return rect; 
}

SDL_Rect Block::getBoundsTop()
{
	int width = 96; 
	int height = 96; 

	SDL_Rect rect; 
	rect.x = (int)(getX()+(width/2)-((width/2)/2))-19;
    rect.y = (int)getY();
    rect.w = width-11; 
    rect.h = height/2; 

	return rect; 
}

SDL_Rect Block::getBoundsLeft()
{
	int width = 96; 
	int height = 96; 

	SDL_Rect rect; 
	rect.x = getX();
    rect.y = getY();
    rect.w = 7; 
    rect.h = height; 

	return rect; 
}

SDL_Rect Block::getBoundsRight()
{
	int width = 96; 
	int height = 96; 

	SDL_Rect rect; 
	rect.x = (int)getX()+width-7;
    rect.y = (int)getY();
    rect.w = 7; 
    rect.h = height; 

	return rect; 
}

//Function to check collision.
void Block::Collision(std::vector<Entity*> handler)
{
    bool onTop = false; 

    for(int i = 0; i < handler.size(); i++)
    {
        Entity* tempObject = handler[i];

        if(tempObject->getType() == 1 && tempObject != this)
        {
            if(intersect(getBounds(), tempObject->getBoundsTop()))
            {
                onTop = true;
                setY(tempObject->getY() - 96);
                setFalling(false);
                setVelY(0);
            }
        }
    }

    if(getY() != 672 || !onTop) setFalling(true);

}