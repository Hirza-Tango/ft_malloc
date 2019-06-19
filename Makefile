ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME=libft_malloc.so
LOCAL_NAME=libft_malloc_$(HOSTTYPE).so
DEPS=libft.a
LIBFT_DIR=libft
INCLUDES=$(LIBFT_DIR)
REL_DEPS=$(DEPS:%=$(LIBFT_DIR)/%)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -I . -I $(INCLUDES) -Ofast
CFILES=
OBJ=$(CFILES:%.c=build/%.o)

$(NAME): $(LOCAL_NAME)
	@ln -s $^ $@

$(LOCAL_NAME): $(OBJ) $(REL_DEPS)
	@gcc $(CFLAGS) -o $@ $^

$(REL_DEPS):
	@make -C $(dir $@)

build/%.o: %.c
	@mkdir -p build
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME);

clean fclean re::
	@for file in $(dir $(REL_DEPS)) ; do $(MAKE) -C $$file $@ ; done

clean::
	@rm -rf build/

fclean:: clean
	@rm -rf $(NAME)

re:: fclean all

.PHONY: clean fclean re all $(REL_DEPS)