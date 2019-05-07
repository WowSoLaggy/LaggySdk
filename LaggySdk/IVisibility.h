#pragma once


namespace Sdk
{
  class IVisibility
  {
  public:
    IVisibility() : d_isVisible(true) { }
    virtual ~IVisibility() = default;

    bool getVisibility() const { return d_isVisible; }
    void setVisibility(bool i_isVisible) { d_isVisible = i_isVisible; }

  private:
    bool d_isVisible;
  };

} // ns Sdk
