#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string.h>
#include <cmath>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Fireball.hpp"
#include "Handler.hpp"
#include "Block.hpp"

const int WIDTH = 768; 
const int HEIGHT = 768;

RenderWindow* window; 
Handler* handler; 
Player* player; 

SDL_Texture* player_sheet;
SDL_Texture* number_sheet;
SDL_Texture* menu_sheet;
SDL_Texture* fireball; 
SDL_Texture* blockTex; 

TTF_Font* font32;
TTF_Font* font64;
TTF_Font* font96; 

int coolDown[6];
bool moving[3]; 
bool winner[2];

int minutes = 2;
int seconds = 30; 

bool MainMenu = true;
bool gameComplete = false;

SDL_Color black = {0, 0, 0, 255};

void init()
{
    window = new RenderWindow("Run or Crush", WIDTH, HEIGHT);
    handler = new Handler(); 
    
    player_sheet = window->loadTexture("res/textures/player_sheet.png");
    number_sheet = window->loadTexture("res/textures/number_sheet.png");
    menu_sheet = window->loadTexture("res/textures/menu_sheet.png");
    fireball = window->loadTexture("res/textures/fireball.png");
    blockTex = window->loadTexture("res/textures/block.png");

    font32 = TTF_OpenFont("res/font/snow.ttf", 32);
    font64 = TTF_OpenFont("res/font/snow.ttf", 64);
    font96 = TTF_OpenFont("res/font/snow.ttf", 96);

    player = new Player(50, 736, player_sheet, false);

    handler->addObject(player); 
}

void reset()
{
    handler->clearAll(); 
    handler->addObject(player);
    player->playerReset();
    minutes = 2; 
    seconds = 30; 
    moving[0] = moving[1] = moving[2] = false;
    coolDown[0] = coolDown[1] = coolDown[2] = coolDown[3] = coolDown[5] = 0; 
    winner[0] = winner[1] = false;
    MainMenu = true;
    gameComplete = false;
}

