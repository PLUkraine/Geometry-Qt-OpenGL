#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertColor;

out vec3 outColor;

uniform mat4 projection;

void main()
{
    outColor = vertColor;
    gl_Position = projection * vec4(position, 1.0f);
}
