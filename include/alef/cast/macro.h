#ifndef ALEF_CAST_MACRO_H
#define ALEF_CAST_MACRO_H

#define scast(type, value) static_cast<type>(value)
#define rcast(type, value) reinterpret_cast<type>(value)
#define ccast(type, value) const_cast<type>(value)
#define dcast(type, value) dynamic_cast<type>(value)

#endif // ALEF_CAST_MACRO_H
