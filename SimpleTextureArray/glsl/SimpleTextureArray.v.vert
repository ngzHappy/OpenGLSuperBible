#version 450

uniform layout( location = 0 ) mat4 mvp_matrix ;

out vec2 uv ;
flat out float texture_id;

void main(){

    switch(gl_VertexID){
        case 0:gl_Position = vec4(-1, 1,0,1);break;
        case 1:gl_Position = vec4(-1,-1,0,1);break;
        case 2:gl_Position = vec4( 1, 1,0,1);break;
        case 3:gl_Position = vec4( 1,-1,0,1);break;
    }

    uv = (gl_Position.xy+1)*0.5;
    texture_id = 32;

    gl_Position = mvp_matrix * gl_Position;

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

