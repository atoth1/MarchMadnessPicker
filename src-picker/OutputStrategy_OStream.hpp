#ifndef PICKER_OUTPUT_STRATEGY_OSTREAM_HPP
#define PICKER_OUTPUT_STRATEGY_OSTREAM_HPP

#include <ostream>

#include "OutputStrategy.hpp"

namespace picker {

struct Bracket;

class OStreamStrategy : public picker::OutputStrategy
{
public:
  explicit OStreamStrategy(std::ostream* inOut) : out(inOut) {}

  void writeOutput(const Bracket& bracket) const override;

private:
  std::ostream* out;
};

}// namespace picker

#endif