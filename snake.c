#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20
#define MAX_LENGTH 400

int gameOver;
int score;
int snakeX[MAX_LENGTH];
int snakeY[MAX_LENGTH];
int snakeLength;
int foodX, foodY;
int dirX, dirY;

void setup() {
    gameOver = 0;
    score = 0;
    snakeLength = 3;
    snakeX[0] = 5;
    snakeY[0] = 5;
    snakeX[1] = 4;
    snakeY[1] = 5;
    snakeX[2] = 3;
    snakeY[2] = 5;

    dirX = 1;
    dirY = 0;

    srand(time(NULL));
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}

void draw() {
    system("cls");

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int print = 0;

            if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1) {
                printf("#");
                print = 1;
            }

            for (int i = 0; i < snakeLength; i++) {
                if (snakeX[i] == x && snakeY[i] == y) {
                    printf("O");
                    print = 1;
                    break;
                }
            }

            if (foodX == x && foodY == y) {
                printf("*");
                print = 1;
            }

            if (!print)
                printf(" ");
        }
        printf("\n");
    }

    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        char key = _getch();

        switch (key) {
            case 'a':
                if (dirX != 1) { dirX = -1; dirY = 0; }
                break;
            case 'd':
                if (dirX != -1) { dirX = 1; dirY = 0; }
                break;
            case 'w':
                if (dirY != 1) { dirX = 0; dirY = -1; }
                break;
            case 's':
                if (dirY != -1) { dirX = 0; dirY = 1; }
                break;
            case 'x':
                gameOver = 1;
                break;
        }
    }
}

void update() {
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    snakeX[0] += dirX;
    snakeY[0] += dirY;

    if (snakeX[0] == 0 || snakeY[0] == 0 || snakeX[0] == WIDTH - 1 || snakeY[0] == HEIGHT - 1) {
        gameOver = 1;
    }

    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameOver = 1;
        }
    }

    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        score += 10;
        snakeLength++;
        foodX = rand() % (WIDTH - 2) + 1;
        foodY = rand() % (HEIGHT - 2) + 1;
    }
}

int main() {
    setup();

    while (!gameOver) {
        draw();
        input();
        update();
        for (long i = 0; i < 10000000; i++);
    }

    printf("\nGame Over! Final score: %d\n", score);
    return 0;
}
