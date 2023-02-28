#include <nusys.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

typedef struct {
  float x, y, z;
} Vertex;

Vertex triangle[] = {
  {0, 100, 0},
  {100, -100, 0},
  {-100, -100, 0}
};

void draw_triangle() {
  nuGfxClearCfb();

  guOrtho(&gfxProjection, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
  guMtxIdentity(&gfxModelView);
  guTranslate(&gfxModelView, 0, 0, -1);

  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&gfxProjection), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&gfxModelView), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

  gSPVertex(glistp++, triangle, 3, 0);
  gSP1Triangle(glistp++, 0, 1, 2, 0);

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  nuGfxTaskStart(glistp - gfxListPtr, gfxListPtr, (s32)(glistp - gfxListPtr) * sizeof(Gfx), NU_GFX_UCODE_S2DEX, NU_GFX_UCODE_S2DEX);
  nuGfxTaskAllEndWait();
}

void mainproc(void) {
  nuGfxInit();

  while (1) {
    draw_triangle();
  }
} 
