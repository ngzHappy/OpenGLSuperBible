#version 450

layout(location=1) in vec4 inPosition;
layout(location=0) in vec4 inColor;

out VS_OUT{ vec4 color ; } outStruct;

void main(){
    gl_Position = inPosition ;
	outStruct.color = inColor;
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

