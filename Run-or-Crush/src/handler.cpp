#include "Handler.hpp"

//Function to update all entities in handler.
void Handler::update()
{
    for(int i = 0; i < handler.size(); i++)
    {
        handler[i]->update(); 
    }
}

//Function to render all entities in handler.
void Handler::render(SDL_Renderer* renderer)
{
    for(int i = 0; i < handler.size(); i++)
    {
        handler[i]->render(renderer); 
    }
}

//Function to check collision between entities in handler.
void Handler::collision()
{
    for(int i = 1; i < handler.size(); i++)
    {
        handler[i]->Collision(handler);
    }

    handler[0]->Collision(handler);
}

//Function to add an entity to handler.
void Handler::addObject(Entity* entity)
{
    handler.push_back(entity);
}

//Function to remove an entity to handler.
void Handler::removeObject()
{
    for(int i = 0; i < handler.size(); i++)
    {
        if (handler[i]->getDeleted())
        {
            delete handler[i];
            handler.erase(handler.begin() + i);
        }
    }
}

//Function to remove everything from handler (except the player entity).
void Handler::clearAll()
{
    for(int i = 1; i < handler.size(); i++)
    {
        delete handler[i];
    }

    handler.clear();
}

//Function to remove everything from handler.
void Handler::ClearAll()
{
    for(int i = 0; i < handler.size(); i++)
    {
        delete handler[i];
    }

    handler.clear();
}