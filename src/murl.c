#include <assert.h>
#include <raylib.h>
#include <stdlib.h>

#include "microui.h"
#include "murl.h"

void murl_setup_font_ex(mu_Context *ctx, const Font *font) {
  ctx->style->font = (mu_Font)font;
  ctx->text_width = murl_text_width;
  ctx->text_height = murl_text_height;
  ctx->style->spacing = MURL_TEXT_SPACING;
}

int murl_text_width(mu_Font font, const char *str, int len) {
  (void)len;
  Font rlfont = MURL_FONT_FROM_MU(font);
  Vector2 size = MeasureTextEx(rlfont, str, rlfont.baseSize, MURL_TEXT_SPACING);
  return size.x;
}

int murl_text_height(mu_Font font) {
  Font rlfont = MURL_FONT_FROM_MU(font);
  return rlfont.baseSize;
}

void murl_handle_mouse_scroll(mu_Context *ctx) {
  const Vector2 mouse_wheel_scroll = GetMouseWheelMoveV();
  mu_input_scroll(ctx, (int)mouse_wheel_scroll.x * -30,
                  (int)mouse_wheel_scroll.y * -30);
}

struct murl__MouseButtonMap {
  MouseButton rl;
  int mu;
};

static struct murl__MouseButtonMap murl__mouse_buttons[] = {
    {MOUSE_BUTTON_LEFT, MU_MOUSE_LEFT},
    {MOUSE_BUTTON_RIGHT, MU_MOUSE_RIGHT},
    {MOUSE_BUTTON_MIDDLE, MU_MOUSE_MIDDLE},
    {-1, -1},
};

void murl_handle_mouse_buttons_input_ex(mu_Context *ctx, int x, int y) {
  for (size_t index = 0;; index++) {
    struct murl__MouseButtonMap button = murl__mouse_buttons[index];
    if (button.rl == -1U) {
      break;
    }
    if (IsMouseButtonPressed(button.rl)) {
      mu_input_mousedown(ctx, x, y, button.mu);
    } else if (IsMouseButtonReleased(button.rl)) {
      mu_input_mouseup(ctx, x, y, button.mu);
    }
  }
}

struct murl__KeyboardKeyMap {
  KeyboardKey rl;
  int mu;
};

static struct murl__KeyboardKeyMap murl__keyboard_keys[] = {
    {KEY_LEFT_SHIFT, MU_KEY_SHIFT},    {KEY_RIGHT_SHIFT, MU_KEY_SHIFT},
    {KEY_LEFT_CONTROL, MU_KEY_CTRL},   {KEY_RIGHT_CONTROL, MU_KEY_CTRL},
    {KEY_LEFT_ALT, MU_KEY_ALT},        {KEY_RIGHT_ALT, MU_KEY_ALT},
    {KEY_ENTER, MU_KEY_RETURN},        {KEY_KP_ENTER, MU_KEY_RETURN},
    {KEY_BACKSPACE, MU_KEY_BACKSPACE}, {-1, -1},
};

void murl_handle_keyboard_input(mu_Context *ctx) {
  for (size_t index = 0;; index++) {
    struct murl__KeyboardKeyMap key = murl__keyboard_keys[index];
    if (key.rl == -1U) {
      break;
    }
    if (IsKeyPressed(key.rl)) {
      mu_input_keydown(ctx, key.mu);
    } else if (IsKeyReleased(key.rl)) {
      mu_input_keyup(ctx, key.mu);
    }
  }
}

void murl_handle_text_input(mu_Context *ctx) {
  char buffer[512];
  for (size_t index = 0; index < 512; index++) {
    char c = GetCharPressed();
    buffer[index] = c;
    if (c == '\0') {
      break;
    }
  }
  mu_input_text(ctx, buffer);
}

void murl_handle_input(mu_Context *ctx) {
  const int mouse_position_x = GetMouseX();
  const int mouse_position_y = GetMouseY();
  mu_input_mousemove(ctx, mouse_position_x, mouse_position_y);
  murl_handle_mouse_scroll(ctx);
  murl_handle_mouse_buttons_input_ex(ctx, mouse_position_x, mouse_position_y);
  murl_handle_keyboard_input(ctx);
  murl_handle_text_input(ctx);
}

void murl_render(mu_Context *ctx) {
  BeginScissorMode(0, 0, GetScreenWidth(), GetScreenHeight());

  mu_Command *cmd = NULL;
  while (mu_next_command(ctx, &cmd)) {
    switch (cmd->type) {
    case MU_COMMAND_TEXT: {
      Font font = MURL_FONT_FROM_MU(cmd->text.font);
      Vector2 text_position = MURL_VECTOR2_FROM_MU(cmd->text.pos);
      int font_size = ctx->text_height(&font);
      Color text_color = MURL_COLOR_FROM_MU(cmd->text.color);
      DrawTextEx(font, cmd->text.str, text_position, font_size,
                 ctx->style->spacing, text_color);
    } break;

    case MU_COMMAND_RECT: {
      Rectangle rect = MURL_RECTANGLE_FROM_MU(cmd->rect.rect);
      Color rect_color = MURL_COLOR_FROM_MU(cmd->rect.color);
      DrawRectangleRec(rect, rect_color);
    } break;

    case MU_COMMAND_ICON: {
      Color icon_color = MURL_COLOR_FROM_MU(cmd->icon.color);
      char *icon = "?";
      switch (cmd->icon.id) {
      case MU_ICON_CLOSE: {
        icon = "x";
      } break;
      case MU_ICON_CHECK: {
        icon = "*";
      } break;
      case MU_ICON_COLLAPSED: {
        icon = "+";
      } break;
      case MU_ICON_EXPANDED: {
        icon = "-";
      } break;
      default:
        assert(0 && "unreachable");
      }
      DrawText(icon, cmd->icon.rect.x, cmd->icon.rect.y, cmd->icon.rect.h,
               icon_color);
    } break;

    case MU_COMMAND_CLIP: {
      EndScissorMode();
      BeginScissorMode(cmd->clip.rect.x, cmd->clip.rect.y, cmd->clip.rect.w,
                       cmd->clip.rect.h);
    } break;

    default:
      assert(0 && "unreachable");
      break;
    }
  }

  EndScissorMode();
}
