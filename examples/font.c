#include <raylib.h>
#include <stdlib.h>

#include "microui.h"
#include "murl.h"

int main(void) {
  mu_Context *ctx = malloc(sizeof(mu_Context));
  mu_init(ctx);
  murl_setup_font(ctx);

  InitWindow(800, 600, "");
  SetTargetFPS(60);

  char textbox_buffer[512] = {0};

  while (!WindowShouldClose()) {
    murl_handle_input(ctx);
    mu_begin(ctx);
    if (mu_begin_window(ctx, "font", mu_rect(10, 10, 400, 300))) {
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
