#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#include "microui.h"
#include "murl.h"

int main(void) {
  InitWindow(800, 600, "microui + raylib");
  SetTargetFPS(60);

  mu_Context *ctx = malloc(sizeof(mu_Context));
  mu_init(ctx);
  murl_setup_font(ctx);

  while (!WindowShouldClose()) {
    murl_handle_input(ctx);

    mu_begin(ctx);

    if (mu_begin_window(ctx, "Hello", mu_rect(20, 20, 200, 150))) {
      mu_label(ctx, "Hello, raylib");

      if (mu_button(ctx, "The button")) {
        mu_open_popup(ctx, "popup");
      }

      if (mu_begin_popup(ctx, "popup")) {
        mu_label(ctx, "This is a popup");
        mu_end_popup(ctx);
      }

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
