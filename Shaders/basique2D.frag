// Version du GLSL

#version 410 

out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float text_flag;

void main()
{
    if (text_flag  == 1.0)
    {
        FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    }
    else
    {
        FragColor = vec4(ourColor, 1.0);
    }
}