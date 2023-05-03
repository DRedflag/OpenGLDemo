#version 300 es

layout (location = 0) in vec3 Position;

unform mat4 Translation

void main(){
        gl_position = Translation * vec4(position.x * 0.5, position.y * 0.5, position.z,  1.0);
}
