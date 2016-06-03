#pragma once
#define declareenumloop(T) \
    inline T& operator++(T& e) \
    {\
        e = T(e + 1);\
        return e;\
    }\
    \
    inline T operator++(T& e, int)\
    {\
        T old = e;\
        e = T(e + 1);\
        return old;\
    }\
    \
    inline T& operator--(T& e)\
    {\
        e = T(e - 1);\
        return e;\
    }\
    \
    inline T operator--(T& e, int)\
    {\
        T old = e;\
        e = T(e - 1);\
        return old;\
    }\
    \
    inline T T##_begin()\
    {\
        return T##begin;\
    }\
    \
    inline T T##_end()\
    {\
        return T##end;\
    }

#define forall (ENUM, e) for(ENUM e = ENUM##begin; e != ENUM##end; ++e)
