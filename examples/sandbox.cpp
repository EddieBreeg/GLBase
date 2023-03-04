#include <GLBase/GLBase.hpp>
#include <memory>
#include <iostream>

class Sandbox: public GLBase::Application
{
private:
    GLBase::FrameBuffer _fbo;
    GLBase::Texture _tex;
public:
    Sandbox(): GLBase::Application(500, 500, "Sandbox", true),
        _tex(500, 500, GL_RGBA)
    {
        renderer().setClearColor(1, 0, 0);
        _fbo.attachTexture2D(_tex, 0);
    }
    virtual void update(std::chrono::duration<double> delta) override{
        
    }
    virtual void draw(const GLBase::Renderer& renderer) override {
        renderer.clear();
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
