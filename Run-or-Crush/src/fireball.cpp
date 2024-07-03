#include "Fireball.hpp"

Fireball::Fireball(float px, float py, SDL_Texture* ptex, float pvelX, bool pFalling)
    :Entity{px, py, ptex, pFalling}
{
		setVelX(pvelX);
		setType(2);
}

//Update function.
void Fireball::update()
{
		setX(getX() + getVelX());

		if(getX() > 768 || getX() < -5)
		{
			this->setDeleted(true);
		}
}

//Render function.
void Fireball::render(SDL_Renderer* renderer)
{
		SDL_Rect src; 
		src.x = 0;
		src.y = 0;
		src.w = 32;
		src.h = 32;

		SDL_Rect dst;
		dst.x = getX();
		dst.y = getY();
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, getTex(), &src, &dst);
}

//Hitboxes.
SDL_Rect Fireball::getBounds()
{
		int width = 32; 
		int height = 32; 

		SDL_Rect rect; 
		rect.x = (int)(getX()+(width/2)-((width/2)/2))-3;
		rect.y = (int)getY()+(height/2);
		rect.w = width-11; 
		rect.h = height/2; 

		return rect; 
}

SDL_Rect Fireball::getBoundsTop()
{
		int width = 32; 
		int height = 32; 

		SDL_Rect rect; 
		rect.x = (int)(getX()+(width/2)-((width/2)/2))-3;
		rect.y = (int)getY();
		rect.w = width-11; 
		rect.h = height/2; 

		return rect; 
}

SDL_Rect Fireball::getBoundsLeft()
{
		int width = 32; 
		int height = 32; 

		SDL_Rect rect; 
		rect.x = getX()+2;
		rect.y = getY();
		rect.w = 5; 
		rect.h = height; 

		return rect; 
}

SDL_Rect Fireball::getBoundsRight()
{
		int width = 32; 
		int height = 32; 

		SDL_Rect rect; 
		rect.x = (int)getX()+width-8;
		rect.y = (int)getY();
		rect.w = 5; 
		rect.h = height; 

		return rect; 
}

//Function to check collision.
void Fireball::Collision(std::vector<Entity*> handler)
{
		for(int i = 0; i < handler.size(); i++)
		{
			Entity* tempObject = handler[i];

			if(tempObject->getType() == 1)
			{
				if(intersect(getBoundsRight(), tempObject->getBoundsLeft()) || intersect(getBoundsLeft(), tempObject->getBoundsRight()) 
				|| intersect(getBoundsTop(), tempObject->getBounds()) || intersect(getBounds(), tempObject->getBoundsTop()))
				{
					setDeleted(true);
					tempObject->setDeleted(true);
				}
			}
		}
}