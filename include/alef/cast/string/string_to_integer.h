#ifndef ALEF_CAST_STRING_STRING_TO_INTEGER_H
#define ALEF_CAST_STRING_STRING_TO_INTEGER_H

#include "../macro.h"

#include "alef/concepts.h"
#include "alef/numerics.h"
#include "alef/string.h"
#include "alef/utility.h"

ALEF_GLOBAL_NAMESPACE_BEGIN

namespace __detail::cast {

// Safely converts to integer value.
template<integer T>
static std::optional<T> safely_convert_string_to_integer(
    const std::string& value,
    T (*func)(const std::string&, usize*, int),
    const num::radix_flag radix)
{
    try {
        return func(value, nullptr, scast(int, radix));
    } catch (std::invalid_argument&) {
    } catch (std::out_of_range&) { }

    return std::nullopt;
}

} // namespace __detail::cast

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
    return __detail::cast::safely_convert_string_to_integer(value, std::stoi, radix);
}

template<>
std::optional<uint32> string_to(const std::string& value, num::radix_flag radix) = delete;

template<>
std::optional<int64> string_to(const std::string& value, num::radix_flag radix) {
#ifdef ALEF_LONG64
    return __detail::cast::safely_convert_string_to_integer(value, std::stol, radix);
#else
    return __detail::cast::safely_convert_string_to_integer(value, std::stoll, radix);
#endif
}

template<>
std::optional<uint64> string_to(const std::string& value, num::radix_flag radix) {
#ifdef ALEF_LONG64
    return __detail::cast::safely_convert_string_to_integer(value, std::stoul, radix);
#else
    return __detail::cast::safely_convert_string_to_integer(value, std::stoull, radix);
#endif
}

ALEF_GLOBAL_NAMESPACE_END

#endif // ALEF_CAST_STRING_STRING_TO_INTEGER_H
