#version 300 es

layout (location = 0) in vec3 Position;

uniform mat4 Translation; 

out vec4 Color;

const vec4 colors[3] = vec4[3](
        vec4(1, 0, 0, 1),
        vec4(0, 1, 0, 1),
        vec4(0, 0, 1, 1)
);

void main(){
        gl_Position = Translation * vec4(Position.x * 0.5, Position.y * 0.5, Position.z,  1.0);
        Color = colors[gl_VertexID];
}
