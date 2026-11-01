#include<raylib.h>
#include"snake.h"

void InitializeSnake(struct Snake *snake, int startX, int startY) {
    snake->length = 2;
    snake->direction = DIRECTION_RIGHT;

    //Head
    snake->body[0].x = startX;
    snake->body[0].y = startY;

    //Body
    snake->body[1].x = startX - 1;
    snake->body[1].y = startY;
    
    snake->body[2].x = startX - 2;
    snake->body[2].y = startY;
    
}

void MoveSnake(struct Snake *snake, struct Position *outOldTailPosition) {
    int tailIndex = snake->length - 1;

    outOldTailPosition->x = snake->body[tailIndex].x;
    outOldTailPosition->y = snake->body[tailIndex].y;

    for (int i = tailIndex; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }

    // Move head according to direction
    switch (snake->direction) {
        case DIRECTION_UP:
            snake->body[0].y -= 1;
            break;
        case DIRECTION_DOWN:
            snake->body[0].y += 1;
            break;
        case DIRECTION_LEFT:
            snake->body[0].x -= 1;
            break;
        case DIRECTION_RIGHT:
            snake->body[0].x += 1;
            break;
    }



}

void GrowSnake(struct Snake *snake, struct Position tailPositionToAppend) {
    if (snake->length < MAX_SNAKE_LENGTH) {
        snake->body[snake->length] = tailPositionToAppend;
        snake->length += 1;
    }
}

int CheckSnakeSelfCollision(const struct Snake *snake) {
    struct Position headPosition = snake->body[0];
    for (int i = 1; i < snake->length; i++) {
        if (headPosition.x == snake->body[i].x && headPosition.y == snake->body[i].y) {
            return 1;
        }
    }
    return 0;
}


void DrawSnake(const struct Snake *snake, int cellSize, int gridOffsetY) {
    Color headColor = (Color){ 102, 191, 255, 255 }; // Vibrant Emerald
    Color bodyColor = (Color){ 34, 197, 94, 255 };  // Bright Lime

    for (int i = 0; i < snake->length; i++) {
        int pixelX = snake->body[i].x * cellSize + 1;
        int pixelY = gridOffsetY + (snake->body[i].y * cellSize) + 1;
        int segmentSize = cellSize - 2;

        if (i == 0) {
            DrawRectangle(pixelX, pixelY, segmentSize, segmentSize, headColor);
        } else {
            DrawRectangle(pixelX, pixelY, segmentSize, segmentSize, bodyColor);
        }
    }

}