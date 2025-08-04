#include "std_testcase.h"

%DEFINE%

%RETTYPE% %TYPE%__%DESC%_03_bad(%PARAM%) {
  if (5 == 5) {
    %BADCODE%
  }
}

/* good1() uses if(5!=5) instead of if(5==5) */
%RETTYPE% %TYPE%__%DESC%_03_good1(%PARAM%) {
  if (5 != 5) {
    /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
    printLine("Benign, fixed string");
  } else {
    %GOODCODE%
  }
}

/* good2() reverses the bodies in the if statement */
%RETTYPE% %TYPE%__%DESC%_03_good2(%PARAM%) {
  if (5 == 5) {
    %GOODCODE%
  }
}
