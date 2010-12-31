#include "World.h"
#include "utils/Config.h"
#include "ace/CDR_Stream.h"
#include "ace/Basic_Types.h"
#include "WorldTask.h"
#include <vector>

int ACE_TMAIN(int argc, ACE_TCHAR **argv) {
    ACE_OutputCDR cdr;
    cdr << (ACE_CDR::UShort)1;
    cdr << (ACE_INT64)1;
    cdr << (ACE_CDR::Long)2;
    cdr << 'a';
    cdr << "中文";
    ACE_HEX_DUMP((LM_DEBUG, cdr.buffer(), cdr.length(), "recv:"));
    WorldTask task;
    task.activate();
    sConfig->open("nano.ini");
    sWorld->init();
    sWorld->run();
	return 0;
}
