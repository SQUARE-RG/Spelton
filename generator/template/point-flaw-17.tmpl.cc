#include "std_testcase.h"

%DEFINE%

%RETTYPE% %TYPE%__%DESC%_17_bad(%PARAM%) {
  int j;
  for (j = 0; j < 1; j++) {
    %BADCODE%
  }
}

/* good1() uses the GoodSinkBody in the for statements */
%RETTYPE% %TYPE%__%DESC%_17_good1(%PARAM%) {
  int k;
  for (k = 0; k < 1; k++) {
    %GOODCODE%
  }
}
