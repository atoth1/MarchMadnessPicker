#ifndef PICKER_OUTPUT_STRATEGY_HPP
#define PICKER_OUTPUT_STRATEGY_HPP

namespace picker {

struct Bracket;

class OutputStrategy
{
public:
  virtual ~OutputStrategy( ) = default;

  OutputStrategy(const OutputStrategy&) = delete;

  OutputStrategy(OutputStrategy&&) = delete;

  OutputStrategy& operator=(const OutputStrategy&) = delete;

  OutputStrategy& operator=(OutputStrategy&&) = delete;

  virtual void writeOutput(const Bracket& bracket) const = 0;

protected:
  OutputStrategy( ) = default;
};
}// namespace picker


#endif