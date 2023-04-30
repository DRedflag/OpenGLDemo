#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "mathcore.h"

GLuint VB0;

typedef float v3f[3];
void v3f_assign(v3f vector, float x, float y, float z){
        vector[0] = x;
        vector[1] = y;
        vector[2] = z;
}

static void RenderSceneCB(){
        
        glClear(GL_COLOR_BUFFER_BIT);        

        glBindBuffer(GL_ARRAY_BUFFER, VB0);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glutSwapBuffers();
}

static void CreatVertexBuffer(){
        v3f vertices[3];
        v3f_assign(vertices[0], -1.0f, -1.0f, 0.0f);
        v3f_assign(vertices[1], 0.0f, 1.0f, 0.0f);
        v3f_assign(vertices[2], 1.0f, -1.0f, 0.0f);

        
        
        glGenBuffers(1, &VB0);
        glBindBuffer(GL_ARRAY_BUFFER, VB0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv){
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

        int width = 400;
        int height = 300; 
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
        
        CreatVertexBuffer();
        glutDisplayFunc(RenderSceneCB);

        glutMainLoop();
        
        return 0;

}
