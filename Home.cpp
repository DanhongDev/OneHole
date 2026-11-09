#include "Home.h"
#include "cprocessing.h"
#include "Stage.h"
#include "WinodwConfig.h"

// 나중에 게임시작, 설정, 게임종료 버튼등이 있는 게임 홈화면 용도

void home_init()
{
	CP_System_SetWindowSize((int)window_config.width, (int)window_config.height);
	CP_System_SetWindowTitle("OneHole");

}
void home_update()
{
	CP_Engine_SetNextGameState(stage_init, stage_update, stage_exit);
}
void home_exit()
{

}