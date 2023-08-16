#ifndef MURL_H
#define MURL_H

#include "microui.h"

#define RL_COLOR_FROM_MU(c) ((Color){c.r, c.g, c.b, c.a})
#define RL_RECTANGLE_FROM_MU(r) ((Rectangle){r.x, r.y, r.w, r.h})

int murl_text_width(mu_Font font, const char *str, int len);
int murl_text_height(mu_Font font);

void murl_handle_input(mu_Context *ctx);
void murl_render(mu_Context *ctx);

#endif // MURL_H
