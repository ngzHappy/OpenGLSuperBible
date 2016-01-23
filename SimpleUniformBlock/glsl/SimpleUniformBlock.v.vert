#version 450

uniform layout(std140,binding = 0) UniformBlock{
    mat4 mvp ;
    mat4 normal_mvp ;
} uniforms__ ;

mat4 getMVP(){ return uniforms__.mvp; }
mat4 getNormalMVP(){ return uniforms__.normal_mvp; }

in layout(location=0) vec4 inPosition;
in layout(location=1) vec4 inNormal;

out VS_OUT{ vec4 color; } outStruct ;

void main(){
    gl_Position =  getMVP() * inPosition ;
    outStruct.color = abs( getNormalMVP() * inNormal );
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

