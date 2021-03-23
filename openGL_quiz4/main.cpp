//
//  main.cpp
//  openGL_quiz4
//
//  Created by 謝育斌 on 2021/3/21.
//

#include "Common.h"

using namespace std;

GLuint            triangle_buffer;
GLuint            triangle_vao;
GLuint            program;

static const GLfloat triangle_vertices[] =
{
    -0.4f, -0.4f, 0.0f, 1.0f,
     0.0f,  0.4f, 0.0f, 1.0f,
     0.4f, -0.4f, 0.0f, 1.0f,
};

char* vsSource = R"glsl(
    #version 330 core
    layout (location = 0) in vec4 position;
    void main()
    {
        gl_Position = position;
    }
)glsl";

char* fsSource = R"glsl(
    #version 330 core
    out vec4 color;
    void main()
    {
        color = vec4(1.0, 0.0, 0.0, 1.0);
    }
)glsl";

void My_Init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glewInit();
    //Initialize shaders
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vsSource, NULL);
    glShaderSource(fs, 1, &fsSource, NULL);

    glCompileShader(vs);
    glCompileShader(fs);

    //Attach Shader to program
    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    ///////////////////////////
    glGenVertexArrays(1, &triangle_vao);
    glBindVertexArray(triangle_vao);
    glGenBuffers(1, &triangle_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangle_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices) * sizeof(float), &triangle_vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}

// GLUT callback. Called to draw the scene.
void My_Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Update shaders' input variable
    ///////////////////////////
    glUseProgram(program);
    {
        glBindVertexArray(triangle_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    ///////////////////////////
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    // Initialize GLUT and GLEW, then create a window.
    ////////////////////
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    
    glutCreateWindow("SHADER_TRIANGLE"); // You cannot use OpenGL functions before this line; The OpenGL context must be created first by glutCreateWindow()!
    //Call custom initialize function
    glewExperimental = GL_TRUE;
    //glewInit();
    My_Init();
    //Register GLUT callback functions
    glutDisplayFunc(My_Display);

    // Enter main event loop.
    glutMainLoop();

    return 0;
}

