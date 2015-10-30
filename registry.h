#pragma once
#pragma comment(lib, "advapi32")

#include "stdafx.h"
#include "windows.h"

class Registry
{
public:
  Registry();

  std::string getPath();
  bool setPath(const std::string& value);

private:
  std::string getRegKey(const std::string& location, const std::string& name);
  bool setRegKey(const std::string& location, const std::string& name, const std::string& value);
};
