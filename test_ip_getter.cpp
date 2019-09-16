#include "ip_getter.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//------------------------------------------------------------------------

TEST(ip_filter, NotIpByRegexRes)
{
  bool Res;
  std::string NotIpStr = "aaa.999.xxx.0";
  std::tie(Res, std::ignore) = ContainsIp(NotIpStr);
  ASSERT_EQ(Res, false);
}
//------------------------------------------------------------------------

// need this check, because ip-address could be correct since 2nd symbol of input line 
TEST(ip_filter, Bad1stByteIpRes)
{
  bool Res;
  std::string BadIpStr = "892.22.123.7";
  std::tie(Res, std::ignore) = ContainsIp(BadIpStr);
  ASSERT_EQ(Res, false);
}
//------------------------------------------------------------------------

TEST(ip_filter, GoodIpRes)
{
  bool Res;
  std::string GoodIpStr = "192.22.123.7";
  std::tie(Res, std::ignore) = ContainsIp(GoodIpStr);
  ASSERT_EQ(Res, true);
}
//------------------------------------------------------------------------

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  int Res = RUN_ALL_TESTS();
  return Res;
}