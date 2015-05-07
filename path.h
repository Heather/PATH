#pragma once

#include "stdafx.h"

class Path {
public:
  Path();
  std::vector<std::string> GetPath();
  void Reload();
  void SetPath(std::string path);
  static const std::string version;
private:
  std::string path;
};
