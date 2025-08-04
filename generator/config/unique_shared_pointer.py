TYPE = 'CWE476_NULL_Pointer_Dereference'
DESC = 'unique_shared_pointer'
BADCODE = '''{
    auto p = std::make_shared<int>(); // E
    *p = 42;
}'''
GOODCODE = '''{
    auto p = std::make_unique<int>(); // S
    *p = 42;
}'''
