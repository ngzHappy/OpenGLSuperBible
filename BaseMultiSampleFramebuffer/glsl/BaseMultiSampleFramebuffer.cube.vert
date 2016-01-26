#version 450

in layout(location = 0) vec4 inPosition ;
in layout(location = 1) vec2 inUV ;

uniform layout( location = 0 ) mat4 mvp ;

out vec2 texture_uv ;

void main(){

    gl_Position = mvp * inPosition;
    texture_uv = inUV ; 

}

/*
Vertex Language
Inputs
in int gl_VertexID;
in int gl_InstanceID;
Outputs
out gl_PerVertex {
vec4 gl_Position;
float gl_PointSize;
float gl_ClipDistance[];
float gl_CullDistance[];
};
*/

