#ifndef MULTILINE_STR
#define MULTILINE_STR(...) #__VA_ARGS__
#endif

const char *fragmentShaderSource = MULTILINE_STR(
\x23version 330 core\n
out vec4 FragColor;
void main()
{
    FragColor = gl_FragCoord / 800;
}
);
