#ifndef BLINDWORM_COMPILER_COMPARABLE_H
#define BLINDWORM_COMPILER_COMPARABLE_H

#include <typeinfo>

class Comparable {
public:
    virtual ~Comparable() { }
    virtual bool operator==(const Comparable& other) const = 0;
};

template<typename t>
inline bool CMP_AND_DREF_PTR(t* a, t* b){
    if(a != b){ // Same ptr ?
        if(!a or !b) return false;
        return (*a == *b); // == for value of whats behind the pointer
    }
    return true;
}
#endif //BLINDWORM_COMPILER_COMPARABLE_H
