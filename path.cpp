#include "path.h"

#include <boost/algorithm/string.hpp>

const std::string Path::version = "PATH v.0.0.1";

Path::Path() {
  path = std::getenv("PATH");
}

std::vector<std::string> Path::GetPath() {
  std::vector<std::string> strs;
  boost::split(strs, path, boost::is_any_of(";"));
  return strs;
}

void Path::Reload() {
  path = std::getenv("PATH");
}

void Path::SetPath(std::string _path) {
  path = _path;
}
