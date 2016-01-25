#version 450

in  vec2 uv ;
flat in float texture_id;
out vec4 color ;

uniform layout(binding = 0) sampler2DArray texture_0;

void main(){
    color = texture( texture_0 , vec3(uv,texture_id) );
}

/*
Fragment Language
Inputs
in vec4 gl_FragCoord;
in bool gl_FrontFacing;
in float gl_ClipDistance[];
in float gl_CullDistance[];
in vec2 gl_PointCoord;
in int gl_PrimitiveID;
in int gl_SampleID;
in vec2 gl_SamplePosition;
in int gl_SampleMaskIn[];
in int gl_Layer;
in int gl_ViewportIndex;
in bool gl_HelperInvocation;
Outputs
out float gl_FragDepth;
out int gl_SampleMask[];
*/
