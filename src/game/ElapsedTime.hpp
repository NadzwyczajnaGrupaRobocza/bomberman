#pragma once

#include <chrono>
#include <boost/serialization/strong_typedef.hpp>

BOOST_STRONG_TYPEDEF(std::chrono::milliseconds, ElapsedTime)
