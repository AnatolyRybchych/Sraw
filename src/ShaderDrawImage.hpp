#pragma once

constexpr const char *DrawImageVertex = 
"#version 110\n"
"\n"
"attribute vec4 vertex_p;\n"
"varying vec2 tex_coord;\n"
"\n"
"void main(){\n"
"   tex_coord = vertex_p.xy * 0.5 + vec2(0.5, 0.5);\n"
"   gl_Position = vertex_p;\n"
"}\n"
"";

constexpr const char *DrawImageFragment = 
"#version 110\n"
"\n"
"varying vec2 tex_coord;\n"
"uniform sampler2D tex;\n"
"\n"
"void main(){\n"
"   gl_FragColor = texture2D(tex, tex_coord);\n"
"}\n"
"";
