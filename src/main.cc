#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <cstdio>

#include "mathcore.h"
#include "util.h" 


GLuint VB0;
GLint TranslationLocation;
const char* pVSFileName = "shader/shader.vert";
const char* pFSFileName = "shader/shader.frag";


static void RenderSceneCB();
static void CreatVertexBuffer();
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
static void CompileShader();


int main(int argc, char** argv){
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

        int width = 500;
        int height = 500; 
        glutInitWindowSize(width, height);

        int x = 200;
        int y = 100;
        glutInitWindowPosition(x, y);
        int win = glutCreateWindow("main");
        printf("Window id: %d\n", win);

        GLenum res = glewInit();
        if(res!=GLEW_OK){
                fprintf(stderr, "Eroor: %s\n", glewGetErrorString(res));
        }
        GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
        glClearColor(Red, Green, Blue, Alpha);
        
        CompileShader();
        CreatVertexBuffer();
        glutDisplayFunc(RenderSceneCB);

        glutMainLoop();
        
        return 0;

}
        
static void RenderSceneCB(){
        glClear(GL_COLOR_BUFFER_BIT);        
        static float alpha = 0.0f;

        alpha += 0.01f;
        if (alpha > 2) alpha = 0.0f;
        float spin[4][4];
        zRotation(spin, alpha*3.14);
        glUniformMatrix4fv(TranslationLocation, 1, GL_TRUE, &spin[0][0]);

        glBindBuffer(GL_ARRAY_BUFFER, VB0);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        
        glutPostRedisplay();
        glutSwapBuffers();
}

static void CreatVertexBuffer(){
        v3f vertices[3];
        v3f_assign(vertices[0], -1.0f, -0.578f, 0.0f);
        v3f_assign(vertices[1], 0.0f, 1.155f, 0.0f);
        v3f_assign(vertices[2], 1.0f, -0.578f, 0.0f);
        
        glGenBuffers(1, &VB0);
        glBindBuffer(GL_ARRAY_BUFFER, VB0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

static void CompileShader(){
        GLuint ShaderProgram = glCreateProgram();
        if (!ShaderProgram){
                fprintf(stderr, "Error creating shader program\n");
                exit(1);
        }
        std::string vs, fs;

        if(!ReadFile(pVSFileName, vs)){
                exit(1);
        }
        AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

        if(!ReadFile(pFSFileName, fs)){
                exit(1);
        }
        AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

        GLint Success = 0;
        GLchar ErrorLog[1024] = {0};

        glLinkProgram(ShaderProgram);
        glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
        if(!Success){
                glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
                fprintf(stderr, "Error link shader program: %s\n", ErrorLog);
                exit(1);
        }

        
        TranslationLocation = glGetUniformLocation(ShaderProgram, "Translation");
        if(TranslationLocation == -1){
                fprintf(stderr, "Error geting uniform variable\n");
                exit(-1);
        }

        glValidateProgram(ShaderProgram);
        glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
        if(!Success){
                glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
                fprintf(stderr, "Invalid shader program: %s\n", ErrorLog);
                exit(1);
        }

        glUseProgram(ShaderProgram);
}

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType){
        GLuint ShaderObj = glCreateShader(ShaderType);

        if(!ShaderObj){
                fprintf(stderr, "Error creating shader type %d", ShaderType);
                exit(1);
        }
        const GLchar* p[1];
        p[0] = pShaderText;

        GLint Lengths[1];
        Lengths[0] = (GLint) strlen(p[0]);

        glShaderSource(ShaderObj, 1, p, Lengths);
        glCompileShader(ShaderObj);
        
        GLint Success = 0;

        glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &Success);
        if(!Success){
                GLchar InfoLog[1024];
                glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
                fprintf(stderr, "Error compile shader type %d: %s\n", ShaderType, InfoLog);
                exit(1);
        }

        glAttachShader(ShaderProgram, ShaderObj);
}
