#include <raylib.h>
#include <stdlib.h>

#include "microui.h"
#include "murl.h"

int main(void) {
  InitWindow(800, 600, "Custom Input");
  SetTargetFPS(60);

  mu_Context *ctx = malloc(sizeof(mu_Context));
  mu_init(ctx);
  murl_setup_font(ctx);

  while (!WindowShouldClose()) {
    murl_handle_mouse_move(ctx);
    murl_handle_mouse_scroll(ctx);
    murl_handle_mouse_buttons_input(ctx);
    murl_handle_keyboard_input(ctx);
    murl_handle_text_input(ctx);

    mu_begin(ctx);
    if (mu_begin_window(ctx, "Custom Input", mu_rect(0, 0, 800, 600))) {
      mu_label(ctx, "This is a label");
      mu_end_window(ctx);
    }
    mu_end(ctx);

    BeginDrawing();
    ClearBackground(BLACK);
    murl_render(ctx);
    EndDrawing();
  }

  free(ctx);
  CloseWindow();
  return 0;
}