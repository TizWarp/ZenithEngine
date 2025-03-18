#version 460 core

layout (location=0) in vec2 aPos;
layout (location=1) in vec2 aTex;

out vec2 texCoords;

uniform vec3 camera_position;
uniform vec2 sprite_position;

void main(){
gl_Position = vec4(vec3(aPos + sprite_position, 0.0f) + camera_position, 1.0f);
texCoords = aTex;
}
