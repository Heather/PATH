#include "path.h"

#include <algorithm>

#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>

const std::string Path::version = "PATH v.0.0.7";

Path::Path() {
  reg = std::make_unique<Registry>();
  path = reg->getPath();
}

/// <summary>
/// Return sorted unique strings of path
/// </summary>
std::vector<std::string> Path::GetPath() {
  std::vector<std::string> strs;
  boost::split(strs, path, boost::is_any_of(";"));
  std::sort(strs.begin(), strs.end());
  strs.erase(std::unique(strs.begin(), strs.end()), strs.end());
  strs.erase(std::remove_if(strs.begin(), strs.end(),
    boost::bind(&std::string::empty, _1 )), strs.end());
  return strs;
}

void Path::Reload() {
  path = reg->getPath();
}

void Path::SetPath(std::string _path) {
  path = _path;
}

bool Path::UpdatePath(std::string _path) {
  return reg->setPath(_path);
}
