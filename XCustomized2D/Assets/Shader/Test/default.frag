#version 330 core
uniform sampler2D tex;
out vec4 render_color;
void main(){
    render_color = texture(tex, vec2(0.0, 0.0));
}