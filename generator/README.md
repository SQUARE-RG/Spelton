Usage of Generator
==================

Usage
-----

1. All configs are put in one directory (e.g. ./config/), all the configs will be used to generate the test suit.
2. Command line arguments:
    -t for templates (e.g. ./template)
    -c for configures (e.g. ./config)
    -o for output (default ./output)
    -j for multiprocess generating (default 1)
    Refer to the help message for more usage details.

Configures
----------

Each config is a python code with severial string variables defined. See the example for more details.

TYPE (required): the category of the test case (in valid identifier format). e.g. `"CWE476_NULL_Pointer_Dereference"`.
DESC (required): a simple description (in valid identifier format). e.g. `"div_zero_from_return"`.
BADCODE (required): a string of valid C++ code snippet with errors. Comments are suggested to be provided.
GOODCODE (required): a string of valid C++ code snippet with the problem in `BADCODE` fixed.

PARAM (optional, default `""`): the arguments declared in the function declaration.
DEFINE (optional, default `"/* No additional definitions from configure. */"`): additional definitions, function declarations, and etc. that need to be declared before the test case functions.

Example
-------

```config/example.py
TYPE = "Example_Error_Type"
DESC = "a_simple_example_code"
DEFINE = "int get() { return 0; }"
PARAM = "int x"
BADCODE = """{
    int y = get();
    return x / y;
}"""
GOODCODE = """{
    int y = get();
    /* FIX: check before devision */
    return y ? x / y : 0;
}"""
RETTYPE = "int"
```

```template/example-01.tmpl.cc
%DEFINE%
%RETTYPE% %TYPE%__%DESC%_Bad(%PARAM%) {
    %BADCODE%
}
%RETTYPE% %TYPE%__%DESC%_Good(%PARAM%) {
    %BADCODE%
}
```

```output/Example_Error_Type/Example_Error_Type__a_simple_example_code_all_01.cc
int get() { return 0; }
int Example_Error_Type__a_simple_example_code_Bad(int x) {
    {
        int y = get();
        return x / y;
    }
}
int Example_Error_Type__a_simple_example_code_Good(int x) {
    {
        int y = get();
        return y ? x / y : 0;
    }
}
```

Utils
-----

Refer to `template/std_testcase.h` and `template/std_testcase.cpp`. Remember to add include for the `std_testcase.h` file.
