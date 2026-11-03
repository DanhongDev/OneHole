#include <vector>

using namespace std;

#include "cprocessing.h"
#include "Block.h"

namespace // 익명namespace: 이 파일 안에서만 쓸 변수와 함수를 묶어 두는 용도
{
    vector<vector<Block>> blocks;

    const int rows = 40, cols = 121;
    const int startX = 50, startY = 50;
    const int gap = 10;
    const int block_size = 10;
}

void block_init()
{
    blocks.clear();
    blocks.resize(rows);

    const int hole_row = rows - 5;
    const int hole_col = cols / 2;

    for(int row=0; row<rows; row++)
    {
        blocks[row].reserve(cols);
        for(int col=0; col<cols; col++)
        {
            const bool is_hole = row >= hole_row && col == hole_col;
            if(is_hole) continue;

            bool isWall = false;
            if(row == 0 || row == rows - 1 || col == 0 || col == cols - 1) isWall = true;
            else if(row >= hole_row && (col == hole_col - 1 || col == hole_col + 1)) isWall = true;
            else isWall = false;

            blocks[row].push_back(Block(startX + (col * gap), startY + (row * gap), isWall));
        }
    }
}

void block_update()
{
    for(const auto &row : blocks)
    {
        for(const Block &block : row)
        {
            block.draw();
        }
    }
}

void block_exit()
{
    blocks.clear();
}

// 생성자
Block::Block(int x, int y, bool isWall) : x(x), y(y), isWall(isWall), isAlive(true) {}

// 멤버 함수 정의
void Block::draw() const
{
    if(!isAlive) return;

    CP_Settings_Fill(isWall ? CP_Color_Create(80, 80, 80, 255) : CP_Color_Create(255, 255, 255, 255));

    CP_Graphics_DrawRect(x, y, 10, 10);
}