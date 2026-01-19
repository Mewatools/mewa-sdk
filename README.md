# What is Mewa SDK

Mewa SDK is a graphics framework that empowers developers to create OpenGL modules for generating video content. Build procedural videos and interactive webpages, then monetize your creations while reaching global audiences.


## Compile and run an example

The SDK supports building and running examples using either Qt Creator or CMake.

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

## Plugin Configuration
When developing a plugin with Qt, you must configure two macros in your .pro file:
- `MX_PLUGIN_HEADER`: Path to your module's header file (e.g., "myplugin.h")
- `MX_PLUGIN_CLASS`: Name of your module class (e.g., MyPlugin)

These macros tell the shared main.cpp which plugin class to instantiate. The simpletriangle example shows this configuration:

```
DEFINES += MX_PLUGIN_HEADER="simpletriangle.h" \
           MX_PLUGIN_CLASS=SimpleTriangle
```

### Notes for developers
- .cpp and .h file names must have all letters in lower case to prevent compilation errors between linux and windows developers
