#include <GLBase/GLBase.hpp>
#include <memory>
#include <iostream>

static constexpr auto *shaderSource = R"(
    #version 460

    #line 0
    layout(location = 0) in vec4 vPos;
    out vec4 fragPos;

    void main(){
        gl_Position = vPos;
        fragPos = vPos;
    }

    layout(location = 0) out vec4 fragColor;
    in vec4 fragPos;

    void main() {
        fragColor = (1-step(.5, length(fragPos.xyz))) * vec4(1, 0, 0, 1);
    }
)";

class Sandbox: public GLBase::Application
{
private:
    GLBase::FrameBuffer _fbo;
    GLBase::Shader _shader;
    struct Vertex2d{
        float x, y;
    };
    static constexpr Vertex2d _vertices[] = {
        {-.5, .5}, {.5, .5},
        {.5, -.5}, {-.5, -.5},
    };
    static constexpr uint32_t _indices[] = { 0, 1, 2, 2, 3, 0};
    GLBase::VertexBuffer _vbo;
    GLBase::VertexArray _vao;
    GLBase::IndexBuffer _ibo;
public:
    Sandbox(): GLBase::Application(500, 500, "Sandbox", true),
        _vbo(_vertices, sizeof(_vertices), GL_STATIC_DRAW), 
        _ibo(_indices, std::extent_v<decltype(_indices)>, GL_STATIC_DRAW)
    {
        renderer().setClearColor(1, 1, 1);
        std::string_view vSource{shaderSource, 168};
        std::string_view fSource{shaderSource+168};
        _shader = GLBase::Shader(vSource, fSource);
        GLBase::VertexLayout<1> layout(
            GLBase::VertexLayoutElement::create<float>(2)
        );
        _vao.addBuffer(_vbo, layout);
    }
    virtual void update(std::chrono::duration<double> delta) override{
        if(wasWindowResized()){
            auto newSize = windowSize();
            glViewport(-1, -1, newSize.first, newSize.second);
        }
    }
    virtual void draw(const GLBase::Renderer& renderer) override {
        renderer.clear();
        renderer.draw(_vao, _ibo, _shader);
    }
    virtual ~Sandbox() {
        
    };
};


int main(int argc, char const *argv[])
{
    try
    {
        auto app = std::make_unique<Sandbox>();
        app->run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    
    return 0;
}
