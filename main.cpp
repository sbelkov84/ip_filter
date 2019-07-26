#include "ip_getter.h"

int main(int, char**)
{
  TResultSet sSortedIps;
  TResultSet sOfMagicNum; // also sorted. Don't want long variable name
  FillIpsSets(sSortedIps, sOfMagicNum);

  WriteToFile(sSortedIps);
  std::vector<int> vLowerBound {1, 255, 255, 255};
  WriteByCondition(sSortedIps, &vLowerBound);

  vLowerBound = {46, 70, 255, 255};
  std::vector<int> vUpperBound {46, 70, 1, 1};
  WriteByCondition(sSortedIps, &vLowerBound, &vUpperBound);

  WriteToFile(sOfMagicNum);

  return 0;
}
//------------------------------------------------------------------------
