#include "std_testcase.h"

%DEFINE%

%RETTYPE% %TYPE%__%DESC%_18_bad(%PARAM%) {
  goto sink;
sink:
    %BADCODE%
}

/* good1() reverses the blocks on the goto statement */
%RETTYPE% %TYPE%__%DESC%_18_good1(%PARAM%) {
  goto sink;
sink:
    %GOODCODE%
}
