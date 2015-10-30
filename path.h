#pragma once

#include "stdafx.h"
#include "registry.h"

class Path {
public:
  Path();
  std::vector<std::string> GetPath();
  void Reload();

  void SetPath(std::string path);
  bool UpdatePath(std::string path);

  static const std::string version;
private:
  std::unique_ptr<Registry> reg;
  std::string path;
};
