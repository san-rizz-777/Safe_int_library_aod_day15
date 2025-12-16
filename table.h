#pragma once
#include "./VariadicTable.h"
#include <tuple>

template<typename T, typename U>
using Row = std::tuple<std::string, T, U, std::string, std::string>;

template<typename T, typename U>
using Table = VariadicTable<std::string, T, U, std::string, std::string>;
