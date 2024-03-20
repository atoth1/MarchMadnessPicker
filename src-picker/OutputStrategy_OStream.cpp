#include <ostream>

#include "Bracket.hpp"
#include "OutputStrategy_OStream.hpp"

void picker::OutputStrategy_OStream::writeOutput(const picker::Bracket& bracket) const { (*out) << bracket; }
