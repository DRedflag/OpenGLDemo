#include <mathcore.h>
#include <math.h>

void v3f_assign(v3f vector, float x, float y, float z){
        vector[0] = x;
        vector[1] = y;
        vector[2] = z;
}
void m4f_assign(m4f matrix,
                float a00, float a01, float a02, float a03,
                float a10, float a11, float a12, float a13, 
                float a20, float a21, float a22, float a23,
                float a30, float a31, float a32, float a33){
        matrix[0][0] = a00;
        matrix[0][1] = a01;
        matrix[0][2] = a02;
        matrix[0][3] = a03;
        matrix[1][0] = a10;
        matrix[1][1] = a11;
        matrix[1][2] = a12;
        matrix[1][3] = a13;
        matrix[2][0] = a20;
        matrix[2][1] = a21;
        matrix[2][2] = a22;
        matrix[2][3] = a23;
        matrix[3][0] = a30;
        matrix[3][1] = a31;
        matrix[3][2] = a32;
        matrix[3][3] = a33;
}

void zRotation(m4f matrix, float angle){
        m4f_assign(matrix, 
                   cos(angle), -sin(angle), 0, 0,
                   sin(angle), cos(angle), 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1);
}

void yRotation(m4f matrix, float angle){
        m4f_assign(matrix, 
                   cos(angle), 0, sin(angle), 0,
                   0, 1, 0, 0,
                   -sin(angle), 0, cos(angle), 0,
                   0, 0, 0, 1);
}

void xRotation(m4f matrix, float angle){
        m4f_assign(matrix, 
                   1, 0, 0, 0,
                   0, cos(angle), -sin(angle), 0,
                   0, sin(angle), cos(angle), 0,
                   0, 0, 0, 1);
}

void Mat4Mul(m4f left, m4f right, m4f out){
        m4f res;

        m4f_assign(
                res,
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
        );
        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        for (int k = 0; k < 4; k++){
                                res[i][j] += left[i][k]*right[k][j];
                        }
        Mat4Copy(res, out);
}

void Mat4Copy(m4f src, m4f dest){
        for (int i=0; i<4; i++)
                for(int j=0; j<4; j++){
                        dest[i][j] = src[i][j];
                }
} 

vertex::vertex(){}

vertex::vertex(float x, float y, float z){
        v3f_assign(pos, x, y, z);
        float red = (float) rand()/(float) RAND_MAX;
        float green = (float) rand()/(float) RAND_MAX;
        float blue = (float) rand()/(float) RAND_MAX;
        v3f_assign(color, red, green, blue);
}



