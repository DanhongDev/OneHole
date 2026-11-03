#include "cprocessing.h"
#include "Home.h"
#include "Stage.h"
#include "WinodwConfig.h"

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