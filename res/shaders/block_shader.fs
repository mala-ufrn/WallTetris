#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main(){
  if (objectColor == vec3(1.0)){
    FragColor = vec4(objectColor, 1.0);
  } 
  else {
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = max((ambient + diffuse), 1.0) * objectColor;
    FragColor = vec4(result * objectColor, 1.0);
  }
}