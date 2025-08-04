TYPE = 'CWE401_Memory_Leak'
DESC = 'circular_reference_two'
BADCODE = '''{
    struct S;
    struct T;
    struct S { std::shared_ptr<T> t; };
    struct T { std::shared_ptr<S> s; };
    auto t = std::make_shared<T>();
    auto s = std::make_shared<S>();
    t->s = s;
    s->t = t; // E
}'''
GOODCODE = '''{
    struct S;
    struct T;
    struct S { std::weak_ptr<T> t; };
    struct T { std::weak_ptr<S> s; };
    auto t = std::make_shared<T>();
    auto s = std::make_shared<S>();
    t->s = s;
    s->t = t; // S
}'''
