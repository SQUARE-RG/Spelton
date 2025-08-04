TYPE = 'CWE476_NULL_Pointer_Dereference'
DESC = 'deref_condition_on_unknown_ptr'
PARAM = 'int *q'
BADCODE = '''{
    std::%SMARTPTR%<int> P(q);
    if (P) *P = 42;
    else *P = 42; // E
}'''
GOODCODE = '''{
    std::%SMARTPTR%<int> P(q);
    if (P) *P = 42;
}'''
