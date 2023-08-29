C_FLAGS = -Wall -Wextra -Werror
SRC_FILES = ft_printf.c\
			apply_flags.c\
			param_flags.c\
			standalone_flags.c\
			flags_parsing.c\
			flags_mask.c\
			custom_strings.c\
			custom_strings_utils.c\
			chars_utils.c\
			specifiers.c\
			specifiers_utils.c\
			int_to_base.c\
			uint_to_base.c\
			ull_to_base.c\
			math_utils.c\
			lookups.c

OBJ = $(SRC_FILES:.c=.o)
NAME = libftprintf.a
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	cp	$(LIBFT) $(NAME)
	ar -rc $(NAME) $(OBJ)

$(LIBFT):
	make -C $(LIBFT_DIR) all

%.o:%.c ft_printf.h
	cc $(C_FLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

bonus: all

re: fclean all
