# Aurora

Note:- use clone --recursively command to clone the repo if you are using git 

Aurora Only supports Windows till now
if you want to compile it then you will need visual studio 2022 or 2019 and windows 10 sdk

Run the GenerateProjects.bat file which can be found in root folder, it will generate the project files for vs 2022 and then you can compile it in the visual studio 2022

If You want to compile it for vs2019 
You can edit the .bat file to generate vs2019 projects by replacing "vs2022" by "vs2019" in the file

There is one setting that you will have to change for it to compile . You will have to set the shader model and and shader type of all the shaders which you can find in Aurora/Platform/DirectX/Shader and then follow these steps

1 - Right click on the file and go to properties and change the shader model to "Shader Model 4 (/4_0)".

2 - If the shader's name has a suffix of "PS" for example - ColorBlendPS , Change the shader type to "Pixel Shader (/ps)" .

3 - If the shader's name has a suffix of "PS" for example - ColorBlendPS , Change the shader type to "Vertex Shader (/vs)" .

4 - Repeat this for every file in the Aurora/Platform/DirectX/Shader directory.

This issue will be solved soon
