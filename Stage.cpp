#include "cprocessing.h"
#include "Stage.h"

void Stage_init()
{
}

void Stage_update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0,0,0,255));
    // CP_Graphics_DrawRect(100, 100, 10, 10);
    
    Draw_tiles();
}

void Stage_exit()
{

}

void Draw_tiles()
{
    CP_Settings_Fill(CP_Color_Create(255,0,255,255)); //타일 색
    const int row_pcs = 40, col_pcs = 121, tile_size = 10, gap = 10;
    const int startX = 50, startY = 50;
    const int holeX = row_pcs - 5, holeY = col_pcs / 2;

    for(int row=0; row<row_pcs; row++)
    {
        for(int col=0; col<col_pcs; col++)
        {
            if(row == 0 || row == row_pcs-1 || col == 0 || col == col_pcs-1 
                || (row >= holeX && col == holeY-1) || (row >= holeX && col == holeY+1)) 
                {
                    CP_Settings_Fill(CP_Color_Create(80, 80, 80, 255));
                    // Wall 판정 추가
                }
            else 
            {
                CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
            }
            
            if(row >= holeX && col == holeY) continue;

            CP_Graphics_DrawRect
            (
                startX + (col * gap),
                startY + (row * gap),
                tile_size,
                tile_size
            );

        }
    }
}
