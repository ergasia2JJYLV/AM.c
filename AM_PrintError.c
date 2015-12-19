#include <stdio.h>
#include "AM.h"

int AM_errno;

void AM_PrintError(const char *errString)
{
    printf("%s\n",errString);
    switch (AM_errno) {
      //add more 
      case AME_EOF:
        printf("No more entries\n");
        break;
      case -2:
        printf("Error creating file\n",);
        break;
      case -3:
        printf("Error opening file\n");
        break;
      case -4:
        printf("Error destroying file from disc\n");
        break:
      case -5:
        printf("Error closing file\n");
        break;
      case -6:
        printf("Error inserting entry to file\n");
        break;
      case -7:
        printf("OpenIndexScan array if full\n");
        break;
      case -8:
        printf("Error terminating a scan on file\n");
        break;
      default:
        break;
    }
}
