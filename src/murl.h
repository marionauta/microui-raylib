#ifndef MURL_H
#define MURL_H

#include "../vendor/microui.h"

int murl_text_width(mu_Font, const char*, int);
int murl_text_height(mu_Font);

void murl_handle_input(mu_Context *ctx);
void murl_render(mu_Context *ctx);

#endif // MURL_H
