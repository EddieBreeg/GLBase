# GLBase

A simple C++ abstraction layer for OpenGL

## Why?

OpenGL might be a fairly simple graphics API, but in order to do anything useful with it, it still requires 
to write quite a bit of boilerplate code. Error handling is also something to consider. GLBase tackles these
problems by wrapping the bare bones OpenGL API objects and calls into classes you can use, to setup your application quickly. An Application base class is also provided, to make things even easier: all the boring stuff has been 
abstracted way so YOU can focus on what matters: drawing things on your screen.

## How?

### Build the library

The build process should be fairly straightforward because the project is self contained: the dependencies 
(glew, glfw and imgui) are already included. 

First, configure the cmake project:
```
> cmake -S . -B ./build
```

Then, build:
```
> cmake --build ./build
```

### How to use it

The headers of the library are documented using doxygen-style comments. You can also take a look at the [sandbox example](examples/sandbox.cpp) to see how the library is used in a very simple scenario.