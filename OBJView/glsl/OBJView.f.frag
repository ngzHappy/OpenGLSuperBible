#version 450

out vec4 color ;
in VS_OUT{ 
	vec2 uv; 
}  inStruct ;

void main(){
    color = vec4(inStruct.uv,0.5,1)  ;
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
