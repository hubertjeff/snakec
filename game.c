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

static void DrawCenteredText(const char *text, int centerX, int y, int fontSize, Color color) {
    int width = MeasureText(text, fontSize);
    DrawText(text, centerX - width / 2, y, fontSize, color);
}

void DrawGame(const struct Game *game) {
    Color bgColor     = (Color){ 15, 23, 42, 255 };    // Slate 900
    Color tileA       = (Color){ 22, 33, 56, 255 };
    Color tileB       = (Color){ 26, 38, 64, 255 };
    Color headerColor = (Color){ 30, 41, 59, 255 };    // Slate 800
    Color accent      = (Color){ 52, 211, 153, 255 };  // Mint
    Color textColor   = (Color){ 241, 245, 249, 255 };
    Color gold        = (Color){ 251, 191, 36, 255 };

    ClearBackground(bgColor);

    // Checkerboard play field
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            DrawRectangle(x * CELL_SIZE, TOP_BAR_HEIGHT + y * CELL_SIZE, CELL_SIZE, CELL_SIZE,
                          ((x + y) % 2 == 0) ? tileA : tileB);
        }
    }

    // Header bar with accent line
    DrawRectangle(0, 0, SCREEN_WIDTH, TOP_BAR_HEIGHT, headerColor);
    DrawRectangle(0, TOP_BAR_HEIGHT - 3, SCREEN_WIDTH, 3, accent);

    char scoreBuffer[32];
    snprintf(scoreBuffer, sizeof(scoreBuffer), "SCORE  %d", game->score);
    DrawText(scoreBuffer, 20, 10, 20, textColor);

    DrawCenteredText("SNAKE", SCREEN_WIDTH / 2, 8, 24, accent);

    char highScoreBuffer[64];
    snprintf(highScoreBuffer, sizeof(highScoreBuffer), "BEST  %d", game->highScore);
    DrawText(highScoreBuffer, SCREEN_WIDTH - 20 - MeasureText(highScoreBuffer, 20), 10, 20, gold);

    DrawFood(&game->food, CELL_SIZE, TOP_BAR_HEIGHT);
    DrawSnake(&game->snake, CELL_SIZE, TOP_BAR_HEIGHT);

    if (game->isGameOver) {
        // Dim the board
        DrawRectangle(0, TOP_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - TOP_BAR_HEIGHT, Fade(BLACK, 0.55f));

        // Centered panel
        Rectangle panel = { SCREEN_WIDTH / 2.0f - 200, SCREEN_HEIGHT / 2.0f - 100, 400, 210 };
        DrawRectangleRounded(panel, 0.15f, 8, headerColor);
        DrawRectangleRoundedLines(panel, 0.15f, 8, (Color){ 239, 68, 68, 255 });

        int cx = SCREEN_WIDTH / 2;
        int top = (int)panel.y;
        DrawCenteredText("GAME OVER", cx, top + 25, 40, (Color){ 239, 68, 68, 255 });

        char finalScoreBuffer[64];
        snprintf(finalScoreBuffer, sizeof(finalScoreBuffer), "Score: %d", game->score);
        DrawCenteredText(finalScoreBuffer, cx, top + 85, 24, textColor);

        char bestBuffer[64];
        snprintf(bestBuffer, sizeof(bestBuffer), "Best: %d", game->highScore);
        DrawCenteredText(bestBuffer, cx, top + 115, 20, gold);

        // Blinking restart hint
        if ((int)(GetTime() * 2) % 2 == 0) {
            DrawCenteredText("Press ENTER or SPACE to restart", cx, top + 165, 18, (Color){ 148, 163, 184, 255 });
        }
    }
}
