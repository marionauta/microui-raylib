#ifndef MURL_H
#define MURL_H

#include <raylib.h>

#include "microui.h"

#define MURL_TEXT_SPACING 1

#define RL_COLOR_FROM_MU(c) ((Color){c.r, c.g, c.b, c.a})
#define RL_FONT_FROM_MU(f) ((f == NULL) ? GetFontDefault() : *(Font *)f)
#define RL_RECTANGLE_FROM_MU(r) ((Rectangle){r.x, r.y, r.w, r.h})
#define RL_VECTOR2_FROM_MU(v) ((Vector2){v.x, v.y})

#define murl_setup_font(ctx) murl_setup_font_ex(ctx, NULL)
void murl_setup_font_ex(mu_Context *ctx, const Font *font);

int murl_text_width(mu_Font font, const char *str, int len);
int murl_text_height(mu_Font font);

// Handle all keyboard & mouse events.
void murl_handle_input(mu_Context *ctx);

// Handle mouse cursor position update.
#define murl_handle_mouse_move(ctx)                                            \
  mu_input_mousemove(ctx, GetMouseX(), GetMouseY())

// Handle mouse wheel scroll.
void murl_handle_mouse_scroll(mu_Context *ctx);

// Handle right, left & middle clicks.
void murl_handle_mouse_buttons_input_ex(mu_Context *ctx, int x, int y);
#define murl_handle_mouse_buttons_input(ctx)                                   \
  murl_handle_mouse_buttons_input_ex(ctx, GetMouseX(), GetMouseY())

// Handle shift, control, alt, enter & backspace presses.
void murl_handle_keyboard_input(mu_Context *ctx);

// Handle text input.
void murl_handle_text_input(mu_Context *ctx);

#define murl_render(ctx) murl_render_ex(ctx, BLACK)
void murl_render_ex(mu_Context *ctx, Color background_color);

#endif // MURL_H
