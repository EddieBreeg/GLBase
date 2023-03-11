#pragma once

#include "core/Renderer.hpp"
#include "core/RNG.hpp"
#include "core/FrameBuffer.hpp"
#include <GLFW/glfw3.h>
#include <chrono>
#include "core/Mesh.hpp"

namespace GLBase {
    // A very simple base application class. All subclasses must at least override the update and draw methods
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
        // Indicates whether the window has been resized since the last frame
        bool wasWindowResized() const;
        // Returns the total runtime of the application (in seconds), either since its start or since the last time it was reset
        duration runtime() const;
        // Sets the application runtime to 0
        void resetRuntime();
        // Gets the renderer object
        const Renderer& renderer() const;
    public:
        std::pair<int, int> windowSize() const { return _winSize; }
        /* Constructs the application 
        @param width: The window width, in pixels
        @param height: The window height, in pixels
        @param resizeable: Whether the window should be resizable
        @param miximized: Whether the window should be maximized at creation
        */
        Application(int width, int height, const std::string_view& title, bool resizeable = false, bool maximized = false);
        // Start the application
        void run();
        /* Processes the events
        @return Whether the application should keep running
        */
        virtual bool processEvents();
        /* Updates the logic of the application, at each frame
        @param delta: The duration since the last frame, in seconds
        */
        virtual void update(duration delta) = 0;
        /*
        Clears the screen and issues the draw calls to the renderer
        */
        virtual void draw(const Renderer&) = 0;
        virtual ~Application();
    };
}