#version 330 core
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
layout(location=0) in vec4 draw_vertex;
out vec2 tex_coord;
void main(){
    gl_Position =  projection * view * model  * draw_vertex;

    vec2 tex = vec2(draw_vertex.xy);
    if(tex.x < 0)
        tex.x = 0;
    if(tex.y < 0)
        tex.y = 0;
    tex_coord = tex;
}