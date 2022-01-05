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

} // ns Sdk
