#version 300 es

layout (location = 0) in vec3 Position;


uniform mat4 Translation; 

void main(){
        gl_Position =  Translation * vec4(Position.x * 0.5, Position.y * 0.5, Position.z,  1.0);
}
