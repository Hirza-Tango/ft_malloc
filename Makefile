ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME=libft_malloc.so
LOCAL_NAME=libft_malloc_$(HOSTTYPE).so
DEPS=libft/libft.a ft_printf/libftprintf.a
LIBFT_DIR=libft
INCLUDES=$(LIBFT_DIR)/includes
REL_DEPS=$(DEPS:%=$(LIBFT_DIR)/%)
CC=gcc
CFLAGS=-Wall -Wextra -shared -Werror -I . -g -I $(INCLUDES) -Ofast
CFILES=	alloc_util.c	free.c	realloc.c	show_alloc_mem.c	malloc.c
OBJ=$(CFILES:%.c=build/%.so)

$(NAME): $(LOCAL_NAME)
	@ln -s $^ $@

$(LOCAL_NAME): $(OBJ)
	@$(CC) $(CFLAGS) -shared -fPIC $^ -o $@

$(REL_DEPS):
	@make -C $(dir $@)

build/malloc.so: malloc.c $(REL_DEPS) build/alloc_util.so
	@mkdir -p build
	@$(CC) $(CFLAGS) -fPIC $^ -o $@

build/show_alloc_mem.so: show_alloc_mem.c $(REL_DEPS) build/alloc_util.so
	@mkdir -p build
	@$(CC) $(CFLAGS) -fPIC $^ -o $@

build/%.so: %.c $(REL_DEPS)
	@mkdir -p build
	@$(CC) $(CFLAGS) -fPIC $^ -o $@

all: $(NAME);

clean fclean re::
	@for file in $(dir $(REL_DEPS)) ; do $(MAKE) -C $$file $@ ; done

clean::
	@rm -rf build/

fclean:: clean
	@rm -rf $(NAME) $(LOCAL_NAME)

re:: fclean all

.PHONY: clean fclean re all $(REL_DEPS)