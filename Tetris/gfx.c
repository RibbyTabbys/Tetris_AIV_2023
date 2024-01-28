#include "Tetris.h"

extern int stage[];

void drawTetromino(const Color currentColor, const int startOffsetX, const int startOffsetY, const int tetrominoStartX, const int tetrominoStartY, const int *tetromino)
{
    for(int y = 0; y < TETROMINO_SIZE; y++)
    {
        for(int x = 0; x < TETROMINO_SIZE; x++)
        {
            const int offset = y * TETROMINO_SIZE + x;

            if(tetromino[offset] == 1)
            {
                DrawRectangle((x + tetrominoStartX) * TILE_SIZE + startOffsetX, (y + tetrominoStartY) * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, currentColor);
            }
        }
    }
}

void drawStage(const int startOffsetX, const int startOffsetY, const Color* colorTypes)
{
    for(int y = 0; y < STAGE_HEIGHT; y++)
    {
        for(int x = 0; x < STAGE_WIDTH; x++)
        {
            const int offset = y * STAGE_WIDTH + x;
            const int color = stage[offset];

            if(stage[offset] != 0)
            {
                DrawRectangle(x * TILE_SIZE + startOffsetX, y * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, colorTypes[color - 1]);
            }

            DrawRectangleLines(x * TILE_SIZE + startOffsetX, y * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, BLACK);
        }
    }
}

void drawScore(const int score)
{
    DrawText(TextFormat("Score: %d", score), 320, 50, 50, RED);
}