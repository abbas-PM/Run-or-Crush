#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Entity
{
    private:  
        float x, y; 
        float velX, velY; 
        bool jumping, falling;
        int type;  
        bool deleted; 
        SDL_Texture* tex; 

    public: 
        Entity(float px, float py, SDL_Texture* ptex, bool pFalling);

        float getX(); 
        float getY();
        float getVelX();
        float getVelY(); 
        bool getJumping();
        bool getFalling(); 
        bool getDeleted(); 
        int getType();
        SDL_Texture* getTex(); 
        void setX(float px); 
        void setY(float py);
        void setVelX(float px); 
        void setVelY(float py);
        void setJumping(bool pJumping); 
        void setFalling(bool pFalling); 
        void setDeleted(bool del);
        void setType(int ptype);
        float clamp(float value, float min, float max);
        bool intersect(SDL_Rect a, SDL_Rect b);
   
        virtual void update() = 0;  
        virtual void render(SDL_Renderer* renderer) = 0;
        virtual SDL_Rect getBounds() = 0; 
        virtual SDL_Rect getBoundsTop() = 0; 
        virtual SDL_Rect getBoundsLeft() = 0; 
        virtual SDL_Rect getBoundsRight() = 0; 
        virtual void Collision(std::vector<Entity*> handler) = 0;

};