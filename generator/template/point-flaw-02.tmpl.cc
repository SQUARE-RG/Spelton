#include "std_testcase.h"

%DEFINE%

%RETTYPE% %TYPE%__%DESC%_02_bad(%PARAM%) {
  if (1) {
   %BADCODE%
  }
}

/* good1() uses if(0) instead of if(1) */
%RETTYPE% %TYPE%__%DESC%_02_good1(%PARAM%) {
  if (0) {
    /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
    printLine("Benign, fixed string");
  } else {
   %GOODCODE%
  }
}

/* good2() reverses the bodies in the if statement */
%RETTYPE% %TYPE%__%DESC%_02_good2(%PARAM%) {
  if (1) {
   %GOODCODE%
  }
}
