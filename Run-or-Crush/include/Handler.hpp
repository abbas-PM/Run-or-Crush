#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "Entity.hpp"

class Handler
{
    public:
        std::vector<Entity*> handler;
        void update();
        void render(SDL_Renderer* renderer); 
        void collision();
        void addObject(Entity* entity);
        void removeObject();
        void clearAll();
        void ClearAll(); 
};