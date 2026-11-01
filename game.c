#include"game.h"
#include<raylib.h>
#include<stdio.h>

void InitGame(struct Game *game) {
    InitializeSnake(&game->snake, GRID_WIDTH / 2, GRID_HEIGHT / 2);
    SpawnFood(&game->food, &game->snake,GRID_WIDTH,GRID_HEIGHT);
    game->score = 0;
    game->highScore = LoadHighScore(HIGH_SCORE_FILE);
    game->isGameOver = 0;
    game->frameCounter = 0;
}

void UpdateGame(struct Game *game) {

    if (game->isGameOver) {
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_R)) {
            InitGame(game);
        }
        return;
    }



    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && game->snake.direction != DIRECTION_DOWN) {
        game->snake.direction = DIRECTION_UP;
    } else if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && game->snake.direction != DIRECTION_UP) {
        game->snake.direction = DIRECTION_DOWN;
    } else if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && game->snake.direction != DIRECTION_RIGHT) {
        game->snake.direction = DIRECTION_LEFT;
    } else if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && game->snake.direction != DIRECTION_LEFT) {
        game->snake.direction = DIRECTION_RIGHT;
    }

    game->frameCounter++;
    int init_speed = MOVE_INTERVAL_FRAMES;
    if(game->score >15){
        init_speed = init_speed-4;
    }

    if (game->frameCounter >= init_speed){
        game->frameCounter = 0;
        struct Position oldTail;
        MoveSnake(&game->snake, &oldTail);

        struct Position headPosition = game->snake.body[0];

        if (headPosition.x < 0 || headPosition.x >= GRID_WIDTH ||
            headPosition.y < 0 || headPosition.y >= GRID_HEIGHT) {
            game->isGameOver = 1;
            return;
        }

        if (CheckSnakeSelfCollision(&game->snake)) {
            game->isGameOver = 1;
            return;
        }

        if (game->isGameOver) {
            if (game->score > game->highScore) {
                game->highScore = game->score;
                SaveHighScore(HIGH_SCORE_FILE, game->highScore);
            }
            return;
        }

        if (headPosition.x == game->food.position.x && headPosition.y == game->food.position.y) {
            GrowSnake(&game->snake, oldTail);
            game->score += 1;
            if (game->score > game->highScore) {
                game->highScore = game->score;
                SaveHighScore(HIGH_SCORE_FILE, game->highScore);
            }
            SpawnFood(&game->food, &game->snake, GRID_WIDTH, GRID_HEIGHT);
        }

    }

}

void DrawGame(const struct Game *game) {
    ClearBackground(BLACK);

    // Header bar
    DrawRectangle(0, 0, SCREEN_WIDTH, TOP_BAR_HEIGHT, (Color){ 30, 41, 59, 255 });

    char scoreBuffer[32];
    snprintf(scoreBuffer, sizeof(scoreBuffer), "SCORE: %d", game->score);
    DrawText(scoreBuffer, 20, 10, 20, (Color){ 241, 245, 249, 255 });

    char highScoreBuffer[64];
    snprintf(highScoreBuffer, sizeof(highScoreBuffer), "HIGH SCORE: %d", game->highScore);
    DrawText(highScoreBuffer, SCREEN_WIDTH - 220, 10, 20, (Color){ 251, 191, 36, 255 });

    DrawFood(&game->food, CELL_SIZE, TOP_BAR_HEIGHT);
    DrawSnake(&game->snake, CELL_SIZE, TOP_BAR_HEIGHT);

    if(game->isGameOver){
        DrawRectangle(0, TOP_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - TOP_BAR_HEIGHT, (Color){ 15, 23, 42, 220 });

        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 60, 40, (Color){ 239, 68, 68, 255 });

        char finalScoreBuffer[64];
        snprintf(finalScoreBuffer, sizeof(finalScoreBuffer), "Final Score: %d", game->score);
        DrawText(finalScoreBuffer, SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2, 20, (Color){ 226, 232, 240, 255 });

        DrawText("Press ENTER or SPACE to Restart", SCREEN_WIDTH / 2 - 170, SCREEN_HEIGHT / 2 + 50, 20, (Color){ 226, 232, 240, 255 });


    }

}