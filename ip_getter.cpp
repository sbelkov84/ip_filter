#include "ip_getter.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <functional>
//------------------------------------------------------------------------

std::vector<int> ParseStrToIp(std::string& Str)
{
  std::vector<int> Res;
  Res.resize(4);
  sscanf(Str.c_str(), "%d.%d.%d.%d", &Res[0], &Res[1], &Res[2], &Res[3]);
  return Res;
}
//------------------------------------------------------------------------

bool IsCorrect1stOctet(std::vector<int>& vIp)
{
  return (vIp[0] >= 0) && (vIp[0] <= 255);
}
//------------------------------------------------------------------------

std::tuple<bool, std::string> ContainsIp(std::string& Str)
{
  std::tuple<bool, std::string> Result;
  std::regex Pat("((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[1]?\\d\\d?)");
  std::smatch Matches;
  bool IsHere = std::regex_search(Str, Matches, Pat);
  // if ip-address looks like correct, but not from line start, e.g. "392.168.0.1" returns Matches[0] = "92.168.0.1"
  // this case is checked by condition Matches.position(0) == 0 in if-statement below
  if (IsHere && Matches.position(0) == 0)
    Result = std::make_tuple(true, Matches[0]);
  else
    Result = std::make_tuple(false, "");
  //---
  return Result;
}
//------------------------------------------------------------------------

void FillIpsSets(TResultSet& sSortedIps, TResultSet& sOfMagicNum)
{
  for (std::string Line; getline(std::cin, Line); )
  {
    bool BoolRes;
    std::string ResStr;
    std::tie(BoolRes, ResStr) = ContainsIp(Line);
    if (BoolRes)
    {
      auto It = sSortedIps.emplace(ParseStrToIp(ResStr));
      // while emplacing ip-Vectors in main Multiset, emplace in another Multiset ip-Vectors, which contains byte == 46
      if (std::find((*It).begin(), (*It).end(), gMagicNum) != (*It).end())
        sOfMagicNum.emplace(*It);
    }
    else
    {
      continue;
    }
  }
}
//------------------------------------------------------------------------

void WriteByCondition(TResultSet& sSortedIps, std::vector<int>* vLowerBound, std::vector<int>* vUpperBound)
{
  auto BegIt = sSortedIps.cbegin();
  auto EndIt = sSortedIps.cend();

  if (vLowerBound != nullptr)
    BegIt = sSortedIps.lower_bound(*vLowerBound);

  if (vUpperBound != nullptr)
    EndIt = sSortedIps.upper_bound(*vUpperBound);

  for (auto It = BegIt; It != EndIt; ++It)
  {
    for (int i = 0; i < 3; ++i)
    {
      std::cout << (*It)[i] << ".";
    }
    std::cout << (*It)[3] << '\n';
  }
}
//------------------------------------------------------------------------

void WriteToFile(TResultSet& sSortedIps)
{
  WriteByCondition(sSortedIps);
}
//------------------------------------------------------------------------
