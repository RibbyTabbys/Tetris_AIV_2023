#include <time.h>
#include <string.h>
#include "Tetris.h"
#include "tetromini_info.h"
#include "stage.h"
#include <stdio.h>
#include "color_types.h"

int score = 0;

int main(int argc, char** argv, char** environ)
{
    const int windowWidth = 700; 
    const int windowHeight = 600; 

    const int startOffsetX = (windowWidth / 4.2) - ((STAGE_WIDTH * TILE_SIZE) / 2);
    const int startOffsetY = (windowHeight / 2) - ((STAGE_HEIGHT * TILE_SIZE) / 2);

    const int tetrominoStartX = STAGE_WIDTH / 2;
    const int tetrominoStartY = 0;

    const float minTimeToMoveTetrominoDown = 0.2f;

    const int pointsNeededToFallFaster = 500;

    int gameOver = 0;

    int currentTetrominoX = tetrominoStartX;
    int currentTetrominoY = tetrominoStartY;

    time_t unixTime;

    time(&unixTime);

    SetRandomSeed(unixTime);

    int currentTetrominoType = GetRandomValue(0, 6);
    int currentRotation = 0;

    float moveTetrominoDownTimer = 1.f;
    float timeToMoveTetrominoDown = moveTetrominoDownTimer;
    int currentColor = GetRandomValue(0, 7);

    InitWindow(windowWidth, windowHeight, "Tetris");
    InitAudioDevice();

    const Music music = LoadMusicStream("Sounds/music.mp3");
    const Sound rotateSound = LoadSound("Sounds/rotating.wav");
    const Sound clearLineSound = LoadSound("Sounds/clear.wav");
    const Sound tetrominoPlacedSound = LoadSound("Sounds/landing.wav");
    const Sound moveSound = LoadSound("Sounds/moving.wav");

    SetTargetFPS(60);
    SetMusicVolume(music, 0.1f);

    while(!WindowShouldClose())
    {
        PlayMusicStream(music);
        UpdateMusicStream(music);

        timeToMoveTetrominoDown -= GetFrameTime();

        if (IsGameOver(currentTetrominoX, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation])) 
        {
            CloseWindow();
            break;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            const int lastRotation = currentRotation;

            currentRotation++;

            if (currentRotation > 3)
            {
                currentRotation = 0;
            }

            if (CheckCollision(currentTetrominoX,currentTetrominoY,tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                currentRotation = lastRotation;
            }
            else
            {
                PlaySound(rotateSound);
            }
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            if (!CheckCollision(currentTetrominoX+1,currentTetrominoY,tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                currentTetrominoX++;
                PlaySound(moveSound);
            }
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            if (!CheckCollision(currentTetrominoX-1,currentTetrominoY,tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                currentTetrominoX--;
                PlaySound(moveSound);
            }
        }

        if(timeToMoveTetrominoDown <= 0 || IsKeyPressed(KEY_DOWN))
        {            
            if(!CheckCollision(currentTetrominoX,currentTetrominoY+1,tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                currentTetrominoY++;
                timeToMoveTetrominoDown = moveTetrominoDownTimer;
                PlaySound(moveSound);
            }
            else
            {
                for(int y = 0; y < TETROMINO_SIZE; y++)
                {
                    for(int x = 0; x < TETROMINO_SIZE; x++)
                    {
                        const int offset = y * TETROMINO_SIZE + x;

                        const int *tetromino = tetrominoTypes[currentTetrominoType][currentRotation];

                        if(tetromino[offset] == 1)
                        {
                            const int offset_stage = (y + currentTetrominoY) * STAGE_WIDTH + (x + currentTetrominoX);

                            stage[offset_stage] = currentColor+1;
                        }
                    }
                }

                DeleteLines(clearLineSound);
                PlaySound(tetrominoPlacedSound);

                if(moveTetrominoDownTimer >= minTimeToMoveTetrominoDown && score >= pointsNeededToFallFaster && score % pointsNeededToFallFaster == 0)
                    moveTetrominoDownTimer -= 0.1f;

                currentTetrominoX = tetrominoStartX;
                currentTetrominoY = tetrominoStartY;

                currentTetrominoType = GetRandomValue(0, 6);
                currentRotation = 0;
                currentColor = GetRandomValue(0, 7);
            }
        }

        BeginDrawing();

        ClearBackground(BLUE);

        drawStage(startOffsetX, startOffsetY, colorTypes);

        drawScore(score);

        drawTetromino(colorTypes[currentColor],startOffsetX, startOffsetY, currentTetrominoX, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]);

        EndDrawing();
    }
    
    UnloadMusicStream(music);
    UnloadSound(rotateSound);
    UnloadSound(moveSound);
    UnloadSound(tetrominoPlacedSound);
    UnloadSound(clearLineSound);
    CloseAudioDevice();

    return 0;
}