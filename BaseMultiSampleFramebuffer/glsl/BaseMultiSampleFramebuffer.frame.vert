#version 450

void main(){

    switch(gl_VertexID){
        case 0:gl_Position = vec4(-0.5,-0.5,0,1);break;
        case 1:gl_Position = vec4( 0.5,-0.5,0,1);break;
        case 2:gl_Position = vec4( 0,   0.5,0,1);break;
    }

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

