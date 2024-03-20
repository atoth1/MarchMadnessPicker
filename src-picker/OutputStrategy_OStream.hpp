#ifndef PICKER_OUTPUT_STRATEGY_OSTREAM_HPP
#define PICKER_OUTPUT_STRATEGY_OSTREAM_HPP

#include <ostream>

#include "OutputStrategy.hpp"

namespace picker {

struct Bracket;

class OutputStrategy_OStream : public picker::OutputStrategy
{
public:
  explicit OutputStrategy_OStream(std::ostream* inOut) : out(inOut) {}

  void writeOutput(const Bracket& bracket) const override;

private:
  std::ostream* out;
};

}// namespace picker

#endif