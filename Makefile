ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME=libft_malloc.so
LOCAL_NAME=libft_malloc_$(HOSTTYPE).so
DEPS=libft/libft.a
LIBFT_DIR=libft
INCLUDES=$(LIBFT_DIR)/includes
REL_DEPS=$(DEPS:%=$(LIBFT_DIR)/%)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -I . -I $(INCLUDES) -O3
CFILES=	alloc_util.c	free.c	realloc.c	show_alloc_mem.c	malloc.c
OBJ=$(CFILES:%.c=build/%.o)

$(NAME): $(LOCAL_NAME)
	@ln -sf $^ $@

$(LOCAL_NAME): $(OBJ) $(REL_DEPS)
	@$(CC) $(CFLAGS) -shared $(OBJ) -L libft/libft -lft -o $@ -D MUTEX_ENABLE

$(REL_DEPS):
	@make -C $(dir $@)

build/%.o: %.c ft_malloc.h
	@mkdir -p build
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME);

clean fclean re::
	@for file in $(dir $(REL_DEPS)) ; do $(MAKE) -C $$file $@ ; done

clean::
	@rm -rf build/

fclean:: clean
	@rm -rf $(NAME) $(LOCAL_NAME)

re:: fclean all

.PHONY: clean fclean re all $(REL_DEPS)
