#version 450

out vec4 out_color ;

void main(){
    vec4 positions[3]={
        vec4(-0.5,-0.5,0,1),
        vec4( 0.5,-0.5,0,1),
        vec4( 0,   0.5,0,1)
    };
    gl_Position = positions[gl_VertexID];
    out_color = (1+gl_Position)/2;
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

