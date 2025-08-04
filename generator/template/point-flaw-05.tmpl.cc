#include "std_testcase.h"

%DEFINE%

/* The two variables below are not defined as "const", but are never
   assigned any other value, so a tool should be able to identify that
   reads of these will always return their initialized values. */
static int staticTrue = 1;  /* true */
static int staticFalse = 0; /* false */

%RETTYPE% %TYPE%__%DESC%_05_bad(%PARAM%) {
  if (staticTrue) {
    %BADCODE%
  }
}

/* good1() uses if(staticFalse) instead of if(staticTrue) */
%RETTYPE% %TYPE%__%DESC%_05_good1(%PARAM%) {
  if (staticFalse) {
    /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
    printLine("Benign, fixed string");
  } else {
    %GOODCODE%
  }
}

/* good2() reverses the bodies in the if statement */
%RETTYPE% %TYPE%__%DESC%_05_good2(%PARAM%) {
  if (staticTrue) {
    %GOODCODE%
  }
}
