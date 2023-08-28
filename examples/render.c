#include <raylib.h>
#include <stdlib.h>

#include "microui.h"
#include "murl.h"

#define WIDTH 600
#define HEIGHT 800

int main(void) {
  InitWindow(WIDTH, HEIGHT, "Render Textures");
  SetTargetFPS(60);

  RenderTexture texture = LoadRenderTexture(WIDTH, HEIGHT / 2);

  mu_Context *ctx = malloc(sizeof(mu_Context));
  mu_init(ctx);
  murl_setup_font(ctx);

  while (!WindowShouldClose()) {
    murl_handle_input(ctx);

    mu_begin(ctx);
    if (mu_begin_window(ctx, "Render Texture", mu_rect(150, 50, 300, 300))) {
      mu_layout_row(ctx, 1, (int[]){-1}, 0);
      mu_label(ctx, "Only the top window responds to events.");
      mu_label(ctx, "The bottom one is a mirror.");
      mu_end_window(ctx);
    }
    mu_end(ctx);

    BeginTextureMode(texture);
    ClearBackground(BLACK);
    murl_render(ctx);
    EndTextureMode();

    BeginDrawing();
    for (size_t index = 0; index < 2; index++) {
      Vector2 position = {.x = 0, .y = index * texture.texture.height};
      Rectangle rectangle = {
          .x = 0,
          .y = 0,
          .width = texture.texture.width,
          .height = -1 * texture.texture.height,
      };
      DrawTextureRec(texture.texture, rectangle, position, WHITE);
    }
    EndDrawing();
  }

  free(ctx);
  CloseWindow();
  return 0;
}