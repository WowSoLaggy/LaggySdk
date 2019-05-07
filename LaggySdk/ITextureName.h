#pragma once

#include <string>


namespace Sdk
{
  class ITextureName
  {
  public:
    ITextureName() : d_textureName("") { }
    virtual ~ITextureName() = default;

    const auto& getTextureName() const { return d_textureName; }
    void setTextureName(std::string i_textureName) { d_textureName = std::move(i_textureName); }

  private:
    std::string d_textureName;
  };

} // ns Sdk
