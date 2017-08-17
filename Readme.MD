![Earth](http://i.imgur.com/U4SmFet.png)

![Island](https://pbs.twimg.com/media/DD1-5_NXUAAfU1Z.jpg)

![Island2](https://pbs.twimg.com/media/DD1_a-lXcAEo12X.jpg)

## Work in progress, 3D Game Engine with OpenGL and DirectX.

Used Windows SDK Version 10.0.14393.0 and Visual Studio 2015 (v140)

### How to use

Extract Dependencies.rar into the Solution Folder
     
Set to x64 and Release for best performance. And set the Sandbox project as your start project.

On the first start it could crash because DLL's are missing. Copy the DLL's from the Dependencies\Dlls Folder into 
your Binaries Folder.

### Supported Graphic API's
* OpenGL 4.5
* DirectX 11 (Is a little bit behind)
* (Planned support for Vulkan and DirectX 12)

### Supported texture formats
* .TGA
* .BMP
* (Planned support for .png)

### Supported archive files
* Uncompressed/Compressed .zip files 
* (Planned support for my own file format .lol)

### Supported Systems
* Windows

### Used Libraries
* Assimp (for loading .obj, will be exchanged later with my own implementation..)
* GLEW 
* zLib
* [GrumpyZip](https://github.com/GrumpyLion/MinimalZipLoader) 
* [Sol](https://github.com/ThePhD/sol2) 

### Scenes are built like in Unity with GameObjects and Components.
