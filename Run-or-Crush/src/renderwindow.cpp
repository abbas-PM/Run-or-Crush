#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height)
    :window(NULL), renderer(NULL)
{
        //Create window and set to window pointer. 
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

        //If window failed to be created. 
        if(window == NULL)
        {
            std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
        }

        //Create renderer and set to renderer pointer. 
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        //If renderer failed to be created.
        if (renderer == NULL)
        {
            std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
        }

        //Set the color of the background.
        SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);
}

//Function to load textures.
SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
        SDL_Texture* texture = NULL; 
        texture = IMG_LoadTexture(renderer, filePath);

        if(texture == NULL)
        {
            std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
        }

        return texture; 
}

//Get function for renderer.
SDL_Renderer* RenderWindow::getRenderer()
{
        return renderer;
}

//Function to render text using a font.
void RenderWindow::renderText(float px, float py, const char* ptext, TTF_Font* font, SDL_Color textColor)
{
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, ptext, textColor);
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        SDL_Rect text;
        text.x = px;
        text.y = py;

        SDL_QueryTexture(message, NULL, NULL, &text.w, &text.h);

        SDL_RenderCopy(renderer, message, NULL, &text);
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(message);
}

//Function used when the program terminates.
void RenderWindow::cleanUp()
{
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer); 
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();  
}

//Clearing the screen.
void RenderWindow::clear()
{
        SDL_RenderClear(renderer); 
}

//Displaying everything on the screen.
void RenderWindow::display()
{
        SDL_RenderPresent(renderer);
}
