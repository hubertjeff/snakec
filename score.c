#include"score.h"
#include<stdio.h>

int LoadHighScore(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    int highScore = 0;
    if (fscanf(file, "%d", &highScore) != 1) {
        highScore = 0;
    }

    fclose(file);
    return highScore;
}


void SaveHighScore(const char *filename, int highScore) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }

    fprintf(file, "%d\n", highScore);
    fclose(file);

}