#version 450

layout(location=1) uniform mat4 mvp ;
layout(location=2) uniform mat4 normal_mvp ;

in layout(location=0) vec4 inPosition;
in layout(location=1) vec4 inNormal;
out VS_OUT{ vec4 color; } outStruct ;

vec4 normal2color(vec4 color_i_){
	float length_ = length( color_i_.xyz );
	if(length_==0){return vec4(0,0,0,1);}
	return abs( vec4((color_i_/length_).xyz,1) );
}

void main(){
    gl_Position =  mvp * inPosition ;
    outStruct.color = normal2color( normal_mvp * inNormal )  ;
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

