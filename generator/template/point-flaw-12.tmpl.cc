#include "std_testcase.h"

%DEFINE%

%RETTYPE% %TYPE%__%DESC%_12_bad(%PARAM%) {
  if (globalReturnsTrueOrFalse()) {
    %BADCODE%
  } else {
    %GOODCODE%
  }
}

/* good1() uses the GoodSink on both sides of the "if" statement */
%RETTYPE% %TYPE%__%DESC%_12_good1(%PARAM%) {
  if (globalReturnsTrueOrFalse()) {
    %GOODCODE%
  } else {
    %GOODCODE%
  }
}
