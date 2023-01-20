#include <SDL2/SDL.h>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SAND_SIZE = 10;
const int SAND_COUNT = 100;

struct Sand {
    int x, y;
    int vx, vy;
    int colorR, colorG, colorB;
};

std::vector<Sand> sands;
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Falling Sand", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Create sand particles
    for (int i = 0; i < SAND_COUNT; i++) {
        Sand sand;
        sand.x = rand() % SCREEN_WIDTH;
        sand.y = rand() % SCREEN_HEIGHT;
        sand.vx = 0;
        sand.vy = 1 + rand() % 5;
        sand.colorR = rand() % 256;
        sand.colorG = rand() % 256;
        sand.colorB = rand() % 256;
        sands.push_back(sand);
    }

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Update sand particles
        for (Sand& sand : sands) {
            sand.y += sand.vy;
            if (sand.y > SCREEN_HEIGHT) {
                sand.y = 0;
            }
        }

        // Draw the falling sand
        for (Sand& sand : sands) {
            SDL_SetRenderDrawColor(renderer, sand.colorR, sand.colorG, sand.colorB, 255);
            SDL_Rect rect;
            rect.x = sand.x;
            rect.y = sand.y;
            rect.w = SAND_SIZE;
            rect.h = SAND_SIZE;
            SDL_RenderFillRect(renderer, &rect);
        }

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}