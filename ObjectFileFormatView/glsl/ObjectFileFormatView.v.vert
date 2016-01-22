#version 450

layout(location=1) uniform mat4 mvp ;
layout(location=2) uniform mat4 base_mvp ;

in layout(location=0) vec4 inPosition;
out VS_OUT{ vec4 color; } outStruct ;

void main(){
    gl_Position =  mvp * inPosition ; 
	outStruct.color = ( base_mvp  * inPosition + 1) / 2;
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

