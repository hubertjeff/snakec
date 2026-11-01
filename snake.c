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
    Color headColor = (Color){ 52, 211, 153, 255 };  // Mint
    Color tailColor = (Color){ 6, 95, 70, 255 };     // Deep green
    Color eyeWhite  = (Color){ 240, 253, 244, 255 };
    Color pupil     = (Color){ 15, 23, 42, 255 };

    // Draw from tail to head so the head is always on top
    for (int i = snake->length - 1; i >= 0; i--) {
        float t = (snake->length > 1) ? (float)i / (float)(snake->length - 1) : 0.0f;
        Color c = {
            (unsigned char)(headColor.r + (tailColor.r - headColor.r) * t),
            (unsigned char)(headColor.g + (tailColor.g - headColor.g) * t),
            (unsigned char)(headColor.b + (tailColor.b - headColor.b) * t),
            255
        };

        Rectangle seg = {
            (float)(snake->body[i].x * cellSize + 1),
            (float)(gridOffsetY + snake->body[i].y * cellSize + 1),
            (float)(cellSize - 2),
            (float)(cellSize - 2)
        };
        DrawRectangleRounded(seg, (i == 0) ? 0.6f : 0.4f, 6, c);
    }

    // Eyes on the head, facing the movement direction
    float cx = snake->body[0].x * cellSize + cellSize / 2.0f;
    float cy = gridOffsetY + snake->body[0].y * cellSize + cellSize / 2.0f;
    float fwd = cellSize * 0.18f;   // how far forward the eyes sit
    float side = cellSize * 0.22f;  // spacing between the eyes
    float dx = 0, dy = 0;
    switch (snake->direction) {
        case DIRECTION_UP:    dy = -1; break;
        case DIRECTION_DOWN:  dy =  1; break;
        case DIRECTION_LEFT:  dx = -1; break;
        case DIRECTION_RIGHT: dx =  1; break;
    }
    // perpendicular vector is (-dy, dx)
    for (int s = -1; s <= 1; s += 2) {
        float ex = cx + dx * fwd + (-dy) * side * s;
        float ey = cy + dy * fwd + dx * side * s;
        DrawCircle((int)ex, (int)ey, cellSize * 0.16f, eyeWhite);
        DrawCircle((int)(ex + dx * 1.5f), (int)(ey + dy * 1.5f), cellSize * 0.08f, pupil);
    }
}
