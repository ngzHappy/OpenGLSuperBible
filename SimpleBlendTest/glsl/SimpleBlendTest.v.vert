#version 450

out vec4 vColor;

void main(){

    switch( (gl_VertexID%3) ){
        case 0:gl_Position = vec4(-0.5,-0.5,0,1);break;
        case 1:gl_Position = vec4( 0.5,-0.5,0,1);break;
        case 2:gl_Position = vec4( 0,   0.5,0,1);break;
    }

    if(gl_VertexID > 2){
        gl_Position += vec4( 0.125,0.125,0.125,0 );
        vColor = vec4(0.5,0,0,0.61); /*z big is red*/
    }else{
        vColor = vec4(0,0,0.8,0.61); /*z samll is blue*/
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

