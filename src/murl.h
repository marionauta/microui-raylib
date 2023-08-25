#ifndef MURL_H
#define MURL_H

#include <raylib.h>

#include "microui.h"

#define MURL_TEXT_SPACING 1

#define RL_COLOR_FROM_MU(c) ((Color){c.r, c.g, c.b, c.a})
#define RL_RECTANGLE_FROM_MU(r) ((Rectangle){r.x, r.y, r.w, r.h})
#define RL_VECTOR2_FROM_MU(v) ((Vector2){v.x, v.y})

void murl_setup_font(mu_Context *ctx);
int murl_text_width(mu_Font font, const char *str, int len);
int murl_text_height(mu_Font font);

void murl_handle_input(mu_Context *ctx);

#define murl_render(ctx) murl_render_ex(ctx, BLACK)
void murl_render_ex(mu_Context *ctx, Color background_color);

#endif // MURL_H
