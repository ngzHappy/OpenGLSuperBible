﻿#version 450

out layout(location=0) vec4 color0 ;
out layout(location=1) vec4 color1 ;

void main(){
    color0 = vec4( 0.6,0.2,0.1,1);
	color1 = vec4( 0.6,0.1,0.1,1);
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
