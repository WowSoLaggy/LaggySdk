#pragma once

#include <filesystem>
#include <string>


namespace Sdk
{
  std::string getParentFolder(const std::string& i_fileName)
  {
    using namespace std::experimental::filesystem;
    return path(i_fileName).parent_path().string();
  }

  std::string getExtension(const std::string& i_fileName)
  {
    using namespace std::experimental::filesystem;
    return path(i_fileName).extension().string();
  }

} // ns Sdk
