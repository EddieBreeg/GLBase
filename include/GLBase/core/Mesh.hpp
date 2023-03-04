#pragma once

#include <inttypes.h>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <GLBase/core/Vertex.hpp>

namespace GLBase
{


    class Mesh
    {
    private:
        std::vector<Vertex3d> _vertices;
        std::vector<uint32_t> _indices;
        void OBJ_loadPolygon(std::string_view line, 
            const std::vector<vec3>& positions, const std::vector<vec3>& normals,
            const std::vector<Vertex3d::UV_coord>& UVs);
    public:
        std::string name;
        Mesh() = default;
        static std::shared_ptr<Mesh> fromOBJ(std::string_view path);
        ~Mesh() = default;
    };
    
    
} // namespace GLBase
