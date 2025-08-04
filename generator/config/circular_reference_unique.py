TYPE = 'CWE401_Memory_Leak'
DESC = 'circular_reference_unique'
BADCODE = '''{
    struct T { std::unique_ptr<T> t; };
    auto t = std::make_unique<T>();
    t->t = std::move(t); // E
}'''
GOODCODE = '''{
    struct T { T *t; };
    auto t = std::make_unique<T>();
    t->t = t.get(); // S
}'''
