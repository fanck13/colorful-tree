src=$(wildcard *.c)
objs=$(patsubst %.c, %.o, $(src))

CUR_DIR  = $(shell pwd)
OUT_DIR = $(CUR_DIR)/../out

OBJ_WITHOUT_DIR = $(notdir $(objs))
OBJ_DIR = $(OUT_DIR)/obj
OBJ_WITH_DIR = $(addprefix $(OBJ_DIR)/,$(OBJ_WITHOUT_DIR))

target=colorful_tree_test
INC = -I../src/


CC = gcc
CFLAGS = -g -Wall -Werror -Wno-unused
CCFLAGS = -g

all:dir_create $(OUT_DIR)/$(target)

define CRT_DIR
	if [ ! -d $(1) ];\
	 	then\
    	mkdir -p $(1);\
    	echo "******$(1) created success!!!******";\
    else\
      echo "******$(1) has been created!!!******";\
	fi	
endef

dir_create:  
	@$(call CRT_DIR,$(OUT_DIR))
	@$(call CRT_DIR,$(OBJ_DIR))


$(OUT_DIR)/$(target):$(OBJ_WITH_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c $(INC) $< -o $@

.PHONY:clean
clean:
	- rm -f ../*.o $(target)
