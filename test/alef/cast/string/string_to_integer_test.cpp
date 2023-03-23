#include "alef/cast/string.h"
#include "alef/utility.h"

#include <gtest/gtest.h>

TEST(alef_cast, string_to_integer_correct) {
    auto string = "256";
    auto number = alf::string_to<alf::int32>(string);

    EXPECT_TRUE(number.has_value());
    EXPECT_EQ(number.value(), alf::int32{256});
}

TEST(alef_cast, string_to_integer_incorrect) {
    auto str_number = "abc";
    auto number = alf::string_to<alf::int32>(str_number);

    EXPECT_FALSE(number.has_value());
}
