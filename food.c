#include"food.h"
#include<raylib.h>
#include<stdlib.h>

void SpawnFood(struct Food *food, const struct Snake *snake, int gridWidth, int gridHeight){

    int validPositionFound = 0;

    while(!validPositionFound){

        int randomX = rand() % gridWidth;
        int randomY = rand() % gridHeight;

        int overlapsWithSnake = 0;
        for (int i = 0; i < snake->length; i++) {
            if (snake->body[i].x == randomX && snake->body[i].y == randomY) {
                overlapsWithSnake = 1;
                break;
            }
        }

        if(!overlapsWithSnake){
            food->position.x = randomX;
            food->position.y = randomY;
            food->active = 1;
            validPositionFound = 1;
        }

    }

}

void DrawFood(const struct Food *food, int cellSize, int gridOffsetY) {
    if (!food->active) return;

    Color foodColor = (Color){ 244, 63, 94, 255 }; // Rose Red

    int pixelX = food->position.x * cellSize + 2;
    int pixelY = gridOffsetY + (food->position.y * cellSize) + 2;
    int foodSize = cellSize - 4;

    DrawRectangle(pixelX, pixelY, foodSize, foodSize, foodColor);
}
