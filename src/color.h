#ifndef __COLOR_H__
#define __COLOR_H__

void create_configs();

void destroy_configs();

void color_print(char* color, char const* const format, ...);

int assemble_color_config(const char* config, char* color_setting);

#endif