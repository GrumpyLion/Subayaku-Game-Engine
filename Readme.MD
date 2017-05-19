![Earth](http://i.imgur.com/U4SmFet.png)

## Work in progress, 3D Game Engine with OpenGL and DirectX.

Used Windows SDK Version 10.0.15063.0

### Supported Graphic API's
* OpenGL 4.2
* DirectX 11
* (Planned support for Vulkan and DirectX 12)

### Supported texture formats
* .TGA
* .BMP
* (Planned support for .png)

### Supported archive files
* Uncompressed .zip files (Deflate de/compression is in work)
* (Planned support for my own file format .lol)

### Supported Systems
* Windows
* (Planned support for Android, Web and if i get an PS4 Devkit then also for PS4)

### Used Libraries
* Assimp (for loading .obj, will be exchanged later with my own implementation..)
* GLEW 
* [Sol](https://github.com/ThePhD/sol2) 

### Scenes are built like in Unity with GameObjects and Components.

### How to use

Extract Dependencies.rar into the Engine Folder

The structure should look like this

Subayaku-Game-Engine\Engine ..
* \Source\
* \Dependencies\
* ..
     
Set to x64 and Release for best performance. And set the Sandbox project as your start project.

On the first start it will crash because DLL's are missing. Copy the DLL's from the Dependencies\Dlls Folder into 
your Builds Folder.
