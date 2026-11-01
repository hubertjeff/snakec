#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"
#include "score.h"

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600
#define CELL_SIZE       20
#define TOP_BAR_HEIGHT  40

#define GRID_WIDTH         (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT        ((SCREEN_HEIGHT - TOP_BAR_HEIGHT) / CELL_SIZE)

#define MOVE_INTERVAL_FRAMES 8
#define HIGH_SCORE_FILE    "highscore.txt"

struct Game
{
    struct Snake snake;
    struct Food food;
    int score;
    int highScore;
    int isGameOver;
    int frameCounter;
};

void InitGame(struct Game *game);
void UpdateGame(struct Game *game);
void DrawGame(const struct Game *game);

#endif