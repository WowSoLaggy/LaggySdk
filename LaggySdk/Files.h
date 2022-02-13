#pragma once


namespace Sdk
{
  /// Read binary file from the given @i_filePath
  /// to the vector of unsigned chars (bytes)
  static std::vector<unsigned char> readBytes(const fs::path& i_filePath)
  {
    std::ifstream file(i_filePath.c_str(), std::ios::binary);

    file.seekg(0, std::ios::end);
    const auto length = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<unsigned char> buffer(length, 0);
    file.read((char*)buffer.data(), length);

    return buffer;
  }

  static fs::path getExePath()
  {
#ifdef _WIN32
    wchar_t path[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, path, MAX_PATH);
    return path;
#else
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return std::string(result, (count > 0) ? count : 0);
#endif
  }

  static fs::path getExeFolder()
  {
#ifdef _WIN32
    wchar_t path[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, path, MAX_PATH);
    return fs::path(path).parent_path();
#else
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return std::string(result, (count > 0) ? count : 0);
#endif
  }

} // ns Sdk
