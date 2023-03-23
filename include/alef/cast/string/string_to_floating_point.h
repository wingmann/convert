#ifndef ALEF_CAST_STRING_STRING_TO_FLOATING_POINT_H
#define ALEF_CAST_STRING_STRING_TO_FLOATING_POINT_H

#include "alef/concepts.h"
#include "alef/string.h"
#include "alef/utility.h"

ALEF_GLOBAL_NAMESPACE_BEGIN

namespace __detail::cast {

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

} // namespace __detail::cast

template<floating_point T>
static std::optional<T> string_to(const std::string& value);

template<>
std::optional<float> string_to(const std::string& value) {
    return __detail::cast::safe_convert_string_to_floating_point(value, std::stof);
}

template<>
std::optional<double> string_to(const std::string& value) {
    return __detail::cast::safe_convert_string_to_floating_point(value, std::stod);
}

template<>
std::optional<long double> string_to(const std::string& value) {
    return __detail::cast::safe_convert_string_to_floating_point(value, std::stold);
}

ALEF_GLOBAL_NAMESPACE_END

#endif // ALEF_CAST_STRING_STRING_TO_FLOATING_POINT_H
