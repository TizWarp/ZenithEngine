#version 460 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aTex;
layout (location = 2) in vec4 aColor;

out vec4 fragColor;
out vec2 texCoords;

void main(){
gl_Position = vec4(pos, 1.0f);
}
