#include "std_testcase.h"

%DEFINE%

/* The variable below is declared "const", so a tool should be able
   to identify that reads of this will always give its initialized
   value. */
static const int STATIC_CONST_FIVE = 5;

%RETTYPE% %TYPE%__%DESC%_06_bad(%PARAM%) {
  if (STATIC_CONST_FIVE == 5) {
    %BADCODE%
  }
}

/* good1() uses if(STATIC_CONST_FIVE!=5) instead of if(STATIC_CONST_FIVE==5) */
%RETTYPE% %TYPE%__%DESC%_06_good1(%PARAM%) {
  if (STATIC_CONST_FIVE != 5) {
    /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
    printLine("Benign, fixed string");
  } else {
    %GOODCODE%
  }
}

/* good2() reverses the bodies in the if statement */
%RETTYPE% %TYPE%__%DESC%_06_good2(%PARAM%) {
  if (STATIC_CONST_FIVE == 5) {
    %GOODCODE%
  }
}
