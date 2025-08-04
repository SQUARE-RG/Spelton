#include "std_testcase.h"

%DEFINE%

%RETTYPE% %TYPE%__%DESC%_10_bad(%PARAM%) {
  if (globalTrue) {
    %BADCODE%
  }
}

/* good1() uses if(globalFalse) instead of if(globalTrue) */
%RETTYPE% %TYPE%__%DESC%_10_good1(%PARAM%) {
  if (globalFalse) {
    /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
    printLine("Benign, fixed string");
  } else {
    %GOODCODE%
  }
}

/* good2() reverses the bodies in the if statement */
%RETTYPE% %TYPE%__%DESC%_10_good2(%PARAM%) {
  if (globalTrue) {
    %GOODCODE%
  }
}
