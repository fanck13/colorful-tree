src=$(wildcard *.c)
objs=$(patsubst %.c, %.o, $(src))

CUR_DIR  = $(shell pwd)
OUT_DIR = $(CUR_DIR)/../out

OBJ_WITHOUT_DIR = $(notdir $(objs))
OBJ_DIR = $(OUT_DIR)/obj
OBJ_WITH_DIR = $(addprefix $(OBJ_DIR)/,$(OBJ_WITHOUT_DIR))

target = colorful_tree
CC = gcc
CFLAGS = -g -Wall -Werror -Wno-unused
CCFLAGS = 

all:dir_create $(OUT_DIR)/$(target)

define CRT_DIR
	if [ ! -d $(1) ];\
	 	then\
    	mkdir -p $(1);\
	fi	
endef

dir_create:  
	@$(call CRT_DIR,$(OUT_DIR))
	@$(call CRT_DIR,$(OBJ_DIR))


$(OUT_DIR)/$(target):$(OBJ_WITH_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	- rm -f *.o $(target)