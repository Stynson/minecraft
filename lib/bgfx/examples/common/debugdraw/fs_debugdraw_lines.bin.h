static const uint8_t fs_debugdraw_lines_glsl[89] =
{
	0x46, 0x53, 0x48, 0x05, 0xa4, 0x8b, 0xef, 0x49, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x76, 0x61, // FSH....I..J...va
	0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, // rying highp vec4
	0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, //  v_color0;.void 
	0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, // main ().{.  gl_F
	0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, // ragColor = v_col
	0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                           // or0;.}...
};
static const uint8_t fs_debugdraw_lines_spv[2079] =
{
	0x46, 0x53, 0x48, 0x05, 0xa4, 0x8b, 0xef, 0x49, 0x00, 0x00, 0x10, 0x08, 0x00, 0x00, 0x03, 0x02, // FSH....I........
	0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x08, 0x00, 0x7a, 0x61, 0x00, 0x00, 0x00, 0x00, // #.........za....
	0x00, 0x00, 0x11, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x06, 0x00, 0x01, 0x00, // ................
	0x00, 0x00, 0x47, 0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, 0x35, 0x30, 0x00, 0x00, // ..GLSL.std.450..
	0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, // ................
	0x07, 0x00, 0x04, 0x00, 0x00, 0x00, 0x1f, 0x16, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, // ..........main..
	0x00, 0x00, 0x77, 0x0e, 0x00, 0x00, 0xd1, 0x0d, 0x00, 0x00, 0x10, 0x00, 0x03, 0x00, 0x1f, 0x16, // ..w.............
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x05, 0x00, 0x00, 0x00, 0xf4, 0x01, // ................
	0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x1f, 0x16, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, // ..........main..
	0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x35, 0x13, 0x00, 0x00, 0x76, 0x65, 0x63, 0x34, 0x5f, 0x73, // ......5...vec4_s
	0x70, 0x6c, 0x61, 0x74, 0x28, 0x66, 0x31, 0x3b, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, 0xdd, 0x0e, // plat(f1;........
	0x00, 0x00, 0x5f, 0x78, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0xff, 0x0f, 0x00, 0x00, 0x40, 0x6d, // .._x..........@m
	0x61, 0x69, 0x6e, 0x28, 0x76, 0x66, 0x34, 0x3b, 0x76, 0x66, 0x34, 0x3b, 0x00, 0x00, 0x05, 0x00, // ain(vf4;vf4;....
	0x05, 0x00, 0x4f, 0x30, 0x00, 0x00, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x00, 0x00, // ..O0..v_color0..
	0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0xa2, 0x25, 0x00, 0x00, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, // .......%..gl_Fra
	0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, 0x30, 0x5f, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0xa0, 0x11, // gData_0_........
	0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x56, 0x6f, 0x69, 0x64, 0x46, 0x72, 0x61, 0x67, 0x00, // ..bgfx_VoidFrag.
	0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x2c, 0x4e, 0x00, 0x00, 0x70, 0x61, 0x72, 0x61, 0x6d, 0x00, // ......,N..param.
	0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0xbf, 0x40, 0x00, 0x00, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, // .......@..v_colo
	0x72, 0x30, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x77, 0x0e, 0x00, 0x00, 0x76, 0x5f, // r0........w...v_
	0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0xce, 0x1c, // color0..........
	0x00, 0x00, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, 0x30, 0x5f, // ..gl_FragData_0_
	0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0xef, 0x47, 0x00, 0x00, 0x70, 0x61, 0x72, 0x61, 0x6d, 0x00, // .......G..param.
	0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x9a, 0x16, 0x00, 0x00, 0x70, 0x61, 0x72, 0x61, 0x6d, 0x00, // ..........param.
	0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0xd1, 0x0d, 0x00, 0x00, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, // ..........gl_Fra
	0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, 0x30, 0x5f, 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0xc7, 0x02, // gData_0_........
	0x00, 0x00, 0x24, 0x47, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x00, 0x06, 0x00, 0x06, 0x00, 0xc7, 0x02, // ..$Global.......
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x52, 0x65, 0x63, 0x74, // ......u_viewRect
	0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x75, 0x5f, // ..............u_
	0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x00, 0x06, 0x00, 0x05, 0x00, 0xc7, 0x02, // viewTexel.......
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x00, 0x00, 0x06, 0x00, // ......u_view....
	0x06, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x69, 0x6e, 0x76, 0x56, // ..........u_invV
	0x69, 0x65, 0x77, 0x00, 0x00, 0x00, 0x06, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x04, 0x00, // iew.............
	0x00, 0x00, 0x75, 0x5f, 0x70, 0x72, 0x6f, 0x6a, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0xc7, 0x02, // ..u_proj........
	0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x69, 0x6e, 0x76, 0x50, 0x72, 0x6f, 0x6a, 0x00, // ......u_invProj.
	0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x75, 0x5f, // ..............u_
	0x76, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x00, 0x00, 0x06, 0x00, 0x07, 0x00, 0xc7, 0x02, // viewProj........
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x69, 0x6e, 0x76, 0x56, 0x69, 0x65, 0x77, 0x50, // ......u_invViewP
	0x72, 0x6f, 0x6a, 0x00, 0x00, 0x00, 0x06, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x08, 0x00, // roj.............
	0x00, 0x00, 0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x00, 0x06, 0x00, 0x06, 0x00, 0xc7, 0x02, // ..u_model.......
	0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x56, 0x69, 0x65, // ......u_modelVie
	0x77, 0x00, 0x06, 0x00, 0x07, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x75, 0x5f, // w.............u_
	0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x56, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x00, 0x06, 0x00, // modelViewProj...
	0x06, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x61, 0x6c, 0x70, 0x68, // ..........u_alph
	0x61, 0x52, 0x65, 0x66, 0x34, 0x00, 0x47, 0x00, 0x04, 0x00, 0x77, 0x0e, 0x00, 0x00, 0x1e, 0x00, // aRef4.G...w.....
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0xd1, 0x0d, 0x00, 0x00, 0x1e, 0x00, // ......G.........
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0xf0, 0x06, 0x00, 0x00, 0x06, 0x00, // ......G.........
	0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x00, 0x00, // ..@...H.........
	0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, // ..#.......H.....
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, // ......#.......H.
	0x04, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, // ..............H.
	0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x20, 0x00, // ..........#... .
	0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x07, 0x00, // ..H.............
	0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x03, 0x00, // ......H.........
	0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x03, 0x00, // ......H.........
	0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, // ..#...`...H.....
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, // ..............H.
	0x04, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, // ..............H.
	0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0xa0, 0x00, // ..........#.....
	0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, // ..H.............
	0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x05, 0x00, // ......H.........
	0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x05, 0x00, // ......H.........
	0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, // ..#.......H.....
	0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, // ..............H.
	0x04, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, // ..............H.
	0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x20, 0x01, // ..........#... .
	0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, // ..H.............
	0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x07, 0x00, // ......H.........
	0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x07, 0x00, // ......H.........
	0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x60, 0x01, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, // ..#...`...H.....
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, // ..............H.
	0x04, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, // ..............H.
	0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0xa0, 0x01, // ..........#.....
	0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x07, 0x00, // ..H.............
	0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x09, 0x00, // ......H.........
	0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x09, 0x00, // ......H.........
	0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0xa0, 0x09, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, // ..#.......H.....
	0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, // ..............H.
	0x04, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, // ..............H.
	0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0xe0, 0x09, // ..........#.....
	0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x07, 0x00, // ..H.............
	0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xc7, 0x02, 0x00, 0x00, 0x0b, 0x00, // ......H.........
	0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x20, 0x0a, 0x00, 0x00, 0x47, 0x00, 0x03, 0x00, 0xc7, 0x02, // ..#... ...G.....
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 0x08, 0x00, 0x00, 0x00, 0x21, 0x00, // ..............!.
	0x03, 0x00, 0x02, 0x05, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, 0x0d, 0x00, // ................
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x8a, 0x02, 0x00, 0x00, 0x07, 0x00, // .. ... .........
	0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x0d, 0x00, // ................
	0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x21, 0x00, 0x04, 0x00, 0xef, 0x00, 0x00, 0x00, 0x1d, 0x00, // ......!.........
	0x00, 0x00, 0x8a, 0x02, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x9a, 0x02, 0x00, 0x00, 0x07, 0x00, // ...... .........
	0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x21, 0x00, 0x05, 0x00, 0x3d, 0x0b, 0x00, 0x00, 0x08, 0x00, // ......!...=.....
	0x00, 0x00, 0x9a, 0x02, 0x00, 0x00, 0x9a, 0x02, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x0d, 0x00, // ..........+.....
	0x00, 0x00, 0x0c, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x9b, 0x02, // .......... .....
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x9b, 0x02, // ..........;.....
	0x00, 0x00, 0x77, 0x0e, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x9c, 0x02, // ..w....... .....
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x9c, 0x02, // ..........;.....
	0x00, 0x00, 0xd1, 0x0d, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x18, 0x00, 0x04, 0x00, 0x65, 0x00, // ..............e.
	0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 0x0b, 0x00, // ................
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x0b, 0x00, // .. .......+.....
	0x00, 0x00, 0x6a, 0x0a, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x04, 0x00, 0xf0, 0x06, // ..j... .........
	0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x6a, 0x0a, 0x00, 0x00, 0x1e, 0x00, 0x0e, 0x00, 0xc7, 0x02, // ..e...j.........
	0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, // ..........e...e.
	0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, // ..e...e...e...e.
	0x00, 0x00, 0xf0, 0x06, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x1d, 0x00, // ......e...e.....
	0x00, 0x00, 0x36, 0x00, 0x05, 0x00, 0x08, 0x00, 0x00, 0x00, 0x1f, 0x16, 0x00, 0x00, 0x00, 0x00, // ..6.............
	0x00, 0x00, 0x02, 0x05, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x53, 0x61, 0x00, 0x00, 0x3b, 0x00, // ..........Sa..;.
	0x04, 0x00, 0x9a, 0x02, 0x00, 0x00, 0xef, 0x47, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x3b, 0x00, // .......G......;.
	0x04, 0x00, 0x9a, 0x02, 0x00, 0x00, 0x9a, 0x16, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x3d, 0x00, // ..............=.
	0x04, 0x00, 0x1d, 0x00, 0x00, 0x00, 0xbf, 0x40, 0x00, 0x00, 0x77, 0x0e, 0x00, 0x00, 0x3e, 0x00, // .......@..w...>.
	0x03, 0x00, 0xef, 0x47, 0x00, 0x00, 0xbf, 0x40, 0x00, 0x00, 0x39, 0x00, 0x06, 0x00, 0x08, 0x00, // ...G...@..9.....
	0x00, 0x00, 0x79, 0x61, 0x00, 0x00, 0xff, 0x0f, 0x00, 0x00, 0xef, 0x47, 0x00, 0x00, 0x9a, 0x16, // ..ya.......G....
	0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x1d, 0x00, 0x00, 0x00, 0xce, 0x1c, 0x00, 0x00, 0x9a, 0x16, // ..=.............
	0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0xd1, 0x0d, 0x00, 0x00, 0xce, 0x1c, 0x00, 0x00, 0xfd, 0x00, // ..>.............
	0x01, 0x00, 0x38, 0x00, 0x01, 0x00, 0x36, 0x00, 0x05, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x35, 0x13, // ..8...6.......5.
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xef, 0x00, 0x00, 0x00, 0x37, 0x00, 0x03, 0x00, 0x8a, 0x02, // ..........7.....
	0x00, 0x00, 0xdd, 0x0e, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x88, 0x2e, 0x00, 0x00, 0x3d, 0x00, // ..............=.
	0x04, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x64, 0x57, 0x00, 0x00, 0xdd, 0x0e, 0x00, 0x00, 0x3d, 0x00, // ......dW......=.
	0x04, 0x00, 0x0d, 0x00, 0x00, 0x00, 0xa9, 0x4e, 0x00, 0x00, 0xdd, 0x0e, 0x00, 0x00, 0x3d, 0x00, // .......N......=.
	0x04, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x49, 0x39, 0x00, 0x00, 0xdd, 0x0e, 0x00, 0x00, 0x3d, 0x00, // ......I9......=.
	0x04, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x5c, 0x39, 0x00, 0x00, 0xdd, 0x0e, 0x00, 0x00, 0x50, 0x00, // .......9......P.
	0x07, 0x00, 0x1d, 0x00, 0x00, 0x00, 0xb0, 0x2a, 0x00, 0x00, 0x64, 0x57, 0x00, 0x00, 0xa9, 0x4e, // .......*..dW...N
	0x00, 0x00, 0x49, 0x39, 0x00, 0x00, 0x5c, 0x39, 0x00, 0x00, 0xfe, 0x00, 0x02, 0x00, 0xb0, 0x2a, // ..I9...9.......*
	0x00, 0x00, 0x38, 0x00, 0x01, 0x00, 0x36, 0x00, 0x05, 0x00, 0x08, 0x00, 0x00, 0x00, 0xff, 0x0f, // ..8...6.........
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 0x0b, 0x00, 0x00, 0x37, 0x00, 0x03, 0x00, 0x9a, 0x02, // ......=...7.....
	0x00, 0x00, 0x4f, 0x30, 0x00, 0x00, 0x37, 0x00, 0x03, 0x00, 0x9a, 0x02, 0x00, 0x00, 0xa2, 0x25, // ..O0..7........%
	0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0xee, 0x5f, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x8a, 0x02, // ......._..;.....
	0x00, 0x00, 0x2c, 0x4e, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x2c, 0x4e, // ..,N......>...,N
	0x00, 0x00, 0x0c, 0x0a, 0x00, 0x00, 0x39, 0x00, 0x05, 0x00, 0x1d, 0x00, 0x00, 0x00, 0xa0, 0x11, // ......9.........
	0x00, 0x00, 0x35, 0x13, 0x00, 0x00, 0x2c, 0x4e, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x1d, 0x00, // ..5...,N..=.....
	0x00, 0x00, 0x58, 0x5b, 0x00, 0x00, 0x4f, 0x30, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0xa2, 0x25, // ..X[..O0..>....%
	0x00, 0x00, 0x58, 0x5b, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00, 0x00,       // ..X[......8....
};
static const uint8_t fs_debugdraw_lines_dx9[131] =
{
	0x46, 0x53, 0x48, 0x05, 0xa4, 0x8b, 0xef, 0x49, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x00, 0x03, // FSH....I..t.....
	0xff, 0xff, 0xfe, 0xff, 0x14, 0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, 0x00, 0x00, 0x00, 0x23, 0x00, // ......CTAB....#.
	0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, // ................
	0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x70, 0x73, 0x5f, 0x33, 0x5f, 0x30, 0x00, 0x4d, 0x69, 0x63, // ......ps_3_0.Mic
	0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, 0x20, 0x48, 0x4c, 0x53, 0x4c, 0x20, // rosoft (R) HLSL 
	0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, // Shader Compiler 
	0x31, 0x30, 0x2e, 0x31, 0x00, 0xab, 0x1f, 0x00, 0x00, 0x02, 0x0a, 0x00, 0x00, 0x80, 0x00, 0x00, // 10.1............
	0x0f, 0x90, 0x01, 0x00, 0x00, 0x02, 0x00, 0x08, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0x90, 0xff, 0xff, // ................
	0x00, 0x00, 0x00,                                                                               // ...
};
static const uint8_t fs_debugdraw_lines_dx11[262] =
{
	0x46, 0x53, 0x48, 0x05, 0xa4, 0x8b, 0xef, 0x49, 0x00, 0x00, 0xf4, 0x00, 0x00, 0x00, 0x44, 0x58, // FSH....I......DX
	0x42, 0x43, 0xa6, 0x7f, 0x08, 0xe2, 0x95, 0xbd, 0x5f, 0xa3, 0x3f, 0x5b, 0x58, 0x8e, 0x54, 0x0f, // BC......_.?[X.T.
	0x89, 0x67, 0x01, 0x00, 0x00, 0x00, 0xf4, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x2c, 0x00, // .g............,.
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xb4, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x4e, 0x4c, 0x00, // ..........ISGNL.
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, // ..........8.....
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, // ................
	0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, // ..D.............
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x4f, 0x53, // ..........SV_POS
	0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0xab, 0xab, 0x4f, 0x53, // ITION.COLOR...OS
	0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00, // GN,........... .
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x41, 0x52, 0x47, 0x45, 0x54, 0x00, // ......SV_TARGET.
	0xab, 0xab, 0x53, 0x48, 0x44, 0x52, 0x38, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x0e, 0x00, // ..SHDR8...@.....
	0x00, 0x00, 0x62, 0x10, 0x00, 0x03, 0xf2, 0x10, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x65, 0x00, // ..b...........e.
	0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x05, 0xf2, 0x20, // ... ......6.... 
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x1e, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3e, 0x00, // ......F.......>.
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00,                                                             // ......
};
static const uint8_t fs_debugdraw_lines_mtl[404] =
{
	0x46, 0x53, 0x48, 0x05, 0xa4, 0x8b, 0xef, 0x49, 0x00, 0x00, 0x85, 0x01, 0x00, 0x00, 0x75, 0x73, // FSH....I......us
	0x69, 0x6e, 0x67, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65, 0x20, 0x6d, 0x65, // ing namespace me
	0x74, 0x61, 0x6c, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, // tal;.struct xlat
	0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, 0x75, 0x74, 0x20, 0x7b, // MtlShaderInput {
	0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, // .  float4 v_colo
	0x72, 0x30, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, // r0;.};.struct xl
	0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, // atMtlShaderOutpu
	0x74, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x67, 0x6c, 0x5f, // t {.  float4 gl_
	0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x73, 0x74, // FragColor;.};.st
	0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, // ruct xlatMtlShad
	0x65, 0x72, 0x55, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x7b, 0x0a, 0x7d, 0x3b, 0x0a, 0x66, // erUniform {.};.f
	0x72, 0x61, 0x67, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, // ragment xlatMtlS
	0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, // haderOutput xlat
	0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, // MtlMain (xlatMtl
	0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, 0x75, 0x74, 0x20, 0x5f, 0x6d, 0x74, 0x6c, // ShaderInput _mtl
	0x5f, 0x69, 0x20, 0x5b, 0x5b, 0x73, 0x74, 0x61, 0x67, 0x65, 0x5f, 0x69, 0x6e, 0x5d, 0x5d, 0x2c, // _i [[stage_in]],
	0x20, 0x63, 0x6f, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, //  constant xlatMt
	0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x55, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x26, 0x20, // lShaderUniform& 
	0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x20, 0x5b, 0x5b, 0x62, 0x75, 0x66, 0x66, 0x65, 0x72, 0x28, // _mtl_u [[buffer(
	0x30, 0x29, 0x5d, 0x5d, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, // 0)]]).{.  xlatMt
	0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x5f, 0x6d, // lShaderOutput _m
	0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, 0x20, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x2e, 0x67, // tl_o;.  _mtl_o.g
	0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x5f, 0x6d, // l_FragColor = _m
	0x74, 0x6c, 0x5f, 0x69, 0x2e, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x20, // tl_i.v_color0;. 
	0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, //  return _mtl_o;.
	0x7d, 0x0a, 0x0a, 0x00,                                                                         // }...
};
extern const uint8_t* fs_debugdraw_lines_pssl;
extern const uint32_t fs_debugdraw_lines_pssl_size;