bool mouseOver(int mx, int my, int x, int y, int width, int height)
{
    if(mx > x && mx < (x + width) && my > y && my < (y + height))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void addBlock(int x, int y)
{
    if(mouseOver(x, y, 0, 0, 96, HEIGHT))
    {
        Block *block = new Block(0, 0, blockTex, true);
        handler->addObject(block);
    }

    if(mouseOver(x, y, 96, 0, 96, HEIGHT))
    {
        Block *block = new Block(96, 0, blockTex, true);
        handler->addObject(block);
    }

    if(mouseOver(x, y, 192, 0, 96, HEIGHT))
    {
        Block *block = new Block(192, 0, blockTex, true);
        handler->addObject(block);
    }

    if(mouseOver(x, y, 288, 0, 96, HEIGHT))
    {
        Block *block = new Block(288, 0, blockTex, true);
        handler->addObject(block); 
    }

    if(mouseOver(x, y, 384, 0, 96, HEIGHT))
    {
        Block *block = new Block(384, 0, blockTex, true);
        handler->addObject(block);
    }

    if(mouseOver(x, y, 480, 0, 96, HEIGHT))
    {
        Block *block = new Block(480, 0, blockTex, true);
        handler->addObject(block);
    }

    if(mouseOver(x, y, 576, 0, 96, HEIGHT))
    {
        Block *block = new Block(576, 0, blockTex, true);
        handler->addObject(block);
    }

    if(mouseOver(x, y, 672, 0, 96, HEIGHT))
    {
        Block *block = new Block(672, 0, blockTex, true);
        handler->addObject(block);
    }
}

void addFireball()
{
    Fireball *fire;

    if(player->getVelX() != 0)
    {
        fire = new Fireball(player->getX()+17, player->getY()+25, fireball, player->getVelX() * 2, false);
        player->setFireballs(player->getFireballs() - 1);
    }
    
    else if(player->getVelX() == 0)
    {
        if(!moving[2]) fire = new Fireball(player->getX()+17, player->getY()+ 25, fireball, 8, false); 
        else fire = new Fireball(player->getX()+17, player->getY()+ 25, fireball, -8, false);

        player->setFireballs(player->getFireballs() - 1); 
    }
                        
    handler->addObject(fire);

}

void displayNumber(int num, int x, bool addZero)
{
    char n_char[2];

    if(addZero) std::sprintf(n_char, "%d%d", 0, num);
    else std::sprintf(n_char, "%d", num);

    for(int i = 0; i < strlen(n_char); i++)
    {
        SDL_Rect numSRC; 
        numSRC.x = (int(n_char[i]) - 48) * 32; 
        numSRC.y = 0; 
        numSRC.w = numSRC.h = 32;


        SDL_Rect numDST; 
        numDST.x = x + (i * 28); 
        numDST.y  = -10; 
        numDST.w = numDST.h = 64;

        SDL_RenderCopy(window->getRenderer(), number_sheet, &numSRC, &numDST);
    }
}

void addHUD()
{
    //Tracking number of fireballs player has. 
    SDL_Rect src; 
    src.x = src.y = 0; 
    src.w = src.h = 32; 

    SDL_Rect dst; 
    dst.x = dst.y = 5;
    dst.w = dst.h = 32; 

    SDL_RenderCopy(window->getRenderer(), fireball, &src, &dst);

    SDL_Rect src2; 
    src2.x = 320; 
    src2.y = 0; 
    src2.w = src2.h = 32;

    SDL_Rect dst2; 
    dst2.x = 18; 
    dst2.y  = -5; 
    dst2.w = dst2.h = 64;

    SDL_RenderCopy(window->getRenderer(), number_sheet, &src2, &dst2);

    displayNumber(player->getFireballs(), 45, false);

    //Displays the timer
    displayNumber(minutes, 645, false);
    
    if(seconds > 9) displayNumber(seconds, 685, false); 
    else displayNumber(seconds, 685, true); 

    SDL_Rect src3; 
    src3.x = 352; 
    src3.y = 0; 
    src3.w = src2.h = 32;

    SDL_Rect dst3; 
    dst3.x = 682; 
    dst3.y  = 5; 
    dst3.w = dst3.h = 32;

    SDL_RenderCopy(window->getRenderer(), number_sheet, &src3, &dst3);

    //To show cooldown on fireball creating.
    SDL_Rect fSRC;
    fSRC.x = 10; 
    fSRC.y = 50; 
    fSRC.w = 150;
    fSRC.h = 20; 

    SDL_Rect src4; 
    src4.x = 10;
    src4.y = 50;
    src4.w = 0.25 * (600 - coolDown[1]);
    src4.h = 20;

    //To show cooldown on block placement.
    SDL_Rect bSRC; 
    bSRC.x = 608;
    bSRC.y = 50;
    bSRC.w = 150;
    bSRC.h = 20;

    SDL_Rect src5; 
    src5.x = 608;
    src5.y = 50;
    src5.w = 2.5 * (60 - coolDown[2]);
    src5.h = 20;

    //To show fireball creation completion
    SDL_Rect fcSRC;
    fcSRC.x = player->getX();
    fcSRC.y = player->getY() - 20;
    fcSRC.w = 60;
    fcSRC.h = 10;

    SDL_Rect src6; 
    src6.x = player->getX();
    src6.y = player->getY() - 20;
    if(coolDown[3] == 0) src6.w = coolDown[0];
    else src6.w = 60;
    src6.h = 10; 

    SDL_SetRenderDrawColor(window->getRenderer(), 255, 0, 0, 0);

    SDL_RenderFillRect(window->getRenderer(), &src4);

    SDL_SetRenderDrawColor(window->getRenderer(), 5, 146, 184, 0);

    SDL_RenderFillRect(window->getRenderer(), &src5);

    SDL_SetRenderDrawColor(window->getRenderer(), 255, 255, 0, 0);

    SDL_RenderFillRect(window->getRenderer(), &src6);

    SDL_SetRenderDrawColor(window->getRenderer(), 0, 0, 0, 0);

    SDL_RenderDrawRect(window->getRenderer(), &fSRC);
    SDL_RenderDrawRect(window->getRenderer(), &bSRC);
    if(player->getCreating() || coolDown[3] > 0) SDL_RenderDrawRect(window->getRenderer(), &fcSRC);

    SDL_SetRenderDrawColor(window->getRenderer(), 173, 216, 230, 255);
}

void Timer(int* frameCounter)
{
    *frameCounter = *frameCounter + 1;

    if(*frameCounter % 60 == 0) seconds -= 1; 
    
    if(seconds == -1)
    {
        minutes -= 1; 
        seconds = 59;
    }

    if(player->getCreating()) coolDown[0] += 1; 
    if(coolDown[1] > 0) coolDown[1] -= 1;
    if(coolDown[2] > 0) coolDown[2] -= 1; 
    if(coolDown[3] > 0) coolDown[3] -= 1;

    if(coolDown[0] == 60)
    {
        coolDown[0] = 0; 
        coolDown[1] = 600;
        coolDown[3] = 30; 
        player->setCreating(false); 
        player->setFireballs(player->getFireballs() + 5);
    } 
}

void gameLoop()
{
    bool running = true; 
 
    const int FPS = 60; 
    const int frameDelay = 1000 / FPS; 

    Uint32 frameStart; 
    int frameTime; 

    int frameCounter = 0;

    while(running)
    {
        frameStart = SDL_GetTicks(); 

        SDL_Event event;
  
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false; 
            }

            else if(event.type == SDL_MOUSEBUTTONDOWN && !MainMenu)
            {
                int x = 0; 
                int y = 0; 
                SDL_GetMouseState(&x, &y); 

                if(coolDown[2] == 0)
                {
                    addBlock(x, y);
                    coolDown[2] = 60;
                }
            }

            else if(event.type == SDL_MOUSEBUTTONDOWN && MainMenu && SDL_GetTicks() > 2500)
            {
                MainMenu = false;
            }

            else if(event.type == SDL_KEYDOWN && !MainMenu && !player->getCrushed())
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_a: 
                        moving[0] = true;
                        player->setCreating(false); 
                        coolDown[0] = 0;
                        break; 
                    
                    case SDLK_d: 
                        moving[1] = true;
                        player->setCreating(false); 
                        coolDown[0] = 0;
                        break; 
                    
                    case SDLK_SPACE: 
                        if(coolDown[1] == 0 && !player->getJumping() && !player->getFalling())
                        {
                            moving[0] = false; 
                            moving[1] = false; 
                            player->setCreating(true);
                        }
                        break; 
                }
            }

            else if(event.type == SDL_KEYUP && !MainMenu && !player->getCrushed())
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_a: 
                        moving[0] = false; 
                        moving[2] = true;
                        break; 

                    case SDLK_d:
                        moving[1] = false;
                        moving[2] = false;
                        break; 
                        
                    case SDLK_w: 
                        if(!player->getJumping() && !player->getFalling())
                        {
                            player->setJumping(true);
                            player->setVelY(-11);
                        }
                        player->setCreating(false);
                        coolDown[0] = 0;
                        break; 
                        
                    case SDLK_s:
                        if(player->getFireballs() > 0) addFireball(); 
                        player->setCreating(false); 
                        coolDown[0] = 0;
                        break; 
                        
                    case SDLK_SPACE:
                        player->setCreating(false);
                        coolDown[0] = 0;
                        break; 
                }
            }
        }

        if(MainMenu)
        {
            if(SDL_GetTicks() < 2500)
            {
                window->clear();
                window->renderText(WIDTH/5 + 10, 320 + sin(SDL_GetTicks()/100) * 2, "Created by Abbas Peermohammed", font32, black);
                window->display();
            }
            else
            {
                window->clear();

                window->renderText(WIDTH/5 - 3, 20, "Run Or Crush", font96, black);
                window->renderText(WIDTH/4 + 35, 320 + sin(SDL_GetTicks()/100) * 2, "Click to Play", font64, black);

                SDL_Rect src1 = {0, 0, 32, 32};
                SDL_Rect dst1 = {100, 615, 160, 160};

                SDL_Rect src2 = {32, 0, 32, 32};
                SDL_Rect dst2 = {400, 672, 96, 96};

                SDL_Rect src3 = {64, 0, 32, 32};
                SDL_Rect dst3 = {500, 658, 110, 110};

                SDL_RenderCopy(window->getRenderer(), menu_sheet, &src1, &dst1);
                SDL_RenderCopy(window->getRenderer(), menu_sheet, &src2, &dst2);
                SDL_RenderCopy(window->getRenderer(), menu_sheet, &src3, &dst3);

                window->display();
            }
        }
        else if(gameComplete)
        {
            window->clear();
            coolDown[4]--;

            if(winner[0]) window->renderText(WIDTH/3 + 10, 320 + sin(SDL_GetTicks()/100) * 2, "The Runner Wins!", font32, black);
            else if(winner[1]) window->renderText(WIDTH/3 + 10, 320 + sin(SDL_GetTicks()/100) * 2, "The Crusher Wins!", font32, black);

            if(coolDown[4] == 0)
            {
                reset();
            }
            window->display();
        }
        else
        {
            window->clear();

            SDL_SetRenderDrawColor(window->getRenderer(), 0, 0, 0, 0);

            for(int i = 1; i < 9; i++)
            {
                SDL_RenderDrawLine(window->getRenderer(), 96*i, 0, 96*i, HEIGHT);
            }

            for(int i = 1; i < 9; i++)
            {
                SDL_RenderDrawLine(window->getRenderer(), 0, 96*i, WIDTH, 96*i);
            }

            SDL_SetRenderDrawColor(window->getRenderer(), 173, 216, 230, 255);

            handler->update();
            handler->render(window->getRenderer());
            handler->collision();

            handler->removeObject();

            addHUD();
            Timer(&frameCounter);

            if(moving[0])player->setVelX(-4);
            if(moving[1])player->setVelX(4);

            if((!moving[0] && !moving[1]) || (moving[0] && moving[1]))player->setVelX(0);

            if(minutes == 0 && seconds == 0)
            {
                gameComplete = true;
                winner[0] = true;
                coolDown[4] = 300;
            }

            if(player->getCrushed())
            {
                coolDown[5]++;

                if(coolDown[5] == 15)
                {
                    gameComplete = true;
                    winner[1] = true;
                    coolDown[4] = 300;
                }
            }

            window->display();
        }

        frameTime = SDL_GetTicks() - frameStart; 

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime); 
        }
    } 

    TTF_CloseFont(font32);
    TTF_CloseFont(font64);
    TTF_CloseFont(font96);

    SDL_DestroyTexture(player_sheet);
    SDL_DestroyTexture(number_sheet);
    SDL_DestroyTexture(menu_sheet);
    SDL_DestroyTexture(blockTex);
    SDL_DestroyTexture(fireball);

    handler->ClearAll(); 
    window->cleanUp();
}

int main(int argc, char* argv[])
{
    //If SDL_Init failed. 
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl; 
    }

    //If IMG_Init failed. 
    if(!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG_Init failed: " << IMG_GetError() << std::endl; 

    }

    //If TTF_Init failed
    if(TTF_Init() < 0)
    {
        std::cout << "TTF_Init failed: " << TTF_GetError() << std::endl; 
    }

    init(); 
    gameLoop(); 

    return 0; 
}