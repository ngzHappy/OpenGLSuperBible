#version 450

/*
.x : rotate
.y : dx
.z : dz
.w : 1
*/
in layout( location = 0 ) vec4 input_data_0 ;

uniform mat4 data_matrix = mat4(
    vec4(-1, 1,0,3.5),
    vec4(-1,-1,0,3.5),
    vec4( 1, 1,0,3.5),
    vec4( 1,-1,0,3.5)
);

mat4 getMatrix( vec4 data_1 ){

    float rotate_ = data_1.x ;
    double dx = data_1.y;
    double dy = data_1.z;

    double rsin_ = sin( rotate_/data_1.w );
    double rcos_ = cos( rotate_/data_1.w );

    mat4 rotate_matrix =  mat4(
    rcos_,-rsin_,0,0,/*column x*/
    rsin_, rcos_,0,0,/*column y*/
        0,     0,1,0,/*column z*/
        0,     0,0,1 /*column t*/
    );

    return mat4(
     1, 0,0,0,
     0, 1,0,0,
     0, 0,1,0,
    dx,dy,0,1
    ) * rotate_matrix  ;

}

out vec2 uv ;
flat out float texture_id;

void main(){

    vec4 vertex_this = data_matrix[ gl_VertexID ] ;
    uv = (vertex_this.xy+1)*0.5;
    gl_Position = getMatrix( input_data_0 ) * vertex_this;
    texture_id = gl_InstanceID;

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

