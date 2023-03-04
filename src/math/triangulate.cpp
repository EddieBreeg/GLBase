#include <vector>
#include <GLBase/core/Vertex.hpp>
#include <stdexcept>

namespace GLBase
{
    class IndexList
    {
    private:
        struct ListNode{
            uint32_t _val;
            ListNode* _prev, *_next;
        } *_head = nullptr;
        size_t _size;
    public:
        struct iterator {
            using value_type = uint32_t;
            using pointer = value_type*;
            using reference = value_type&;
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type = size_t;

            ListNode* _ptr;
            bool operator==(const iterator& other) const { return _ptr == other._ptr; }
            bool operator!=(const iterator& other) const { return !(*this == other); }
            iterator& operator++() {
                _ptr = _ptr->_next;
                return *this;
            }
            iterator& operator--() {
                _ptr = _ptr->_prev;
                return *this;
            }
            iterator operator++(int) {
                auto tmp = *this;
                _ptr = _ptr->_next;
                return tmp;
            }
            iterator operator--(int) {
                auto tmp = *this;
                _ptr = _ptr->_prev;
                return tmp;
            }
            reference operator*() { return _ptr->_val; }
            pointer operator->() { return &(_ptr->_val); }
        };
        IndexList(size_t n): _size(n)
        {
            _head = new ListNode{0};
            auto it = _head;
            for(size_t i = 1; i < n; ++i){
                auto n = new ListNode{uint32_t(i), it};
                it->_next = n;
                it = n;
            }
            it->_next = _head;
            _head->_prev = it;
        }
        iterator erase(iterator pos){
            ListNode* n = pos._ptr;
            n->_prev->_next = n->_next;
            n->_next->_prev = n->_prev;
            ListNode* ret = n->_next;
            if(n == _head) _head = ret;
            delete n;
            --_size;
            return iterator{ret};
        }
        iterator begin() { return iterator{_head}; }
        size_t size() const { return _size; }
        ~IndexList(){
            while(_size--){
                auto tmp = _head;
                _head = _head->_next;
                delete tmp;
            }
        }
    };

    bool onSameSide(const vec3& x, const vec3& y, const vec3& a, const vec3& b){
        vec3 ab = b-a;
        return (x-a).cross(ab).dot((y-a).cross(ab)) >= 0;
    }

    void triangulate(const std::vector<vec3>& positions, const std::vector<uint32_t>& faceIndices,
        const vec3& faceNormal, size_t offset,
        std::vector<uint32_t>& out)
    {
        if(faceIndices.size() < 3) return;
        else if(faceIndices.size() == 3){
            auto n = out.size();
            out.resize(n + 3);
            out[n] = offset;
            out[n+1] = offset+1;
            out[n+2] = offset+2;
            return;
        }
        IndexList iList(faceIndices.size());
        size_t nVertices = out.size();
        out.resize(nVertices + (iList.size() - 2) * 3);
        size_t t = 0;
        for(auto it=iList.begin(); iList.size() > 2; ){
            auto tmp = it;
            // if no ear was found, raise an exception
            if(t == iList.size()) throw std::runtime_error("Couldn't triangulate polygon");
            // form a triangle from 3 points
            const auto& c = positions[faceIndices[*it++]];
            const auto& a = positions[faceIndices[*it++]];
            const auto& b = positions[faceIndices[*it++]];
            vec3 i = b-a, j = c-a;
            vec3 n = i.cross(j);
            if(n.dot(faceNormal) < 0){ // a is not a convex point
                ++t; continue;
            }
            // check if another point is in the abc triangle
            for(; it != tmp; ++it){
                vec3 x = positions[faceIndices[*it]];
                vec3 k = x-a;
                if(n.dot(k)) // if n and k are not orthogonal, x is not in the same plane
                    continue;
                // project k on i and j
                double u = k.dot(i)/i.squaredLength(), v = k.dot(j)/j.squaredLength();
                if(u < 0 || v < 0) continue;
                if(onSameSide(a, x, b, c)) // if a and x are on the same side of segment ab, then
                                            // x is in abc -> we don't have an ear
                    break;
            }
            if(it != tmp){// we found another point in the triangle, abc is not an ear 
                ++t; continue;
            }
            // append the ear to the list of vertices 
            out[nVertices++] =  *it++ + offset;
            out[nVertices++] =  *it++ + offset;
            out[nVertices++] =  *it + offset;
            iList.erase(++tmp); // remove a from the list of vertices
            t = 0; // reset t
        }
    }
} // namespace GLBase
