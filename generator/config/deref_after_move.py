TYPE = 'CWE476_NULL_Pointer_Dereference'
DESC = 'deref_after_move'
PARAM = 'std::%SMARTPTR%<int> P'
BADCODE = '''{
    std::%SMARTPTR%<int> Q = std::move(P);
    if (Q) doNothingDefined();
    if (globalReturnsTrueOrFalse())
        *Q.get() = 1;  // E
    *P.get() = 1;  // E
}'''
GOODCODE = '''{
    std::%SMARTPTR%<int> Q = std::move(P);
    if (Q) doNothingDefined();
    if (globalReturnsTrueOrFalse())
        if (Q)
            *Q.get() = 1;  // S
    /* FIX: check before used */
    if (P)
        *P.get() = 1;  // S
}'''
