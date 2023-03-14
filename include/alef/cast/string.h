#ifndef ALEF_STRING_CAST_H
#define ALEF_STRING_CAST_H

#include "alef/alef.h"
#include "alef/concepts.h"
#include "alef/numerics/radix.h"
#include "alef/string.h"
#include "alef/utility.h"

ALEF_GLOBAL_NAMESPACE_BEGIN

namespace __detail {

// Safely converts to integer value.
template<integer T>
static std::optional<T> safe_convert_string_to_integer(
    const std::string& value,
    T (* func)(const std::string&, std::size_t*, int),
    const num::radix_flag radix)
{
    try {
        return func(value, nullptr, static_cast<int>(radix));
    } catch (std::invalid_argument&) {
    } catch (std::out_of_range&) { }

    return std::nullopt;
}

// Safely converts to floating point value.
template<floating_point T>
static std::optional<T> safe_convert_string_to_floating_point(
    const std::string& value,
    T (* func)(const std::string&, std::size_t*))
{
    try {
        return func(value, nullptr);
    } catch (std::invalid_argument&) {
    } catch (std::out_of_range&) { }

    return std::nullopt;
}

} // namespace __detail

// Integer -----------------------------------------------------------------------------------------
template<integer T>
static std::optional<T> string_to(
    const std::string& value,
    num::radix_flag radix = num::radix_flag::decimal);

template<>
std::optional<int8> string_to(const std::string& value, num::radix_flag radix) = delete;

template<>
std::optional<uint8> string_to(const std::string& value, num::radix_flag radix) = delete;

template<>
std::optional<int16> string_to(const std::string& value, num::radix_flag radix) = delete;

template<>
std::optional<uint16> string_to(const std::string& value, num::radix_flag radix) = delete;

template<>
std::optional<int32> string_to(const std::string& value, num::radix_flag radix) {
    return __detail::safe_convert_string_to_integer(value, std::stoi, radix);
}

template<>
std::optional<uint32> string_to(const std::string& value, num::radix_flag radix) = delete;

template<>
std::optional<int64> string_to(const std::string& value, num::radix_flag radix) {
#ifdef ALEF_LONG64
    return __detail::safe_convert_string_to_integer(value, std::stol, radix);
#else
    return __detail::safe_convert_string_to_integer(value, std::stoll, radix);
#endif
}

template<>
std::optional<uint64> string_to(const std::string& value, num::radix_flag radix) {
#ifdef ALEF_LONG64
    return __detail::safe_convert_string_to_integer(value, std::stoul, radix);
#else
    return __detail::safe_convert_string_to_integer(value, std::stoull, radix);
#endif
}

// Floating point ----------------------------------------------------------------------------------
template<floating_point T>
static std::optional<T> string_to(const std::string& value);

template<>
std::optional<float> string_to(const std::string& value) {
    return __detail::safe_convert_string_to_floating_point(value, std::stof);
}

template<>
std::optional<double> string_to(const std::string& value) {
    return __detail::safe_convert_string_to_floating_point(value, std::stod);
}

template<>
std::optional<long double> string_to(const std::string& value) {
    return __detail::safe_convert_string_to_floating_point(value, std::stold);
}

ALEF_GLOBAL_NAMESPACE_END

#endif // ALEF_STRING_CAST_H
