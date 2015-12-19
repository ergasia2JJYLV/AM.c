#include "AM.h"
#include <stdio.h>



struct ScanInfo{  //insert more usefull info for scans later
  int i;
};
typedef struct ScanInfo ScanInfo;

ScanInfo scans[MAXOPENSCANS];

int AM_CloseIndexScan(int scanDesc)
{
  for (int i=0;i<MAXOPENSCANS;i++)
  {
    if(scans[i].i==scanDesc)
    {
      //
      scans[i].i=0;
      return AME_OK;
    }
  }
  return AME_ERROR_CLOSE_INDEX_SCAN;
}
