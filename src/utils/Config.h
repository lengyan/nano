#include "ace/Configuration.h"
#include "ace/Configuration_Import_Export.h"
#include "ace/Singleton.h"

class Config
{
    friend class ACE_Singleton<Config, ACE_Recursive_Thread_Mutex>;
    public:
        int getString(const ACE_TCHAR *subSection, const ACE_TCHAR *name, ACE_TString &value);
        int getInteger(const ACE_TCHAR *subSection, const ACE_TCHAR *name, u_int &value);
        int open(const ACE_TCHAR *filename);
        int close();
        Config();
        virtual ~Config();
    private:
        ACE_Configuration_Section_Key root_key;
        ACE_Ini_ImpExp *impExp;
        ACE_Configuration_Heap config;
};

#define sConfig ACE_Singleton<Config, ACE_Recursive_Thread_Mutex>::instance()
