#version 330 core

in vec3 vertexColor; // Cor recebida do vertex shader
in vec2 coord;
out vec4 FragColor;  // Saída da cor final do pixel

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, coord); // Define a cor do pixel
}
