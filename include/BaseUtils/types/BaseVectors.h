//
// Created by jacka on 09/12/2025.
//

#ifndef BASEUTILS_BASEVECTORS_H
#define BASEUTILS_BASEVECTORS_H

namespace base_utils::types
{
    template<typename T>
    struct Vector2
    {
        T* x,y;
        Vector2(T* x, T* y) : x(x), y(y) {}
    };

    template<typename T>
    struct Vector3
    {
        T* x,y,z;
        Vector3(T* x, T* y, T* z) : x(x), y(y), z(z) {}
    };

}


#endif //BASEUTILS_BASEVECTORS_H