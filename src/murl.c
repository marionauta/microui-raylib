#include <assert.h>
#include <raylib.h>
#include <stdlib.h>

#include "microui.h"
#include "murl.h"

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

struct murl_MouseButtonMap {
  MouseButton rl;
  int mu;
};

struct murl_MouseButtonMap murl_mouse_buttons[3] = {
    {MOUSE_BUTTON_LEFT, MU_MOUSE_LEFT},
    {MOUSE_BUTTON_RIGHT, MU_MOUSE_RIGHT},
    {MOUSE_BUTTON_MIDDLE, MU_MOUSE_MIDDLE},
};

void murl_handle_input(mu_Context *ctx) {
  const int mouse_position_x = GetMouseX();
  const int mouse_position_y = GetMouseY();
  mu_input_mousemove(ctx, mouse_position_x, mouse_position_y);
  Vector2 mouse_wheel_scroll = GetMouseWheelMoveV();
  mu_input_scroll(ctx, (int)mouse_wheel_scroll.x, (int)mouse_wheel_scroll.y);
  for (size_t index = 0; index < 3; index++) {
    struct murl_MouseButtonMap button = murl_mouse_buttons[index];
    if (IsMouseButtonPressed(button.rl)) {
      mu_input_mousedown(ctx, mouse_position_x, mouse_position_y, button.mu);
    } else if (IsMouseButtonReleased(button.rl)) {
      mu_input_mouseup(ctx, mouse_position_x, mouse_position_y, button.mu);
    }
  }
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
      Color text_color = RL_COLOR_FROM_MU(cmd->text.color);
      DrawText(cmd->text.str, cmd->text.pos.x, cmd->text.pos.y, font_size,
               text_color);
    } break;

    case MU_COMMAND_RECT: {
      Rectangle rect = RL_RECTANGLE_FROM_MU(cmd->rect.rect);
      Color rect_color = RL_COLOR_FROM_MU(cmd->rect.color);
      DrawRectangleRec(rect, rect_color);
    } break;

    case MU_COMMAND_ICON:
      break;

    case MU_COMMAND_CLIP: {
      EndScissorMode();
      BeginScissorMode(cmd->clip.rect.x, cmd->clip.rect.y, cmd->clip.rect.w,
                       cmd->clip.rect.h);
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
