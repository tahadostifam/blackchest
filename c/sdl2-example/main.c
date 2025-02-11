#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SQUARE_SIZE 20
#define SNAKE_MAX_LENGTH 100

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point body[SNAKE_MAX_LENGTH];
    int length;
    int dx, dy;
} Snake;

void spawn_food(Point *food) {
    food->x = (rand() % (SCREEN_WIDTH / SQUARE_SIZE)) * SQUARE_SIZE;
    food->y = (rand() % (SCREEN_HEIGHT / SQUARE_SIZE)) * SQUARE_SIZE;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    Snake snake = {{{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}}, 1, SQUARE_SIZE, 0};
    Point food;
    spawn_food(&food);
    
    int running = 1;
    SDL_Event event;
    srand(time(NULL));
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:    if (snake.dy == 0) { snake.dx = 0; snake.dy = -SQUARE_SIZE; } break;
                    case SDLK_DOWN:  if (snake.dy == 0) { snake.dx = 0; snake.dy = SQUARE_SIZE; } break;
                    case SDLK_LEFT:  if (snake.dx == 0) { snake.dx = -SQUARE_SIZE; snake.dy = 0; } break;
                    case SDLK_RIGHT: if (snake.dx == 0) { snake.dx = SQUARE_SIZE; snake.dy = 0; } break;
                }
            }
        }
        
        for (int i = snake.length - 1; i > 0; i--) {
            snake.body[i] = snake.body[i - 1];
        }
        
        snake.body[0].x += snake.dx;
        snake.body[0].y += snake.dy;
        
        if (snake.body[0].x < 0 || snake.body[0].x >= SCREEN_WIDTH || snake.body[0].y < 0 || snake.body[0].y >= SCREEN_HEIGHT) running = 0;
        
        for (int i = 1; i < snake.length; i++) {
            if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) running = 0;
        }
        
        if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
            if (snake.length < SNAKE_MAX_LENGTH) snake.length++;
            spawn_food(&food);
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect food_rect = {food.x, food.y, SQUARE_SIZE, SQUARE_SIZE};
        SDL_RenderFillRect(renderer, &food_rect);
        
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (int i = 0; i < snake.length; i++) {
            SDL_Rect segment = {snake.body[i].x, snake.body[i].y, SQUARE_SIZE, SQUARE_SIZE};
            SDL_RenderFillRect(renderer, &segment);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}