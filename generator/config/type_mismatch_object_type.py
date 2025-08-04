TYPE = 'CWE476_NULL_Pointer_Dereference'
DESC = 'type_mismatch_object_type'
BADCODE = '''{
    std::%SMARTPTR%<int> P(new int[5]); // E
}'''
GOODCODE = '''{
    std::%SMARTPTR%<int[]> P(new int[5]); // S
}'''
