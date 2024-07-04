#pragma once
#include "Entity.hpp"

class Fireball : public Entity
{
    public: 
        Fireball(float px, float py, SDL_Texture* ptex, float pvelX, bool pFalling);
        void update() override;
        void render(SDL_Renderer* renderer) override;
        SDL_Rect getBounds() override; 
        SDL_Rect getBoundsTop() override;  
        SDL_Rect getBoundsLeft() override;  
        SDL_Rect getBoundsRight() override;  
        virtual void Collision(std::vector<Entity*> handler) override;
};