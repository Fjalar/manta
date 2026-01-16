#ifndef MULTILINE_STR
#define MULTILINE_STR(...) #__VA_ARGS__
#endif

const char *vertexShaderSource = MULTILINE_STR(
\x23version 330 core\n
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
);
