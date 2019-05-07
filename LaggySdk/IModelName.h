#pragma once

#include <string>


namespace Sdk
{
  class IModelName
  {
  public:
    IModelName() : d_modelName("") { }
    virtual ~IModelName() = default;

    const auto& getModelName() const { return d_modelName; }
    void setModelName(std::string i_modelName) { d_modelName = std::move(i_modelName); }

  private:
    std::string d_modelName;
  };

} // ns Sdk
