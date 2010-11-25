// $Id: test_timestamp.cpp 91671 2010-09-08 18:39:23Z johnnyw $

// Test the ACE::timestamp method.

#include "ace/OS_main.h"
#include "ace/ACE.h"
#include "ace/Log_Msg.h"



int
ACE_TMAIN (int, ACE_TCHAR *[])
{
  ACE_TCHAR day_and_time[35];
  ACE::timestamp (day_and_time,
                  sizeof day_and_time);

  ACE_DEBUG ((LM_DEBUG, "%s", day_and_time));

  return 0;
}
