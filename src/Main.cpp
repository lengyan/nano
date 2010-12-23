#include "World.h"
#include "utils/Config.h"

int ACE_TMAIN(int argc, ACE_TCHAR **argv) {
    sConfig->open("nano.ini");
    sWorld->init();
    sWorld->run();
	return 0;
}
