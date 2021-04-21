#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aTexCoord;
layout (location = 3) in vec3 aNormal;

//out vec3 ourColor;
out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;
out float height;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0f));
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    Normal = mat3(transpose(inverse(model))) * aNormal;
    //ourColor = aColor;
    texCoord = vec2(aTexCoord.x, aTexCoord.z);
    height = aColor.y *255;

}