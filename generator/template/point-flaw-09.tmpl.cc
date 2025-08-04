#include "std_testcase.h"

%DEFINE%

%RETTYPE% %TYPE%__%DESC%_09_bad(%PARAM%) {
  if (GLOBAL_CONST_TRUE) {
    %BADCODE%
  }
}

/* good1() uses if(GLOBAL_CONST_FALSE) instead of if(GLOBAL_CONST_TRUE) */
%RETTYPE% %TYPE%__%DESC%_09_good1(%PARAM%) {
  if (GLOBAL_CONST_FALSE) {
    /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
    printLine("Benign, fixed string");
  } else {
    %GOODCODE%
  }
}

/* good2() reverses the bodies in the if statement */
%RETTYPE% %TYPE%__%DESC%_09_good2(%PARAM%) {
  if (GLOBAL_CONST_TRUE) {
    %GOODCODE%
  }
}
