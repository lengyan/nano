#include "Config.h"

Config::Config():impExp(NULL) {


}

Config::~Config() {
    if (impExp)
        delete impExp;
    impExp = NULL;
}

int Config::open(const ACE_TCHAR *filename) {
    if (this->config.open() == -1)
        return -1;
    this->impExp  = new ACE_Ini_ImpExp(config);
    return this->impExp->import_config(filename);
}

int Config::getString(const ACE_TCHAR *subSection, const ACE_TCHAR *name, ACE_TString &value) {
    if (config.open_section(config.root_section(), ACE_TEXT(subSection), 0, this->root_key) == -1)
        return -1;
    return config.get_string_value(this->root_key, name, value);
}

int Config::getInteger(const ACE_TCHAR *subSection, const ACE_TCHAR *name, u_int &value) {
    ACE_TString strValue;
    if (config.open_section(config.root_section(), ACE_TEXT(subSection), 0, this->root_key) == -1)
        return -1;
    if (config.get_string_value(this->root_key, name, strValue) == -1)
        return -1;
    value = ACE_OS::atoi(strValue.c_str());
    if (value == 0 && strValue != "0")
        return -1;
    return value;
}

int Config::close() {
    if (impExp) {
       delete impExp;
       impExp = NULL;
    }
}
