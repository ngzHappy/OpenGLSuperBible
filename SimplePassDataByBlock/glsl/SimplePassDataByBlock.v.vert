#version 450

out VS_OUT{ vec4 color ;} vs_out;

void main(){
    vec4 positions[3]={
        vec4(-0.5,-0.5,0,1),
        vec4( 0.5,-0.5,0,1),
        vec4( 0,   0.5,0,1)
    };
    gl_Position = positions[gl_VertexID];
    vs_out.color = (1+gl_Position)/2;
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

