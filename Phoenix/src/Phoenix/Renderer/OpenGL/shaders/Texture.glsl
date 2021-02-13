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
    color = texture(u_Textures[int(v_TexID)], v_UV) * v_Color;
}
