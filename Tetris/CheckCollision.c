#include "Tetris.h"

extern int stage[];

int CheckCollision(const int tetrominoStartX, const int tetrominoStartY, const int *tetromino)
{
    for(int y = 0; y < TETROMINO_SIZE; y++)
    {
        for(int x = 0; x < TETROMINO_SIZE; x++)
        {
            const int offset = y * TETROMINO_SIZE + x;

            if(tetromino[offset] == 1)
            {
                const int offset_stage = (y + tetrominoStartY) * STAGE_WIDTH + (x + tetrominoStartX);

                if (stage[offset_stage] != 0)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

int IsGameOver(int tetrominoX, int tetrominoY, const int *tetromino)
{
    for (int y = 0; y < TETROMINO_SIZE; y++) {
        for (int x = 0; x < TETROMINO_SIZE; x++) {
            const int offset = y * TETROMINO_SIZE + x;

            if (tetromino[offset] == 1) {
                const int stageX = x + tetrominoX;
                const int stageY = y + tetrominoY;

                if (stageX < 0 || stageX >= STAGE_WIDTH || stageY >= STAGE_HEIGHT || (stageY >= 0 && stage[stageY * STAGE_WIDTH + stageX] != 0)) {
                    return 1; // Collisione, game over
                }
            }
        }
    }

    return 0; // Il gioco continua
}