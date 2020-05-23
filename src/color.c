#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "color.h"
#include "map.h"



static RBRoot* fore_colors = NULL;
static RBRoot* back_colors = NULL;
static RBRoot* show_configs = NULL;

void create_configs(){
    fore_colors = create_rbtree();
    back_colors = create_rbtree();
    show_configs = create_rbtree();

    Pair pair;
    memset(pair.key, '\0', 10);
    strcpy(pair.key, "black");
    strcpy(pair.value,  "30");
    set(fore_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "red");
    strcpy(pair.value,  "31");
    set(fore_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "green");
    strcpy(pair.value,  "32");
    set(fore_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "yellow");
    strcpy(pair.value,  "33");
    set(fore_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "blue");
    strcpy(pair.value,  "34");
    set(fore_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "purple");
    strcpy(pair.value,  "35");
    set(fore_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "darkgreen");
    strcpy(pair.value,  "36");
    set(fore_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "white");
    strcpy(pair.value,  "37");
    set(fore_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "black");
    strcpy(pair.value,  "40");
    set(back_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "red");
    strcpy(pair.value,  "41");
    set(back_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "green");
    strcpy(pair.value,  "42");
    set(back_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "yellow");
    strcpy(pair.value,  "43");
    set(back_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "blue");
    strcpy(pair.value,  "44");
    set(back_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "purple");
    strcpy(pair.value,  "45");
    set(back_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "darkgreen");
    strcpy(pair.value,  "46");
    set(back_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "white");
    strcpy(pair.value,  "47");
    set(back_colors, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "highlight");
    strcpy(pair.value,  "1");
    set(show_configs, &pair);

    memset(pair.key, '\0', 10);
    strcpy(pair.key, "nonhighlight");
    strcpy(pair.value,  "21");
    set(show_configs, &pair);
}

void destroy_configs(){
    destroy_rbtree(fore_colors);
    destroy_rbtree(back_colors);
    destroy_rbtree(show_configs);
}

char* get_fore_color_index(char* color, char* res){
    int ans = -1;
    Pair pair;
    ans = get(fore_colors, color, &pair);
    if(ans == 0){
        strcpy(res, pair.value);
    }
    return NULL;
}

char* get_back_color_index(char* color, char* res){
    int ans = -1;
    Pair pair;
    ans = get(back_colors, color, &pair);
    if(ans == 0){
        strcpy(res, pair.value);
    }
    return NULL;
}

char* get_show_color_index(char* color, char* res){
    int ans = -1;
    Pair pair;
    ans = get(show_configs, color, &pair);
    if(ans == 0){
        strcpy(res,  pair.value);
    }
    return NULL;
}

void color_print(char* color, char const* const format, ...){
    printf("\033%s", color);
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
    printf("\033[0m");
}

int assemble_color_config(const char* config, char* color_setting){

    int first = -1;
    int second = -1;

    for(int i= 0; config[i] != '\0'; i++){
        if(config[i] == ','){
            if(first == -1){
                first = i;
            }
            else if(second == -1){
                second = i;
                break;
            }
        }
    }

    char fore[10] = {'\0'};
    char back[10] = {'\0'};
    char show[10] = {'\0'};

    for(int i = 0; i<first; i++){
        fore[i] = config[i];
    }
    fore[first] = '\0';
    first++;
    
    int j = 0;
    for(j = 0; first < second; first++){
        back[j] = config[first];
        j++;
    }
    back[j] = '\0';

    second++;
    for(j = 0; config[second] != '\0'; second++){
        show[j] = config[second];
        j++;
    }
    show[j] = '\0';

    char a[10] = {'\0'};
    char b[10] = {'\0'};
    char c[10] = {'\0'};

    get_fore_color_index(fore, a);
    get_back_color_index(back, b);
    get_show_color_index(show, c);

    sprintf(color_setting, "[%s;%s;%sm", c, a,b);

    return 0;
}