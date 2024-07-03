#include "Player.hpp"
#include "Fireball.hpp"

Player::Player(float px, float py, SDL_Texture* ptex, bool pFalling)
    :Entity{px, py, ptex, pFalling}
{
	gravity = 0.3f;
	MAX_SPEED = 10;
	fireballs = 10;
	direction = 1;
	creating = false;
	crushed = false;
	setType(0);
}

//Update function.
void Player::update()
{
	setX(getX() + getVelX());
	setY(getY() + getVelY());

	if(getVelX() > 0) direction = 1; 
	else if(getVelX() < 0) direction = 0; 

	setX(clamp(getX(), -15, 720));
	setY(clamp(getY(), 0, 704));
	setFireballs(clamp(getFireballs(), 0, 99));	

	if(getY() == 0) setVelY(0);
	
	if(getY() == 704)
	{
		setJumping(false);
		setFalling(false);
	}

	if(getFalling() || getJumping())
	{
		setVelY(getVelY() + gravity);
		if(getVelY() > MAX_SPEED) setVelY(MAX_SPEED); 
	}
}

//Render function.
void Player::render(SDL_Renderer* renderer)
{
	if(getJumping() || getFalling())
	{
		SDL_Rect src; 
		if(direction == 1) src.x = 4 * 32;
		else if(direction == 0) src.x = 10 * 32;
		src.y = 0;
		src.w = 32;
		src.h = 32;

		SDL_Rect dst;
		dst.x = getX();
		dst.y = getY();
		dst.w = src.w * 2;
		dst.h = src.h * 2;

		SDL_RenderCopy(renderer, getTex(), &src, &dst);
	}

	else if(creating)
	{
		Uint32 seconds = SDL_GetTicks() / 200; 
		Uint32 sprite = (seconds % 3) + 12; 

		SDL_Rect src; 
		src.x = sprite * 32;
		src.y = 0;
		src.w = 32;
		src.h = 32;

		SDL_Rect dst;
		dst.x = getX();
		dst.y = getY();
		dst.w = src.w * 2;
		dst.h = src.h * 2;

		SDL_RenderCopy(renderer, getTex(), &src, &dst);
	} 
	
	else
	{
		if(getVelX() > 0)
		{
			Uint32 seconds = SDL_GetTicks() / 200; 
			Uint32 sprite = seconds % 4; 

			SDL_Rect src; 
			src.x = sprite * 32;
			src.y = 0;
			src.w = 32;
			src.h = 32;

			SDL_Rect dst;
			dst.x = getX();
			dst.y = getY();
			dst.w = src.w * 2;
			dst.h = src.h * 2;

			SDL_RenderCopy(renderer, getTex(), &src, &dst);
		}
		else if (getVelX() < 0)
		{
			Uint32 seconds = SDL_GetTicks() / 200; 
			Uint32 sprite = (seconds % 4) + 6; 

			SDL_Rect src; 
			src.x = sprite * 32;
			src.y = 0;
			src.w = 32;
			src.h = 32;

			SDL_Rect dst;
			dst.x = getX();
			dst.y = getY();
			dst.w = src.w * 2;
			dst.h = src.h * 2;

			SDL_RenderCopy(renderer, getTex(), &src, &dst);
		}
		else
		{
			SDL_Rect src; 
			if(direction == 1) src.x = 0;
			else if(direction == 0) src.x = 6 * 32;
			src.y = 0;
			src.w = 32;
			src.h = 32;

			SDL_Rect dst;
			dst.x = getX();
			dst.y = getY();
			dst.w = src.w * 2;
			dst.h = src.h * 2;

			SDL_RenderCopy(renderer, getTex(), &src, &dst);
		}
	}
}

//Hitboxes.
SDL_Rect Player::getBounds()
{
	int width = 64; 
	int height = 64; 

	SDL_Rect rect; 
	rect.x = (int)(getX()+(width/2)-((width/2)/2))-2;
	rect.y = (int)getY()+(height/2);
	rect.w = width-30; 
	rect.h = height/2; 

	return rect; 
}

SDL_Rect Player::getBoundsTop()
{
	int width = 64; 
	int height = 64; 

	SDL_Rect rect; 
	rect.x = (int)(getX()+(width/2)-((width/2)/2))-2;
	rect.y = (int)getY();
	rect.w = width-30; 
	rect.h = height/2; 

	return rect; 
}

SDL_Rect Player::getBoundsLeft()
{
	int width = 64; 
	int height = 64; 

	SDL_Rect rect; 
	rect.x = (int)getX() + 11;
	rect.y = (int)getY();
	rect.w = 5; 
	rect.h = height - 11; 

	return rect; 
}

SDL_Rect Player::getBoundsRight()
{
	int width = 64; 
	int height = 64; 

	SDL_Rect rect; 
	rect.x = (int)getX()+width - 18;
	rect.y = (int)getY();
	rect.w = 5; 
	rect.h = height - 11; 

	return rect; 
}

//Getters and Setters.
void Player::setCreating(bool pCreating)
{
	creating = pCreating;
}

void Player::setFireballs(int pFireballs)
{
	fireballs = pFireballs;
}

bool Player::getCreating()
{
	return creating;
}

int Player::getFireballs()
{
	return fireballs; 
}

bool Player::getCrushed()
{
	return crushed;
}

//Function used when a new game is started.
void Player::playerReset()
{
	setX(50);
    setY(736);
    setFalling(false);
    setJumping(false);
    fireballs = 10; 
	direction = 1;
	creating = false;
	crushed = false;
}

//Function to check collision.
void Player::Collision(std::vector<Entity*> handler)
{
	bool onTop = false; 

	for(int i = 0; i < handler.size(); i++)
	{
		Entity* tempObject = handler[i];

		if(tempObject->getType() == 1)
		{
			if(intersect(getBoundsLeft(), tempObject->getBoundsRight()))
			{
				setX(tempObject->getX() + 85);
			}

			if(intersect(getBoundsRight(), tempObject->getBoundsLeft()))
			{
				setX(tempObject->getX() - 50);
			}

			if(intersect(getBounds(), tempObject->getBoundsTop()))
			{
				onTop = true; 
				setY(tempObject->getY() - 64);
				setVelY(tempObject->getVelY());
				setJumping(false);
				setFalling(false);
			}

			if(intersect(getBoundsTop(), tempObject->getBounds()))
			{
				setJumping(false);
				setFalling(true);
				setVelY(tempObject->getVelY());
				setY(tempObject->getY() + 96);	

				if(onTop || getY() >= 736) crushed = true;
			}
		}
	}

	if(getY() != 704 && !onTop) setFalling(true);
}




