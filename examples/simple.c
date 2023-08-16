#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#include "microui.h"
#include "murl.h"

int main(void) {
  mu_Context *ctx = malloc(sizeof(mu_Context));
  mu_init(ctx);

  ctx->text_width = murl_text_width;
  ctx->text_height = murl_text_height;

  InitWindow(800, 600, "microui + raylib");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    murl_handle_input(ctx);

    mu_begin(ctx);

    if (mu_begin_window(ctx, "Hello", mu_rect(20, 20, 200, 150))) {
      mu_label(ctx, "Hello, raylib");
      mu_end_window(ctx);
    }

    mu_end(ctx);

    murl_render(ctx);
  }

  CloseWindow();
  free(ctx);
  return 0;
}
