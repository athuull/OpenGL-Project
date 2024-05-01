#version 330 core

in vec3 ourColor;
out vec4 fragColor;
in vec2 TexCoords;
uniform sampler2D texture1;
uniform sampler2D texture2;
void main(){
fragColor = mix(texture(texture1 , TexCoords) , texture(texture2 , TexCoords), 0.5);

}