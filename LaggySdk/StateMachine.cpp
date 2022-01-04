#include "stdafx.h"
#include "StateMachine.h"

#include "Contracts.h"
#include "ITransition.h"


namespace Sdk
{
  namespace
  {
    bool sameStates(const std::shared_ptr<IState>& i_left, const std::shared_ptr<IState>& i_right)
    {
      return i_left.get() == i_right.get();
    }

  } // anonym NS


  void StateMachine::check()
  {
    if (!d_currentState)
      return;

    for (const auto& transition : d_transitions)
    {
      if (sameStates(d_currentState, transition->getSourceState()))
      {
        transit(*transition);
        break;
      }
    }
  }


  void StateMachine::addTransition(std::shared_ptr<ITransition> i_transition)
  {
    d_transitions.push_back(std::move(i_transition));
  }

  void StateMachine::setCurrentState(std::shared_ptr<IState> i_state)
  {
    d_currentState = std::move(i_state);
  }


  void StateMachine::transit(const ITransition& i_transition)
  {
    CONTRACT_EXPECT(!d_currentState || sameStates(i_transition.getSourceState(), d_currentState));
    setCurrentState(i_transition.getDestState());
  }

} // ns Sdk
