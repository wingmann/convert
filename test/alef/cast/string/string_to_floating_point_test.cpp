#include "alef/cast/string.h"

#include <gtest/gtest.h>

TEST(alef_cast, string_to_floating_point_correct) {
    auto str_number = "256.1024";
    auto number = alf::string_to<float>(str_number);

    EXPECT_TRUE(number.has_value());
    EXPECT_FLOAT_EQ(number.value(), float{256.1024});
}

TEST(alef_cast, string_to_floating_point_incorrect) {
    auto str_number = "abc.defg";
    auto number = alf::string_to<float>(str_number);

    EXPECT_FALSE(number.has_value());
}