#ifndef IP_GETTER_H
#define IP_GETTER_H

#include <string>
#include <set>
#include <vector>
#include <tuple>
//------------------------------------------------------------------------

// use std::greater instead of std::less and get reverse lexicographical sort
using TResultSet = std::multiset<std::vector<int>, std::greater<std::vector<int>>>;
//------------------------------------------------------------------------

const int gMagicNum = 46;
//------------------------------------------------------------------------

std::vector<int> ParseStrToIp(std::string& Str);

bool IsCorrect1stOctet(std::vector<int>& vIp);

std::tuple<bool, std::string> ContainsIp(std::string& Str);

void FillIpsSets(TResultSet& sSortedIps, TResultSet& sOfMagicNum);

void WriteByCondition(TResultSet& sSortedIps, std::vector<int>* vLowerBound = nullptr, std::vector<int>* vUpperBound = nullptr);

void WriteToFile(TResultSet& sSortedIps);
//------------------------------------------------------------------------

#endif // IP_GETTER_H
