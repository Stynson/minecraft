$input v_wpos, v_view, v_normal, v_tangent, v_bitangent, v_texcoord0 // in...

/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common/common.sh"

SAMPLER2D(s_texColor,  0);

void main()
{
	vec4 color = toLinear(texture2D(s_texColor, v_texcoord0) );

	gl_FragColor.xyz = color.xyz;
	gl_FragColor.w = 1.0;
	gl_FragColor = toGamma(gl_FragColor);

	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
} 