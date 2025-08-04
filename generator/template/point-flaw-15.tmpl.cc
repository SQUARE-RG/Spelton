#include "std_testcase.h"

%DEFINE%

%RETTYPE% %TYPE%__%DESC%_15_bad(%PARAM%) {
  switch (6) {
    case 6: %BADCODE% break;
    default:
      /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
      printLine("Benign, fixed string");
      break;
  }
}

/* good1() changes the switch to switch(5) */
%RETTYPE% %TYPE%__%DESC%_15_good1(%PARAM%) {
  switch (5) {
    case 6:
      /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
      printLine("Benign, fixed string");
      break;
    default: %GOODCODE% break;
  }
}

/* good2() reverses the blocks in the switch */
%RETTYPE% %TYPE%__%DESC%_15_good2(%PARAM%) {
  switch (6) {
    case 6: %GOODCODE% break;
    default:
      /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
      printLine("Benign, fixed string");
      break;
  }
}
