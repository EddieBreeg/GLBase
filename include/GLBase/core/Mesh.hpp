#pragma once

#include <inttypes.h>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <GLBase/core/Vertex.hpp>

namespace GLBase
{

    // Represents a 3D Mesh. Currently, only the OBJ format is supported for loading
    class Mesh
    {
    private:
        std::vector<Vertex3d> _vertices;
        std::vector<uint32_t> _indices;
        void OBJ_loadPolygon(std::string_view line, 
            const std::vector<vec3>& positions, const std::vector<vec3>& normals,
            const std::vector<Vertex3d::UV_coord>& UVs);
    public:
        // The name of the object
        std::string name;
        Mesh() = default;
        // Loads the object from a wavefront OBJ file. If the object couldn't be loaded, nullptr is returned instead
        static std::shared_ptr<Mesh> fromOBJ(std::string_view path);
        ~Mesh() = default;
    };
    
    
} // namespace GLBase
