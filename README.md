# Radiance - Graphics Engine

Radiance Engine is an open-source graphics engine written in C++11 and currently built on top of OpenGL 4.3. 

One of the main focus in the development process is building a clear architecture and providing a simple but also nice API to use.
The Radiance API allows the user to build their graphics application quickly, while the engine handles all the other low-level necessities. The engine strives to be as platform independent as possible.

This project is still in development, therefore the codebase tend to fluctuate a lot.

<p float="left">                                                   
    <img width="99%" src="https://raw.githubusercontent.com/Nickelium/Radiance/Main/Output/1.png">
</p> 

## Graphics Features
* Material System
* Support Custom Shaders

## General Engine Features
* Multiple Loggers
* Component System
* Event System
* Window Handling
* User Interface Layer

## Platform Support
##### ![](https://img.shields.io/badge/Windows-Supported-green.svg)
##### ![](https://img.shields.io/badge/Linux-Not%20Supported-red.svg)
##### ![](https://img.shields.io/badge/MacOS-Not%20Supported-red.svg)

## Dependencies
* GLFW : Window Creattion and Context 
* GLAD : OpenGL Function Binding
* glm : Math library
* ImGui : Immediate mode UI
* spdlog : Logging
* stbi_image : Textures loading
* assimp : Asset Loader

## Render Samples         
 
## Inspiration
* [Cell Engine](https://github.com/JoeyDeVries/Cell)
* [Sparky Engine](https://github.com/TheCherno/Sparky)
* [IRadiance Engine](https://github.com/Nickelium/IRadiance)
