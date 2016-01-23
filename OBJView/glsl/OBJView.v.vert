#version 450

uniform layout(std140,binding = 0) UniformBlock{
    mat4 mvp ;
    mat4 normal_mvp ;
} uniforms__ ;

mat4 getMVP(){ return uniforms__.mvp; }
mat4 getNormalMVP(){ return uniforms__.normal_mvp; }

in layout(location=0) vec4 inPosition;
in layout(location=1) vec4 inNormal;
in layout(location=2) vec2 inUV;

out VS_OUT{
	vec2 uv; 
} outStruct ;

vec4 normal2color(vec4 color_i_){
	float length_ = length( color_i_.xyz );
	if(length_==0){return vec4(0,0,0,1);}
	return abs( vec4((color_i_/length_).xyz,1) );
}

void main(){
    gl_Position =  getMVP() * inPosition ;
	outStruct.uv = inUV;
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

