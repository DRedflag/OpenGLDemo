#include <translation.h>
#include <mathcore.h>
#include <math.h>

void CreateTranslationMatrix(float move_x, float move_y, float move_z, float spin_x, float spin_y, float spin_z, m4f out){
        m4f move, rotx, roty, rotz, project;
        m4f_assign(
                move,
                1, 0, 0, move_x,
                0, 1, 0, move_y,
                0, 0, 1, move_z,
                0, 0, 0, 1
        );
        xRotation(rotx, spin_x);
        yRotation(roty, spin_y);
        zRotation(rotz, spin_z);
        Mat4Mul(roty, rotx, out);
        Mat4Mul(rotz, out, out);
        Mat4Mul(move, out, out);

        float FOV = PI/4.0f;
        float f = 1.0f/tanf(FOV);
        float ar_reverse = (float)SCREEN_HEIGHT/(float)SCREEN_WIDTH;
        float znear = 1.0f;
        float zfar = 10.0f;


        m4f_assign(
                project,
                f*ar_reverse, 0, 0, 0,
                0, f, 0, 0,
                0, 0, (-znear-zfar)/(-znear-zfar), 2*zfar*znear/(znear-zfar),
                0, 0, 1, 0
        );
        Mat4Mul(project, out, out);
}
