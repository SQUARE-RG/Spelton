TYPE = 'CWE476_NULL_Pointer_Dereference'
DESC = 'deref_condition_on_null_ptr'
PARAM = 'std::%SMARTPTR%<int> P'
BADCODE = '''{
    if (P) *P = 42;
    else *P = 42; // E
}'''
GOODCODE = '''{
    if (P) *P = 42;
}'''
