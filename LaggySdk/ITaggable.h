#pragma once

#include <string>


namespace Sdk
{
  class ITaggable
  {
  public:
    virtual ~ITaggable() = default;

    void setTag(std::string i_tag) { d_tag = std::move(i_tag); }
    const std::string& getTag() const { return d_tag; }

  private:
    std::string d_tag;
  };

} // Sdk
