#include <ostream>

#include "Bracket.hpp"
#include "OutputStrategy_OStream.hpp"

void picker::OStreamStrategy::writeOutput(const picker::Bracket& bracket) const { (*out) << bracket; }
