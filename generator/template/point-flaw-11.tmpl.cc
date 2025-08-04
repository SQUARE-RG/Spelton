#include "std_testcase.h"

%DEFINE%

%RETTYPE% %TYPE%__%DESC%_11_bad(%PARAM%) {
  if (globalReturnsTrue()) {
    %BADCODE%
  }
}

/* good1() uses if(globalReturnsFalse()) instead of if(globalReturnsTrue()) */
%RETTYPE% %TYPE%__%DESC%_11_good1(%PARAM%) {
  if (globalReturnsFalse()) {
    /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
    printLine("Benign, fixed string");
  } else {
    %GOODCODE%
  }
}

/* good2() reverses the bodies in the if statement */
%RETTYPE% %TYPE%__%DESC%_11_good2(%PARAM%) {
  if (globalReturnsTrue()) {
    %GOODCODE%
  }
}
