#include <raylib.h>
#include <stdlib.h>

#include "microui.h"
#include "murl.h"

int main(void) {
  mu_Context *ctx = malloc(sizeof(mu_Context));
  mu_init(ctx);

  InitWindow(800, 600, "");
  SetTargetFPS(60);

  Font font = LoadFontEx("./fonts/Roboto-Regular.ttf", 20, NULL, 0);
  murl_setup_font_ex(ctx, &font);

  char textbox_buffer[512] = {0};

  while (!WindowShouldClose()) {
    murl_handle_input(ctx);
    mu_begin(ctx);
    if (mu_begin_window(ctx, "font", mu_rect(10, 10, 400, 300))) {
      mu_layout_row(ctx, 1, (int[]){-1}, 0);
      mu_label(ctx, "Hello, World");
      mu_textbox(ctx, textbox_buffer, 512);
      mu_end_window(ctx);
    }
    mu_end(ctx);
    murl_render(ctx);
  }

  CloseWindow();
  free(ctx);
  return 0;
}
