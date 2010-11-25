#include "ace/Log_Msg.h"


int ACE_TMAIN(int argc, ACE_TCHAR **argv) {
	ACE_DEBUG((LM_INFO, ACE_TEXT("HI Nano\n")));

	getchar();
	return 0;
}