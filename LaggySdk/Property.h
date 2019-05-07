#pragma once


namespace Sdk
{
  template <typename T>
  class Property
  {
  public:

    Property(T i_initialValue = T(0), T i_minValue = T(0), T i_maxValue = T(0))
    {
      set(i_initialValue, i_minValue, i_maxValue);
    }

    void set(T i_value = T(0), T i_minValue = T(0), T i_maxValue = T(0))
    {
      setValueMin(i_minValue);
      setValueMax(i_maxValue);
      setValue(i_value);
    }

    void setToMin()
    {
      d_value = d_valueMin;
    }

    void setToMax()
    {
      d_value = d_valueMax;
    }

    T getValue() const { return d_value; }
    void setValue(T i_value)
    {
      d_value =
        d_value < d_valueMin ? d_valueMin :
        d_value > d_valueMax ? d_valueMax :
        i_value;
    }

    T getValueMin() const { return d_valueMin; }
    void setValueMin(T i_valueMin)
    {
      d_valueMin = i_valueMin;
      if (d_value < d_valueMin)
        d_value = d_valueMin;
    }

    T getValueMax() const { return d_valueMax; }
    void setValueMax(T i_valueMax)
    {
      d_valueMax = i_valueMax;
      if (d_value > d_valueMax)
        d_value = d_valueMax;
    }

    double getValueRelative() const { return double(d_value - d_valueMin) / double(d_valueMax - d_valueMin); }

  private:

    T d_value;
    T d_valueMin;
    T d_valueMax;

  };

} // ns Sdk
