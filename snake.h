#ifndef SNAKE_H
#define SNAKE_H

#include"position.h"


// Direction Constants
#define DIRECTION_UP    0
#define DIRECTION_DOWN  1
#define DIRECTION_LEFT  2
#define DIRECTION_RIGHT 3

#define MAX_SNAKE_LENGTH 256

struct Snake
{
    struct Position body[MAX_SNAKE_LENGTH];
    int length;
    int direction;
};

void InitializeSnake(struct Snake *snake, int startX, int startY);
void MoveSnake(struct Snake *snake, struct Position *outOldTailPosition);
void GrowSnake(struct Snake *snake, struct Position tailPositionToAppend);
int CheckSnakeSelfCollision(const struct Snake *snake);
void DrawSnake(const struct Snake *snake, int cellSize, int gridOffsetY);


#endif