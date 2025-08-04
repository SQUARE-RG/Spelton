TYPE = 'CWE476_NULL_Pointer_Dereference'
DESC = 'use_after_reset'
BADCODE = '''{
    auto p = std::%MAKEPTR%<int>(42);
    if (p) {
        p.reset();
        *p = 5;  // E
    }
}'''
GOODCODE = '''{
    auto p = std::%MAKEPTR%<int>(42);
    auto *rp = new int(24);
    if (p) {
        p.reset(rp);
        *p = 5;  // S
    }
}'''
