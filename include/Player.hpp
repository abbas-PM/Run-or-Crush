#pragma once
#include "Entity.hpp"

class Player : public Entity
{
    public: 
        Player(float px, float py, SDL_Texture* ptex, bool pFalling);
        void update() override;
        void render(SDL_Renderer* renderer) override; 
        SDL_Rect getBounds() override; 
        SDL_Rect getBoundsTop() override;  
        SDL_Rect getBoundsLeft() override;  
        SDL_Rect getBoundsRight() override;  
        void Collision(std::vector<Entity*> handler) override;

        void setCreating(bool pCreating);
        void setFireballs(int pFireballs);
        bool getCreating();
        int getFireballs();
        bool getCrushed();

        void playerReset(); 

    private: 
        float gravity;
        int MAX_SPEED; 
        int fireballs;
        int direction; 
        bool creating;
        bool crushed;
};