TYPE = 'CWE476_NULL_Pointer_Dereference'
DESC = 'deref_after_std_swap_null'
BADCODE = '''{
    std::%SMARTPTR%<int> P;
    std::%SMARTPTR%<int> Q;
    std::swap(P, Q);
    *Q = 42; // E
}'''
GOODCODE = '''{
    std::%SMARTPTR%<int> P(new int);
    std::%SMARTPTR%<int> Q;
    std::swap(P, Q);
    *Q = 42; // S
}'''
