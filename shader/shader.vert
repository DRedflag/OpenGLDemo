#version 300 es

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 inColor;

uniform mat4 Translation; 

out vec4 Color;



void main(){
        gl_Position = Translation*vec4(Position.x , Position.y , Position.z,  1.0);
        Color = vec4(inColor, 1.0);
}
