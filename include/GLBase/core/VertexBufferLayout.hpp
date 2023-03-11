#pragma once

namespace GLBase
{
    // Represents a single vertex attribute
    struct VertexLayoutElement
    {
    private:
        enum {
            FLOAT = 0x1406, 
            UINT = 0x1405, 
            USHORT = 0x1403, 
            BYTE = 0x1401, 
            DOUBLE = 0x140A,
        } _type;
        unsigned _n;
        const bool _normalized;
        VertexLayoutElement(decltype(_type) type, unsigned n, bool normalized): _type(type), _n(n), _normalized(normalized) {}
    public:
        /* Creates an object that represents a vertex attribute
        @tparam T: The underlying data type. Accepted types are float, double, unsigned int, short unsigned int, unsigned char
        @param n: The number of values of type T in the attribute
        @attention Although double precision floats are accepted, they will be converted down to simple precision on the GPU
        @return An object representing the attribute
        */
        template<typename T>
        static VertexLayoutElement create(unsigned n);
        // Returns the size of each value in the attribute (NOT the total size of the attribute itself)
        unsigned size() const {
            switch (_type)
            {
                case FLOAT:     return sizeof(float);
                case DOUBLE:    return sizeof(double);
                case UINT:      return sizeof(unsigned);
                case USHORT:    return sizeof(unsigned short);
                case BYTE:      return 1;
                default: return 0;
            }
        }
        // Returns the number of values in the attribute
        unsigned count() const { return _n; }
        // Returns the OpenGL value corresponding to the data type in the attribute
        int type() const { return _type; }
        // Whether the attribute value is normalized. This is only true if the type is BYTE
        bool normalized() const { return _normalized; }
    };
    template<> inline VertexLayoutElement VertexLayoutElement::create<float>(unsigned n) { 
        return VertexLayoutElement(VertexLayoutElement::FLOAT, n, false);
    }
    template<> inline VertexLayoutElement VertexLayoutElement::create<unsigned>(unsigned n) { 
        return VertexLayoutElement(VertexLayoutElement::UINT, n, false);
    }
    template<> inline VertexLayoutElement VertexLayoutElement::create<unsigned short>(unsigned n) { 
        return VertexLayoutElement(VertexLayoutElement::USHORT, n, false);
    }
    template<> inline VertexLayoutElement VertexLayoutElement::create<double>(unsigned n) { 
        return VertexLayoutElement(VertexLayoutElement::DOUBLE, n, false);
    }
    template<> inline VertexLayoutElement VertexLayoutElement::create<unsigned char>(unsigned n) { 
        return VertexLayoutElement(VertexLayoutElement::BYTE, n, true);
    }

    /* Represents a vertex layout
    @tparam N: The number of attributes in the layout
    */
    template<unsigned N>
    struct VertexLayout
    {
    private:
        VertexLayoutElement _elements[N];
    public:
        /* Constructs the layout description object
        @param elements: A list of VertexLayoutElement objects which represent the attributes of the vertex layout
        */
        template<typename... Args>
        VertexLayout(const Args&... elements): _elements{elements...} {
        }
        // Returns the total size of the vertex
        unsigned stride() const {
            if(!N) return 0;
            unsigned M = _elements[0].size();
            unsigned stride = M * _elements[0].count();
            for(unsigned i = 1; i < N; ++i){
                unsigned eltSize = _elements[i].size();
                unsigned padding = (eltSize - (stride % eltSize)) % eltSize;
                M = eltSize > M? eltSize : M;
                stride += padding + eltSize * _elements[i].count();
            }
            stride += (M - (stride % M)) % M; // align on the biggest element
        }
        // returns an iterator to the first element in the layout
        const VertexLayoutElement* begin() const { return _elements; }
        // returns an iterator to past the last element in the layout
        const VertexLayoutElement* end() const { return _elements + N; }
        /* accesses a specific element 
        @param i: The index of the element
        */
        const VertexLayoutElement& operator[](unsigned i) const { return _elements[i]; }
    };
} // namespace GLBase

