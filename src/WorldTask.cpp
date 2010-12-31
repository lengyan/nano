#include "WorldTask.h"

/**
 * 世界运行线程
 * */
int WorldTask::svc(void) {
    while(1) {
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("world thread run\n")));
        ACE_OS::sleep(4);
    }
}
