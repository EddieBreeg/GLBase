#include <GLBase/math/Matrix.hpp>
#include <cstdlib>
#include <iostream>

#define ASSERT(expr)    if(!(expr)) { \
    std::cerr << "\033[31;1mAssertion failed at " << __FILE__ << ':' << __LINE__ << ": " << #expr << \
        "\033[0m\n"; \
    exit(1);            \
}

int main(int argc, char const *argv[])
{
    using GLBase::Matrix33, GLBase::MatrixView, GLBase::Matrix44;
    Matrix44 A = {
        1, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 3, 0
    };
    Matrix33 B {
        1, 0, 0, 
        0, 2, 0, 
        0, 0, 3, 
    };
    MatrixView sub = A.subMatrix(0, 0, 3, 3);
    ASSERT((sub(1, 1) == 2));
    ASSERT((sub[8] == 3));
    ASSERT((sub == B));
    return 0;
}
