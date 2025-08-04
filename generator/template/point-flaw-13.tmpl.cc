#include "std_testcase.h"

%DEFINE%

%RETTYPE% %TYPE%__%DESC%_13_bad(%PARAM%) {
  if (GLOBAL_CONST_FIVE == 5) {
    %BADCODE%
  }
}

/* good1() uses if(GLOBAL_CONST_FIVE!=5) instead of if(GLOBAL_CONST_FIVE==5) */
%RETTYPE% %TYPE%__%DESC%_13_good1(%PARAM%) {
  if (GLOBAL_CONST_FIVE != 5) {
    /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
    printLine("Benign, fixed string");
  } else {
    %GOODCODE%
  }
}

/* good2() reverses the bodies in the if statement */
%RETTYPE% %TYPE%__%DESC%_13_good2(%PARAM%) {
  if (GLOBAL_CONST_FIVE == 5) {
    %GOODCODE%
  }
}
