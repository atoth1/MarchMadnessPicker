#ifndef PICKER_CONSTANTS_HPP
#define PICKER_CONSTANTS_HPP

#include <string_view>

namespace picker {
inline constexpr std::string_view TRACE_LABEL = "trace";
inline constexpr std::string_view DEBUG_LABEL = "debug";
inline constexpr std::string_view INFO_LABEL = "info";
inline constexpr std::string_view WARNING_LABEL = "warning";
inline constexpr std::string_view ERROR_LABEL = "error";
inline constexpr std::string_view CRITICAL_LABEL = "critical";
inline constexpr std::string_view OFF_LABEL = "off";

inline constexpr std::string_view FILE_OUT_STRATEGY_LABEL = "file";
inline constexpr std::string_view STD_OUT_STRATEGY_LABEL = "stdout";

inline constexpr std::string_view MERSENNE_TWISTER_STRATEGY_LABEL = "mersenne-twister";
inline constexpr std::string_view MINSTD_RAND_STRATEGY_LABEL = "minstd-rand";
inline constexpr std::string_view STD_RAND_STRATEGY_LABEL = "std-rand";

inline constexpr std::string_view COIN_FLIP_STRATEGY_LABEL = "coin-flip";
inline constexpr std::string_view RANK_DETERMINISTIC_STRATEGY_LABEL = "rank-deterministic";
inline constexpr std::string_view SPREAD_BASED_STRATEGY_LABEL = "spread-based";

}// namespace picker

#endif