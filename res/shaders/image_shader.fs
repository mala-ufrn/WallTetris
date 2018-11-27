#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D tex;
uniform vec3 color;

void main(){
  FragColor = texture(tex, TexCoord) * vec4(color, 1.0);
}