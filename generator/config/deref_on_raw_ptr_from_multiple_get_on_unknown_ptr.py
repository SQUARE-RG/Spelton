TYPE = 'CWE476_NULL_Pointer_Dereference'
DESC = 'deref_on_raw_ptr_from_multiple_get_on_unknown_ptr'
PARAM = 'std::%SMARTPTR%<int> P'
BADCODE = '''{
    int *x = P.get();
    int *y = P.get();
    if (!x)
        *y = 42; // E
}'''
GOODCODE = '''{
    int *x = P.get();
    int *y = P.get();
    if (x)
        *y = 42; // S
}'''
