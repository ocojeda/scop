// Version du GLSL

#version 130

// Entr�e Shader

in vec3 in_Vertex;

// Fonction main

void main()
{
    // Position finale du vertex
    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
