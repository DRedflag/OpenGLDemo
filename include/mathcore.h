#ifndef __MATHCORE__
#define __MATHCORE__
typedef float v3f[3];
typedef float m4f[4][4];

struct vector3f{
        float x;
        float y;
        float z;
        vector3f(){}
        vector3f(float _x, float _y, float _z){
                x = _x;
                y = _y;
                z = _z;
        }
};

struct vertex{
        v3f pos;
        v3f color;
        vertex();
        vertex(float x, float y);
};

void v3f_assign(v3f vector, float x, float y, float z);
void m4f_assign(m4f matrix,
                float a00, float a01, float a02, float a03,
                float a10, float a11, float a12, float a13, 
                float a20, float a21, float a22, float a23,
                float a30, float a31, float a32, float a33);
void zRotation(m4f matrix, float angle);
void xRotation(m4f matrix, float angle);
#endif
