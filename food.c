#include"food.h"
#include<raylib.h>
#include<stdlib.h>
#include<math.h>

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

    Color appleColor = (Color){ 244, 63, 94, 255 };  // Rose red
    Color leafColor  = (Color){ 74, 222, 128, 255 };
    Color stemColor  = (Color){ 120, 72, 40, 255 };

    float cx = food->position.x * cellSize + cellSize / 2.0f;
    float cy = gridOffsetY + food->position.y * cellSize + cellSize / 2.0f + 1;

    // Gentle pulsing glow
    float pulse = (sinf((float)GetTime() * 5.0f) + 1.0f) * 0.5f;  // 0..1
    float radius = cellSize * 0.38f;
    DrawCircle((int)cx, (int)cy, radius + 3 + pulse * 3, Fade(appleColor, 0.18f));

    // Apple body + highlight
    DrawCircle((int)cx, (int)cy, radius, appleColor);
    DrawCircle((int)(cx - radius * 0.35f), (int)(cy - radius * 0.35f), radius * 0.25f, Fade(WHITE, 0.6f));

    // Stem and leaf
    DrawRectangle((int)cx - 1, (int)(cy - radius - 3), 2, 4, stemColor);
    DrawEllipse((int)(cx + 3), (int)(cy - radius - 2), 3, 1.6f, leafColor);
}
