#version 450

out VS_OUT{ 
	vec2 uv;
} outStruct;

void main(){
    switch(gl_VertexID){
        case 0:gl_Position = vec4(-0.5,-0.5,0,1);outStruct.uv=vec2(0,0);break;
        case 1:gl_Position = vec4( 0.5,-0.5,0,1);outStruct.uv=vec2(1,0);break;
        case 2:gl_Position = vec4( 0,   0.5,0,1);outStruct.uv=vec2(0.5,1);break;
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

