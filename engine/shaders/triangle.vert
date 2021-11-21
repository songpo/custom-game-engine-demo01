#version 450

void main(){
    // const array of positions for the triangle
    const vec3 positions[3] = vec3[3] (
    vec3(1.f, 1.f, 0.f),
    vec3(-1.f, 1.f, 0.f),
    vec3(1.f, -1.f, 0.f)
    );

    gl_Position = vec4(positions[gl_VertexIndex], 1.0f);
}