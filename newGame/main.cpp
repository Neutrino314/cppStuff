#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>

const short GRAVITY(1);

class playerBox {

private:

    short xAcceleration = 0;
    short yAcceleration = 0;
    short jumpPower = 24;
    short jumpCount = 0;
    short maxYAcceleration = 120;
    const Uint8 *curKeyState = SDL_GetKeyboardState(NULL);
    bool spacePressed = false;

    bool onGround = false;
    SDL_Point collPoints[4];

    SDL_Rect playerRect {300, 0, 64, 128};


public:

    void jump() {

        if (jumpCount < 2) {

            jumpCount ++;
            yAcceleration = jumpPower;

        }



    };

    void handleInput() {

        if (curKeyState[SDL_SCANCODE_SPACE] && !spacePressed) {

            jump();
            spacePressed = true;

        }else if (!curKeyState[SDL_SCANCODE_SPACE]) {

            spacePressed = false;

        }

        if (curKeyState[SDL_SCANCODE_LEFT]) {

            xAcceleration = -8;

        }

        if (curKeyState[SDL_SCANCODE_RIGHT]) {

            xAcceleration = 8;

        }

        if (!curKeyState[SDL_SCANCODE_RIGHT] && !curKeyState[SDL_SCANCODE_LEFT]) xAcceleration = 0;

    };

    void applyGravity() {

        yAcceleration -= GRAVITY;

    };

    void updateCollPoints() {

        collPoints[0].x = playerRect.x + playerRect.w / 2;
        collPoints[0].y = playerRect.y;
        collPoints[1].x = playerRect.x + playerRect.w;
        collPoints[1].y = playerRect.y + playerRect.h / 2;
        collPoints[2].x = playerRect.x + playerRect.w / 2;
        collPoints[2].y = playerRect.y + playerRect.h;
        collPoints[3].x = playerRect.x;
        collPoints[3].y = playerRect.y + playerRect.h / 2;

    };


    void collide(SDL_Rect *barrier) {

        if (SDL_PointInRect(&collPoints[0], barrier)) {

            playerRect.y = barrier->y + barrier->h;
            yAcceleration = 0;

            updateCollPoints();

        }

        if (SDL_PointInRect(&collPoints[1], barrier)) {

            playerRect.x = barrier->x - playerRect.w;
            xAcceleration = 0;

            updateCollPoints();

        }

        if (SDL_PointInRect(&collPoints[2], barrier)) {

            playerRect.y = barrier->y - playerRect.h;
            yAcceleration = 0;
            onGround = true;
            jumpCount = 0;

            updateCollPoints();

        }

        if (SDL_PointInRect(&collPoints[3], barrier)) {

            playerRect.x = barrier->x + barrier->w;
            xAcceleration = 0;

            updateCollPoints();

        }

    };

    void update(SDL_Renderer *renderer, SDL_Rect *barrier) {

        handleInput();

        applyGravity();

        playerRect.x += xAcceleration;
        playerRect.y -= yAcceleration;

        if (playerRect.x < -32 - playerRect.w) {

            playerRect.x = 1200 - 32;

        } else if (playerRect.x > 1200 + 16) {

            playerRect.x = -8;

        }

        updateCollPoints();

        collide(barrier);

        if (playerRect.y >= 600 + playerRect.w) {

            playerRect.y = 600 + playerRect.w;
            onGround = true;
            jumpCount = 0;
            yAcceleration = 0;

        }

        draw(renderer);


    };


    void draw(SDL_Renderer *renderer) {

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderFillRect(renderer, &playerRect);

    };

    void printPosition() {

        std::cout << playerRect.x << ", " << playerRect.y << std::endl;

    }


};

int main(int argc, char* args[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {

        std::cout << "sdl init error: " << SDL_GetError() << std::endl;
        return 1;

    }

    SDL_Window *window = SDL_CreateWindow("new game", 0, 0, 1200, 900, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    playerBox player;

    SDL_Event event;

    SDL_Rect *platform = new SDL_Rect {400, 500, 300, 100};

    bool running(true);

    while (running) {

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {

                running = false;

            }


        }


        SDL_SetRenderDrawColor(renderer, 235, 235, 235, 255);

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        SDL_RenderFillRect(renderer, platform);

        player.update(renderer, platform);

        SDL_RenderPresent(renderer);

        player.printPosition();

    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << sizeof(player) << std::endl;

    return 0;

}
