#ifndef FOOD_H
#define FOOD_H

#include"position.h"
#include"snake.h"

struct Food {
    struct Position position;
    int active;
};

void SpawnFood(struct Food *food, const struct Snake *snake,
    int gridWidth, int gridHeight);
void DrawFood(const struct Food *food, int cellSize, int gridOffsetY);

#endif