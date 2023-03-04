#include <GLBase/core/Mesh.hpp>
#include <fstream>

#include <cstddef>
#include <cstdlib>


namespace GLBase
{

    #define IS_WSPACE(c)    ((c) == ' ' || (c) == '\t')
    #define IS_NUM(c)   ('0' <= (c) && (c) <= '9')
    template<class InIter>
    uint32_t readNum(InIter& it, InIter end){
        while(it != end && !IS_NUM(*it)) ++it;
        uint32_t r = 0;
        char c;
        while(IS_NUM(c = *it)){
            r = r*10 + (c - '0');
            ++it;
        }
        return r;
    }

    struct vIndex_t {uint32_t pos=0, normal=0, uv=0; };

    std::string_view parseVertexIndex(std::string_view str, vIndex_t& out){
        const char *it = str.data();
        const char *end = it + str.length();
        out.pos = readNum(it, end)-1;
        if(it == end || *it != '/') throw std::runtime_error("Missing normals");
        else if(*++it != '/')
            out.uv = readNum(it, end)-1;
        if(it == end || *it != '/') throw std::runtime_error("Missing normals");
        out.normal = readNum(it, end)-1;
        return std::string_view{it, size_t(end-it)};
    }
    void triangulate(const std::vector<vec3>& positions, const std::vector<uint32_t>& faceIndices,
        const vec3& faceNormal, size_t offset,
        std::vector<uint32_t>& out);
    void Mesh::OBJ_loadPolygon(std::string_view line, 
        const std::vector<vec3>& positions, const std::vector<vec3>& normals,
        const std::vector<Vertex3d::UV_coord>& UVs)
    {
        std::vector<uint32_t> indices;
        vec3 n{};
        size_t offset = _vertices.size();
        while(!line.empty()){
            vIndex_t vertexIndex;
            line = parseVertexIndex(line, vertexIndex);
            n = n + normals[vertexIndex.normal];
            _vertices.emplace_back(positions[vertexIndex.pos], 
                normals[vertexIndex.normal].normalized(), UVs[vertexIndex.uv]);
            indices.emplace_back(vertexIndex.pos);
        }
        triangulate(positions, indices, n.normalized(), offset,_indices);
    }
    std::shared_ptr<Mesh> Mesh::fromOBJ(std::string_view path)
    {
        std::ifstream file(path.data(), std::ios_base::binary);

        if(!file.is_open()) return nullptr;
        std::string line;
        auto mesh = std::make_shared<Mesh>();
        std::vector<vec3> positions, normals;
        std::vector<Vertex3d::UV_coord> UVs;

        while (1)
        {
            file >> line;
            if(file.eof()) break;
            switch (line[0])
            {
            case 'v':
                if(line.size() == 1){
                    double x, y, z;
                    file >> x >> y >> z;
                    positions.emplace_back(x, y, z);
                }
                else switch(line[1])
                {
                case 'n':
                    {
                    double x, y, z;
                    file >> x >> y >> z;
                    normals.emplace_back(x, y, z);
                    }
                    break;
                case 't':
                    {
                    float u, v;
                    file >> u >> v;
                    UVs.emplace_back(decltype(Vertex3d::uv){u, v});
                    }
                default:
                    break;
                }
                break;
            case 'f':
                if(!UVs.size()) UVs.emplace_back(Vertex3d::UV_coord{0, 0});
                std::getline(file, line);
                mesh->OBJ_loadPolygon(line, positions, normals, UVs);
                break;
            case 'o':
                std::getline(file, line);
                {
                size_t i = 0;
                while(IS_WSPACE(line[i])) ++i;
                mesh->name = line.substr(i);
                }
            default: break;
            }
        }
        

        file.close();

        return mesh;
    }
} // namespace GLBase
