#pragma once

#include "SdkFwd.h"


namespace Sdk
{
  class StateMachine
  {
  public:
    void check();

    void addTransition(std::shared_ptr<ITransition> i_transition);
    void setCurrentState(std::shared_ptr<IState> i_state);

  private:
    std::vector<std::shared_ptr<ITransition>> d_transitions;
    std::shared_ptr<IState> d_currentState;

    void transit(const ITransition& i_transition);
  };

} // ns Sdk
