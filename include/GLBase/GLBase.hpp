#pragma once

#include <string_view>
#include "core/Renderer.hpp"
#include "core/RNG.hpp"
#include "core/FrameBuffer.hpp"
#include <GLFW/glfw3.h>
#include <chrono>
#include "core/Mesh.hpp"

namespace GLBase {
    class Application
    {
    private:
        Renderer _renderer;
        void newFrame() const;
        std::pair<int, int> _winSize;
        bool _winResized = false;
        void render();
        std::chrono::duration<double> _runtime{0.0};
    public:    
        using duration = std::chrono::duration<double>;
    protected:
        GLFWwindow *_window;
        bool wasWindowResized() const;
        duration runtime() const;
        void resetRuntime();
        const Renderer& renderer() const;
    public:
        std::pair<int, int> windowSize() const { return _winSize; }
        Application(int width, int height, const std::string_view& title, bool resizeable = false, bool maximized = false);
        void run();
        virtual bool processEvents();
        virtual void update(duration delta) = 0;
        virtual void draw(const Renderer&) = 0;
        virtual ~Application();
    };
}