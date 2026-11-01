#include<raylib.h>
#include"game.h"

int main(){

    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Snake Game");
    SetTargetFPS(60);

    struct Game game;
    InitGame(&game);

    while(!WindowShouldClose()){
        UpdateGame(&game);
        BeginDrawing();
        DrawGame(&game);
        EndDrawing();
    }

    CloseWindow();

}