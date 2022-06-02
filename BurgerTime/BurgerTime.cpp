#include "BurgerTimePCH.h"

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Stabulum.h"
#include "Game.h"

int main(int, char* []) {
	//Stabulum engine;
	Game engine;
	engine.Run();
	return 0;
}