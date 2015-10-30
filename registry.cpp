#include "registry.h"

Registry::Registry()
{

}

std::string Registry::getPath() {
  return this->getRegKey(
        "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"
      , "Path");
}

bool Registry::setPath(const std::string& value) {
  return this->setRegKey(
        "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"
      , "Path"
      , value);
}

std::string Registry::getRegKey(const std::string& location, const std::string& name) {
  HKEY key;
  TCHAR value[4096];
  DWORD bufLen = 4096*sizeof(TCHAR);
  long ret;
  ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, location.c_str(), 0, KEY_QUERY_VALUE, &key);
  if(ret != ERROR_SUCCESS) {
    /// no path reg key?
    return std::getenv("PATH");
  }
  ret = RegQueryValueExA(key, name.c_str(), 0, 0, (LPBYTE) value, &bufLen);
  RegCloseKey(key);
  if ( (ret != ERROR_SUCCESS) || (bufLen > 4096*sizeof(TCHAR)) ) {
    /// can't open with some reason?
    return std::getenv("PATH");
  }
  std::string stringValue = (char*)value;
  size_t i = stringValue.length();
  while(i > 0 && stringValue[i-1] == '\0') {
    --i;
  }
  return stringValue.substr(0,i);
}

bool Registry::setRegKey(const std::string& location, const std::string& name, const std::string& value) {
  HKEY key;
  long ret;
  ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, location.c_str(), 0, KEY_ALL_ACCESS, &key);
  if(ret != ERROR_SUCCESS){
    return false;
  }
  ret = RegSetValueExA(key, name.c_str(), 0, REG_SZ, (LPBYTE) value.c_str()
                       , (DWORD)(value.size()*sizeof(TCHAR)));
  RegCloseKey(key);
  if (ret != ERROR_SUCCESS) {
    return false;
  }
  return true;
}
