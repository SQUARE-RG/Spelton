#include "std_testcase.h"

%DEFINE%

%RETTYPE% %TYPE%__%DESC%_16_bad(%PARAM%) {
  while (1) {
    %BADCODE%
    break;
  }
}

/* good1() uses the GoodSinkBody in the while loop */
%RETTYPE% %TYPE%__%DESC%_16_good1(%PARAM%) {
  while (1) {
    %GOODCODE%
    break;
  }
}
