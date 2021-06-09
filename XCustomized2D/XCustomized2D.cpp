#include "EngineFramework.h"
int main()
{
	EngineFramework *pFramework = EngineFramework::getInstance();
	pFramework->FrameInit();
	pFramework->FrameLoop();
	pFramework->FrameFinalize();

}