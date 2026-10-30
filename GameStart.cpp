#include "cprocessing.h"
#include "GameStart.h"
#include "Stage.h"

float window_width_size = 1280.f;
float window_height_size = 720.f;

void gamestart_init()
{
	CP_System_SetWindowSize((int)window_width_size, (int)window_height_size);
	CP_System_SetWindowTitle("OneHole");
}
void gamestart_update()
{
	Stage_update();
}
void gamestart_exit()
{

}