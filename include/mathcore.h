#ifndef __MATHCORE__
#define __MATHCORE__
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
#endif
