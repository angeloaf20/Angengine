#version 460 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 meshNormal;
in vec3 FragPos;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shine;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 meshColor;
uniform Material material;
uniform sampler2D texture_diffuse1;
uniform Light light;
uniform vec3 viewPos;
uniform float u_Time;

void main()
{    
    float lightColor = 0.75f;

    vec4 texColor = texture(texture_diffuse1, TexCoords); // Accessing the texture using the provided index

    FragColor = texColor;
}
