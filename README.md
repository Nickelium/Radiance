# Radiance - Graphics Engine

Radiance Engine is a graphics engine built currently on top of OpenGL. 
This project is still in development, therefore the codebase tend to change quite a lot.

One of the main focus in the development process is building a clear architecture and providing a simple but also nice API to use.
The Radiance API allows the user to build their graphics application quickly, while the engine handles all the other low-level necessities. 

<p float="left">                                                   
    <img width="99%" src="https://raw.githubusercontent.com/Nickelium/Rasterizer/master/Output/26.png">
</p> 

## Graphics Features
* Material System
* Support Custom Shaders

## General Engine Features:
* Multiple Loggers
* Component System
* Event System
* Window Handling
* User Interface Layer

## Dependencies
* GLFW : Window Creattion and Context 
* GLAD : OpenGL Function Binding
* glm : Math library
* ImGui : Immediate mode UI
* spdlog : Logging
* stbi_image : Textures loading
* assimp : Asset Loader

## Render Samples
<p float="left">                                                   
    <img width="49%" src="https://raw.githubusercontent.com/Nickelium/Rasterizer/master/Output/21.png">
    <img width="49%" src="https://raw.githubusercontent.com/Nickelium/Rasterizer/master/Output/22.png">
    <img width="49%" src="https://raw.githubusercontent.com/Nickelium/Rasterizer/master/Output/16.png">
    <img width="49%" src="https://raw.githubusercontent.com/Nickelium/Rasterizer/master/Output/19.png">
</p>           

https://www.youtube.com/watch?v=7sPPdtgjI90
      
## Inspiration
* [IRadiance Engine](https://github.com/Nickelium/IRadiance)
* [Cell Engine](https://github.com/JoeyDeVries/Cell)
* [Sparky Engine](https://github.com/TheCherno/Sparky)
