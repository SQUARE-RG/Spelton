TYPE = 'CWE476_NULL_Pointer_Dereference'
DESC = 'empty_smart_pointer_dereference'
BADCODE = '''{
    std::%SMARTPTR%<int> P;
    *P = 42; // E
}'''
GOODCODE = '''{
    std::%SMARTPTR%<int> P = std::%MAKEPTR%<int>();
    *P = 42; // S
}'''
