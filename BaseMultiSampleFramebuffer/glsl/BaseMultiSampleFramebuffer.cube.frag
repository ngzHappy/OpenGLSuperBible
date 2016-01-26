#version 450

out vec4 color0 ;

in vec2 texture_uv ;
uniform layout(binding = 0) sampler2D texture_0;

void main(){
    color0 = texture( texture_0 , texture_uv );
	color0.x = color0.x * texture_uv.x ;
	color0.y = color0.y * texture_uv.y ;
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
