#ifndef __TRANSLATION__
#define __TRANSLATION__

#include<mathcore.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
void CreateTranslationMatrix(float move_x, float move_y, float move_z, float spin_x, float spin_y, float spin_z, m4f out);

#endif
