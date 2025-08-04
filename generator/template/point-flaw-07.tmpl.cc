#include "std_testcase.h"

%DEFINE%

/* The variable below is not declared "const", but is never assigned
   any other value so a tool should be able to identify that reads of
   this will always give its initialized value. */
static int staticFive = 5;

%RETTYPE% %TYPE%__%DESC%_07_bad(%PARAM%) {
  if (staticFive == 5) {
    %BADCODE%
  }
}

/* good1() uses if(staticFive!=5) instead of if(staticFive==5) */
%RETTYPE% %TYPE%__%DESC%_07_good1(%PARAM%) {
  if (staticFive != 5) {
    /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
    printLine("Benign, fixed string");
  } else {
    %GOODCODE%
  }
}

/* good2() reverses the bodies in the if statement */
%RETTYPE% %TYPE%__%DESC%_07_good2(%PARAM%) {
  if (staticFive == 5) {
    %GOODCODE%
  }
}
