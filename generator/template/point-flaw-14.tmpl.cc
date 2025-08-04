#include "std_testcase.h"

%DEFINE%

%RETTYPE% %TYPE%__%DESC%_14_bad(%PARAM%) {
  if (globalFive == 5) {
    %BADCODE%
  }
}

/* good1() uses if(globalFive!=5) instead of if(globalFive==5) */
%RETTYPE% %TYPE%__%DESC%_14_good1(%PARAM%) {
  if (globalFive != 5) {
    /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
    printLine("Benign, fixed string");
  } else {
    %GOODCODE%
  }
}

/* good2() reverses the bodies in the if statement */
%RETTYPE% %TYPE%__%DESC%_14_good2(%PARAM%) {
  if (globalFive == 5) {
    %GOODCODE%
  }
}
