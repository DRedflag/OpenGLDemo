#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <cstdio>
#include <stdlib.h>

#include "mathcore.h"
#include "util.h" 


GLuint VB0;
GLuint IB0;
GLint TranslationLocation;
const char* pVSFileName = "shader/shader.vert";
const char* pFSFileName = "shader/shader.frag";


static void RenderSceneCB();
static void CreateVertexBuffer();
static void CreateIndexBuffer();
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
static void CompileShader();



int main(int argc, char** argv){
        srandom(time(NULL));
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
        CreateVertexBuffer();
        CreateIndexBuffer();


        glutDisplayFunc(RenderSceneCB);

        glutMainLoop();
        
        return 0;

}
        
static void RenderSceneCB(){
        glClear(GL_COLOR_BUFFER_BIT);        
        // static float alpha = 0.0f;

        // alpha += 0.05f;
        // if (alpha > 2) alpha = 0.0f;
        float spin[4][4];
        xRotation(spin, 0);

        glUniformMatrix4fv(TranslationLocation, 1, GL_TRUE, &spin[0][0]);

        glBindBuffer(GL_ARRAY_BUFFER, VB0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB0);
        

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));


        glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        glutPostRedisplay();
        glutSwapBuffers();
}

static void CreateVertexBuffer(){
        vertex vertices[19];
        vertices[0] = vertex(0.0f, 0.0f);

        vertices[1] = vertex(-1.0f, 1.0f);
        vertices[2] = vertex(-0.75f, 1.0f);
        vertices[3] = vertex(-0.5f, 1.0f);
        vertices[4] = vertex(-0.25f, 1.0f);
        vertices[5] = vertex(0.0f, 1.0f);
        vertices[6] = vertex(0.25f, 1.0f);
        vertices[7] = vertex(0.5f, 1.0f);
        vertices[8] = vertex(0.75f, 1.0f);
        vertices[9] = vertex(1.0f, 1.0f);
        
        vertices[10] = vertex(-1.0f, -1.0f);
        vertices[11] = vertex(-0.75f, -1.0f);
        vertices[12] = vertex(-0.5f, -1.0f);
        vertices[13] = vertex(-0.25f, -1.0f);
        vertices[14] = vertex(0.0f, -1.0f);
        vertices[15] = vertex(0.25f, -1.0f);
        vertices[16] = vertex(0.5f, -1.0f);
        vertices[17] = vertex(0.75f, -1.0f);
        vertices[18] = vertex(1.0f, -1.0f);


        
        glGenBuffers(1, &VB0);
        glBindBuffer(GL_ARRAY_BUFFER, VB0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

static void CreateIndexBuffer(){
        unsigned int Indices[] = {
                0, 1, 2,
                0, 2, 3,
                0, 3, 4,
                0, 4, 5,
                0, 5, 6,
                0, 6, 7,
                0, 7, 8,
                0, 8, 9,

                0, 10, 11,
                0, 11, 12,
                0, 12, 13,
                0, 13, 14, 
                0, 14, 15,
                0, 15, 16,
                0, 16, 17,
                0, 17, 18,

                0, 1, 10,
                0, 9, 18
        };
        glGenBuffers(1, &IB0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB0);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
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
