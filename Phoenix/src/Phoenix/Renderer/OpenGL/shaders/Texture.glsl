// Basic Texture Shader

#type vertex
#version 330 core

layout(location = 0) in vec3  a_Position;
layout(location = 1) in vec4  a_Color;
layout(location = 2) in vec2  a_UV;
layout(location = 3) in float a_TexID;
layout(location = 4) in float a_TileCount;

uniform mat4 u_ViewProjection;

out vec4  v_Color;
out vec2  v_UV;
out float v_TexID;

void main()
{
    v_Color = a_Color;
    v_UV    = a_UV * a_TileCount;
    v_TexID = a_TexID;

    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4  v_Color;
in vec2  v_UV;
in float v_TexID;

uniform sampler2D u_Textures[16];

void main()
{
    /*
     Note: This monstrosity is required for now because GLSL 330 only officially supports constant (compile-time) index into a uniform sampler2D array.
     using the following code will get you strange artifacts on some GPUs, since it is undefined behaviour.

     color = texture(u_Textures[int(v_TexID)], v_UV) * v_Color;
     */
    
    switch(int(v_TexID))
    {
        case 0:  color = texture(u_Textures[0],  v_UV) * v_Color; break;
        case 1:  color = texture(u_Textures[1],  v_UV) * v_Color; break;
        case 2:  color = texture(u_Textures[2],  v_UV) * v_Color; break;
        case 3:  color = texture(u_Textures[3],  v_UV) * v_Color; break;
        case 4:  color = texture(u_Textures[4],  v_UV) * v_Color; break;
        case 5:  color = texture(u_Textures[5],  v_UV) * v_Color; break;
        case 6:  color = texture(u_Textures[6],  v_UV) * v_Color; break;
        case 7:  color = texture(u_Textures[7],  v_UV) * v_Color; break;
        case 8:  color = texture(u_Textures[8],  v_UV) * v_Color; break;
        case 9:  color = texture(u_Textures[9],  v_UV) * v_Color; break;
        case 10: color = texture(u_Textures[10], v_UV) * v_Color; break;
        case 11: color = texture(u_Textures[11], v_UV) * v_Color; break;
        case 12: color = texture(u_Textures[12], v_UV) * v_Color; break;
        case 13: color = texture(u_Textures[13], v_UV) * v_Color; break;
        case 14: color = texture(u_Textures[14], v_UV) * v_Color; break;
        case 15: color = texture(u_Textures[15], v_UV) * v_Color; break;
    }
}
