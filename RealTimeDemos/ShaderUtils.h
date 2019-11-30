#include <string>

const char* __shaderUniforms = 
//UBO updated when scene is changed
"layout(std140) uniform sceneUBO\n"
"{\n"
"vec3 lightPosition;\n"
"};\n"

//UBO updated once per frame
"layout(std140) uniform frameUBO\n"
"{\n"
"mat4 viewMatrix;\n"
"mat4 projectionMatrix;\n"
"vec3 cameraPosition;\n"
"};\n\0";

const char*  __vertexShaderPrefix =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 normal;\n"
"layout (location = 2) in vec3 color;\n\0";

const char* __fragmentShaderPrefix = 
"#version 330 core\n"

"out vec4 fragColor;\n\0";