#include "std_testcase.h"

%DEFINE%

/* The two variables below are declared "const", so a tool should
   be able to identify that reads of these will always return their
   initialized values. */
static const int STATIC_CONST_TRUE = 1;  /* true */
static const int STATIC_CONST_FALSE = 0; /* false */

%RETTYPE% %TYPE%__%DESC%_04_bad(%PARAM%) {
  if (STATIC_CONST_TRUE) {
    %BADCODE%
  }
}

/* good1() uses if(STATIC_CONST_FALSE) instead of if(STATIC_CONST_TRUE) */
%RETTYPE% %TYPE%__%DESC%_04_good1(%PARAM%) {
  if (STATIC_CONST_FALSE) {
    /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
    printLine("Benign, fixed string");
  } else {
    %GOODCODE%
  }
}

/* good2() reverses the bodies in the if statement */
%RETTYPE% %TYPE%__%DESC%_04_good2(%PARAM%) {
  if (STATIC_CONST_TRUE) {
    %GOODCODE%
  }
}
