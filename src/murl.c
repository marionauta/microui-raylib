#include <assert.h>
#include <raylib.h>
#include <stdlib.h>

#include "../vendor/microui.h"
#include "murl.h"

#define RL_COLOR_FROM(c) ((Color){c.r, c.g, c.b, c.a})
#define RL_RECTANGLE_FROM(r) ((Rectangle){r.x, r.y, r.w, r.h})

int murl_text_width(mu_Font font, const char *str, int len) {
  (void)len;
  (void)font;
  Font rlfont = GetFontDefault();
  Vector2 size = MeasureTextEx(rlfont, str, rlfont.baseSize, 0);
  return size.x;
}

int murl_text_height(mu_Font font) {
  (void)font;
  Font rlfont = GetFontDefault();
  return rlfont.baseSize;
}

void murl_handle_input(mu_Context *ctx) {
  Vector2 mouse_position = GetMousePosition();
  mu_input_mousemove(ctx, (int)mouse_position.x, (int)mouse_position.y);
  Vector2 mouse_wheel_scroll = GetMouseWheelMoveV();
  mu_input_scroll(ctx, (int)mouse_wheel_scroll.x, (int)mouse_wheel_scroll.y);
}

void murl_render(mu_Context *ctx) {
  BeginDrawing();
  ClearBackground(BLACK);

  BeginScissorMode(0, 0, GetScreenWidth(), GetScreenHeight());

  mu_Command *cmd = NULL;
  while (mu_next_command(ctx, &cmd)) {
    switch (cmd->type) {
    case MU_COMMAND_TEXT: {
      int font_size = ctx->text_height(NULL);
      Color text_color = RL_COLOR_FROM(cmd->text.color);
      DrawText(cmd->text.str, cmd->text.pos.x, cmd->text.pos.y, font_size,
               text_color);
    } break;

    case MU_COMMAND_RECT: {
      Rectangle rect = RL_RECTANGLE_FROM(cmd->rect.rect);
      Color rect_color = RL_COLOR_FROM(cmd->rect.color);
      DrawRectangleRec(rect, rect_color);
    } break;

    case MU_COMMAND_ICON:
      break;

    case MU_COMMAND_CLIP: {
      EndScissorMode();
      BeginScissorMode(cmd->clip.rect.x, cmd->clip.rect.y, cmd->clip.rect.w, cmd->clip.rect.h);
    } break;

    case MU_COMMAND_JUMP:
      break;
      
    default:
      assert(0 && "not implemented");
      break;
    }
  }

  EndScissorMode();
  EndDrawing();
}
