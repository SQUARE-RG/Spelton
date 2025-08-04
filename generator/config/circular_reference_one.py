TYPE = 'CWE401_Memory_Leak'
DESC = 'circular_reference_one'
BADCODE = '''{
    struct T { std::shared_ptr<T> t; };
    std::shared_ptr<T> t(new T);
    t->t = t; // E
}'''
GOODCODE = '''{
    struct T { std::weak_ptr<T> t; };
    std::shared_ptr<T> t(new T);
    t->t = t; // S
}'''
