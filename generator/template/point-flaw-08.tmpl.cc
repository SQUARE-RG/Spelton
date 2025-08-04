#include "std_testcase.h"

%DEFINE%

/* The two function below always return the same value, so a tool
   should be able to identify that calls to the functions will always
   return a fixed value. */
static int staticReturnsTrue() { return 1; }

static int staticReturnsFalse() { return 0; }

%RETTYPE% %TYPE%__%DESC%_08_bad(%PARAM%) {
  if (staticReturnsTrue()) {
    %BADCODE%
  }
}

/* good1() uses if(staticReturnsFalse()) instead of if(staticReturnsTrue()) */
%RETTYPE% %TYPE%__%DESC%_08_good1(%PARAM%) {
  if (staticReturnsFalse()) {
    /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
    printLine("Benign, fixed string");
  } else {
    %GOODCODE%
  }
}

/* good2() reverses the bodies in the if statement */
%RETTYPE% %TYPE%__%DESC%_08_good2(%PARAM%) {
  if (staticReturnsTrue()) {
    %GOODCODE%
  }
}
