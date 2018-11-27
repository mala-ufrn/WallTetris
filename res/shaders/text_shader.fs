#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D text;
uniform vec3 hsvColor;

vec3 hsvToRGB(vec3 hsv) {
    float h = hsv.x;
    float s = hsv.y;
    float v = hsv.z;
    if (s == 0.0) {
        return vec3(v, v, v);
    }
    if (h == 360.0) {
        h = 0.0;
    }
    int hi = int(h / 60.0) % 6;
    float f = h / 60.0 - float(hi);
    float p = v * (1.0 - s);
    float q = v * (1.0 - s * f);
    float t = v * (1.0 - s * (1.0 - f));
    
    vec3 rgb;
    if (hi == 0) {
        rgb = vec3(v, t, p);
    } else if (hi == 1) {
        rgb = vec3(q, v, p);
    } else if (hi == 2) {
        rgb = vec3(p, v, t);
    } else if(hi == 3) {
        rgb = vec3(p, q, v);
    } else if (hi == 4) {
        rgb = vec3(t, p, v);
    } else {
        rgb = vec3(v, p, q);
    }
    return rgb;
}

void main(){
  vec3 textColor = hsvToRGB(hsvColor);
  vec4 sampled = vec4(1.0, 1.0 , 1.0, texture(text, TexCoord).r);
  FragColor = vec4(textColor, 1.0) * sampled;
}