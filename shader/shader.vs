#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in float lifeColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec3 vertexColor;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
    vertexColor = vec3(lifeColor, 0.2f*(1.0f - lifeColor), 1.0f-lifeColor);
}