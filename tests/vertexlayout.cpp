#include <GLBase/core/VertexBufferLayout.hpp>
#include <iostream>
#include <GLBase/core/Vertex.hpp>

#define ASSERT(expr)    if(!(expr)) { fprintf(stderr, "Error at line %d: %s\n", __LINE__, #expr); exit(1); }

void f1(){
    struct Vertex {float x, y;};
    using namespace GLBase;
    auto elt = VertexLayoutElement::create<float>(2);
    ASSERT(elt.size() == sizeof(float));
    VertexLayout<1> layout(elt);
    ASSERT(layout.stride() == sizeof(Vertex));
}
void f2(){
    struct Vertex {float x, y; uint8_t byte; };
    using namespace GLBase;
    VertexLayout<2> layout(
        VertexLayoutElement::create<float>(2),
        VertexLayoutElement::create<uint8_t>(1)
    );
    ASSERT(layout.stride() == sizeof(Vertex));
}
void f3(){
    using GLBase::Vertex3d, GLBase::VertexLayoutElement, GLBase::VertexLayout, GLBase::vec3;
    VertexLayout<3> l = Vertex3d::layout();
    ASSERT(l.stride() == sizeof(Vertex3d));
}

int main(int argc, char const *argv[])
{
    f1();
    f2();
    f3();
    return 0;
}
