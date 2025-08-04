TYPE = 'CWE476_NULL_Pointer_Dereference'
DESC = 'bad_assignment'
BADCODE = '''{
    int a = 42;
    std::%SMARTPTR%<int> P(&a); // E
}'''
GOODCODE = '''{
    int *a = new int(42);
    std::%SMARTPTR%<int> P(a); // S
}'''
