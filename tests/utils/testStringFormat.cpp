#include <catch2/catch.hpp>

#include <aw/utils/stringFormat.hpp>

template <typename Type>
void testMakeNumberStringPretty(const std::string& input, const std::string& expected)
{
  using namespace aw::stringFormat;
  std::string copy = input;
  makeNumberStringPretty<Type>(copy);
  CHECK(copy == expected);
}

TEST_CASE("makeNumberStringPretty")
{
  SECTION("int")
  {
    SECTION("Valid numbers should stay the same")
    {
      testMakeNumberStringPretty<int>("0", "0");
      testMakeNumberStringPretty<int>("1", "1");
      testMakeNumberStringPretty<int>("-1", "-1");
      testMakeNumberStringPretty<int>("100", "100");
      testMakeNumberStringPretty<int>("-100", "-100");
      testMakeNumberStringPretty<int>("-0", "-0");
    }

    SECTION("Remove zeros in front of number")
    {
      testMakeNumberStringPretty<int>("00", "0");
      testMakeNumberStringPretty<int>("01", "1");
      testMakeNumberStringPretty<int>("001", "1");
      testMakeNumberStringPretty<int>("-01", "-1");
      testMakeNumberStringPretty<int>("-0001", "-1");
    }
  }

  SECTION("float")
  {
    SECTION("Valid numbers should stay the same")
    {
      testMakeNumberStringPretty<float>("0.0", "0.0");
      testMakeNumberStringPretty<float>("0", "0");
      testMakeNumberStringPretty<float>("1.0", "1.0");
      testMakeNumberStringPretty<float>("1", "1");
      testMakeNumberStringPretty<float>("-1.0", "-1.0");
      testMakeNumberStringPretty<float>("-1", "-1");
    }

    SECTION("Remove zeros in front of number")
    {
      testMakeNumberStringPretty<float>("00", "0");
      testMakeNumberStringPretty<float>("00.0", "0.0");
      testMakeNumberStringPretty<float>("01.0", "1.0");
      testMakeNumberStringPretty<float>("01", "1");
      testMakeNumberStringPretty<float>("-01.0", "-1.0");
      testMakeNumberStringPretty<float>("-01", "-1");
    }

    SECTION("Remove trailing zeros")
    {
      testMakeNumberStringPretty<float>("0.00", "0.0");
      testMakeNumberStringPretty<float>("1.00", "1.0");
      testMakeNumberStringPretty<float>("-1.00", "-1.0");
      testMakeNumberStringPretty<float>("1.100", "1.1");
      testMakeNumberStringPretty<float>("-1.100", "-1.1");
      testMakeNumberStringPretty<float>("1.1010", "1.101");
      testMakeNumberStringPretty<float>("-1.1010", "-1.101");
    }
  }
}
#include <iostream>

TEST_CASE("toPrettyString")
{
  // Only simple tests here, because it only uses std::to_string (no testing) and makeNumberStringPretty which is tested
  // above
  using namespace aw::stringFormat;
  SECTION("int")
  {
    CHECK(toPrettyString<int>(0) == "0");
    CHECK(toPrettyString<int>(1234) == "1234");
    CHECK(toPrettyString<int>(-1234) == "-1234");
  }

  SECTION("float")
  {
    CHECK(toPrettyString<float>(0.0f) == "0.0");
    CHECK(toPrettyString<float>(1234.f) == "1234.0");
    CHECK(toPrettyString<float>(-1234.f) == "-1234.0");
  }
}
