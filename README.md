# What is Mewa SDK

Mewa SDK is a graphics framework that empowers developers to create OpenGL modules for generating video content. 
Build procedural videos and interactive webpages, then monetize your creations while reaching global audiences.


## Compile and run a Module

A Module is a C++ class that extends [`MxModule`](framework/moduleinterface/mxmodule.h) and uses OpenGL ES 3.0+ to render procedurally generated video frames. Each module implements custom rendering logic via the [`renderOutput()`](framework/moduleinterface/mxmodule.h:24) method and can optionally handle user interactions (mouse/touch events) and expose configurable parameters through a control panel.

The SDK supports building and running modules using either Qt Creator or CMake.

### Using Qt Creator

To build and debug an example with Qt Creator, pick one of the available examples (such as simpletriangle or stars) and open the corresponding .pro file with Qt Creator. This provides a full IDE experience with integrated debugging.

### Using CMake

With the CMake build files, you can use various development environments. For example, with VS Code, open the project folder and use the CMake Tools extension to configure, build, and debug the examples. This approach offers flexibility across different platforms and editors.

## Code Documentation

Run doxygen in the project root to generate the documentation in the doc folder.

## Code structure
The examples folder holds examples, while the framework folder holds all the common code used by an example.
Each example has a MxModule derived class. This is the entry point of every example.

To prevent code duplication, the main.cpp file is located in framework/platform/qt and shared across all examples.

## Module Configuration
When developing a module with Qt, you must configure two macros in your .pro file:
- `MX_MODULE_HEADER`: Path to your module's header file (e.g., "mymodule.h")
- `MX_MODULE_CLASS`: Name of your module class (e.g., MyModule)

These macros tell the shared main.cpp which module class to instantiate. The simpletriangle example shows this configuration:

```
DEFINES += MX_MODULE_HEADER="simpletriangle.h" \
           MX_MODULE_CLASS=SimpleTriangle
```

### Notes for developers
- .cpp and .h file names must have all letters in lower case to prevent compilation errors between linux and windows developers
