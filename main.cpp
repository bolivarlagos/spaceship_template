#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600
#define SHIP_SIZE 100
#define BULLET_SIZE 20

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Error:" << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *bulletTexture = nullptr;
    SDL_Texture *spaceshipTexture = nullptr;

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

    SDL_SetWindowTitle(window, "Spaceship Game");


    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cout << "SDL2_Image format not available" << std::endl;
    }

    SDL_Surface *bulletImage = IMG_Load("./images/bullet.png");

    if (bulletImage == nullptr)
    {
        std::cout << "Error:" << SDL_GetError() << std::endl;
        return -1;
    }

    bulletTexture = SDL_CreateTextureFromSurface(renderer, bulletImage);

    SDL_FreeSurface(bulletImage);

    SDL_Surface *spaceshipImage = IMG_Load("./images/spaceship.png");

    if (spaceshipImage == nullptr)
    {
        std::cout << "Error:" << SDL_GetError() << std::endl;
        return -1;
    }

    spaceshipTexture = SDL_CreateTextureFromSurface(renderer, spaceshipImage);

    SDL_FreeSurface(spaceshipImage);

    bool running = true;

    SDL_Rect spaceship;
    spaceship.x = 0;
    spaceship.y = HEIGHT - SHIP_SIZE;
    spaceship.w = SHIP_SIZE;
    spaceship.h = SHIP_SIZE;

    while (running)
    {
        SDL_Event event;

        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            running = false;
        }

        if (event.type == SDL_KEYDOWN)
        {

            if (event.key.keysym.sym == SDLK_UP)
            {
                int moveUp = spaceship.y - 10;
                spaceship.y = moveUp;

                if (spaceship.y <= 0)
                {
                    spaceship.y = 0;
                }
            }

            if (event.key.keysym.sym == SDLK_DOWN)
            {
                int moveDown = spaceship.y + 10;
                spaceship.y = moveDown;

                if (spaceship.y >= HEIGHT - SHIP_SIZE)
                {
                    spaceship.y = HEIGHT - SHIP_SIZE;
                }
            }

            if (event.key.keysym.sym == SDLK_LEFT)
            {
                int moveLeft = spaceship.x - 10;
                spaceship.x = moveLeft;

                if (spaceship.x <= 0)
                {
                    spaceship.x = 0;
                }
            }

            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                int moveRight = spaceship.x + 10;
                spaceship.x = moveRight;

                if (spaceship.x >= WIDTH - SHIP_SIZE)
                {
                    spaceship.x = WIDTH - SHIP_SIZE;
                }
            }

            if (event.key.keysym.sym == SDLK_SPACE)
            {
                SDL_Rect bullet;
                bullet.x = spaceship.x + (SHIP_SIZE / 2) - (BULLET_SIZE / 2);
                bullet.y = spaceship.y - BULLET_SIZE;
                bullet.w = BULLET_SIZE;
                bullet.h = BULLET_SIZE;

                while (bullet.y >= 0)
                {
                    bullet.y -= 10;
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

                    SDL_RenderClear(renderer);

                    SDL_RenderDrawRect(renderer, &spaceship);

                    SDL_RenderCopy(renderer, spaceshipTexture, NULL, &spaceship);

                    SDL_RenderDrawRect(renderer, &bullet);

                    SDL_RenderCopy(renderer, bulletTexture, NULL, &bullet);

                    SDL_RenderPresent(renderer);

                    SDL_Delay(10);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);

        SDL_RenderDrawRect(renderer, &spaceship);

        SDL_RenderCopy(renderer, spaceshipTexture, NULL, &spaceship);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(bulletTexture);

    SDL_DestroyTexture(spaceshipTexture);

    IMG_Quit();

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
