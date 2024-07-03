#pragma once
#include "Entity.hpp"

class Block : public Entity
{
    public: 
        Block(float px, float py, SDL_Texture* ptex, bool pFalling);
        void update() override;
        void render(SDL_Renderer* renderer) override; 
        SDL_Rect getBounds() override; 
        SDL_Rect getBoundsTop() override;  
        SDL_Rect getBoundsLeft() override;  
        SDL_Rect getBoundsRight() override;  
        void Collision(std::vector<Entity*> handler) override;
};