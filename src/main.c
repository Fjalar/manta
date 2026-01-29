#define GLAD_GL_IMPLEMENTATION
#include "../include/glad/gl.h"
#include "../include/glfw/glfw3.h"
#include <stdio.h>

static void quit(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(512, 512, "Manta", NULL, NULL);
    glfwMakeContextCurrent(window);
    int glad_version = gladLoadGL(glfwGetProcAddress);
    printf("GL %d.%d\n", GLAD_VERSION_MAJOR(glad_version), GLAD_VERSION_MINOR(glad_version));

    int glfw_major, glfw_minor, glfw_rev;
    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_rev);
    printf("GLFW %d.%d.%d\n", glfw_major, glfw_minor, glfw_rev);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.3, 0.7, 0.3, 1.0);

    float points[] = {
       0.0f,  0.5f,  0.0f, // x,y,z of first point.
       0.5f, -0.5f,  0.0f, // x,y,z of second point.
      -0.5f, -0.5f,  0.0f  // x,y,z of third point.
    };

    float colours[] = {
      1.0f, 0.0f,  0.0f,
      0.0f, 1.0f,  0.0f,
      0.0f, 0.0f,  1.0f
    };

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint colours_vbo = 0;
    glGenBuffers(1, &colours_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colours, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    #define SHADER_VERSION_STRING "#version 460 core\n"
    #define _STRINGIFY(...) #__VA_ARGS__
    #define S(...)          _STRINGIFY(__VA_ARGS__)

    const char* vertex_shader =
        #include "../shader/vert.glsl"
    ;

    const char* fragment_shader =
        #include "../shader/frag.glsl"
    ;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);

    glfwSetKeyCallback(window, quit);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
