TYPE = 'CWE476_NULL_Pointer_Dereference'
DESC = 'use_after_release'
BADCODE = '''{
    auto p = std::make_unique<int>(42);
    if (p) {
        delete p.release();
        *p = 5; // E
    }
}'''
GOODCODE = '''{
    auto p = std::make_unique<int>(42);
    auto *rp = new int(24);
    if (p) {
        delete p.release();
        p.reset(rp);
        *p = 5; // S
    }
}'''
