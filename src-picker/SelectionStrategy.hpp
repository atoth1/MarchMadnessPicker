#ifndef PICKER_SELECTION_STRATEGY_HPP
#define PICKER_SELECTION_STRATEGY_HPP

#include <string>

namespace picker {

class SelectionStrategy
{
public:
  virtual ~SelectionStrategy( ) = default;

  SelectionStrategy(const SelectionStrategy&) = delete;

  SelectionStrategy(SelectionStrategy&&) = delete;

  SelectionStrategy& operator=(const SelectionStrategy&) = delete;

  SelectionStrategy& operator=(SelectionStrategy&&) = delete;

  virtual std::string selectWinner(const std::string& team1, const std::string& team2) = 0;

protected:
  SelectionStrategy( ) = default;
};

}// namespace picker

#endif