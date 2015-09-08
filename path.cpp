#include "path.h"

#include <algorithm>

#include <boost/algorithm/string.hpp>

const std::string Path::version = "PATH v.0.0.5";

Path::Path() {
  path = std::getenv("PATH");
}

/// <summary>
/// Return sorted unique strings of path
/// </summary>
std::vector<std::string> Path::GetPath() {
  std::vector<std::string> strs;
  boost::split(strs, path, boost::is_any_of(";"));
  std::sort(strs.begin(), strs.end());
  strs.erase(std::unique(strs.begin(), strs.end()), strs.end());
  return strs;
}

void Path::Reload() {
  path = std::getenv("PATH");
}

void Path::SetPath(std::string _path) {
  path = _path;
}
