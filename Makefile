INCLUDES_DIR = ./includes
SRC_DIR = ./src
OBJ_DIR = ./obj
MLX_DIR = ./minilibx
MLX_MAC_DIR = ./minilibx

INCLUDES_FILES = fdf.h\
		   		 get_next_line.h\
		         fdf_bindings.h\
		         matrix.h\
				 fdf_rendering.h\

SRC_FILES = fdf.c\
			fdf_init.c\
			object_loading.c\
			get_next_line.c\
			get_next_line_utils.c\
			matrix.c\
			matrix_operations.c\
			projectors.c\
			rotations.c\
			transforms.c\
			fdf_setup.c\
			fdf_rendering.c\
			fdf_rendering_utils.c\
			matrix_interface.c\
			fdf_lines.c\
			fdf_object_normalization.c\
			fdf_perspective_mode.c\
			fdf_isometric_mode.c\
			fdf_cleanup.c\
			fdf_cleanup_utils.c\
			fdf_object_rotation.c\
			fdf_object_translation.c\
			fdf_object_scaling.c\
			fdf_colors.c\
			fdf_hsl.c\
			fdf_object_setup.c\
			fdf_object_transform_core.c\
			fdf_loading_utils.c\
			fdf_math_utils.c\
			fdf_object_control.c\
			fdf_key_hooks.c\
			fdf_object_rendering.c\
			fdf_window_hooks.c\
			fdf_view_controls.c\

INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

NAME = fdf

FT_PRINTF_DIR = ./ft_printf
LIBFTPRINTF = $(FT_PRINTF_DIR)/libftprintf.a
MINILIBX = $(MLX_DIR)/libmlx_Linux.a
MINILIBX_MAC = $(MLX_MAC_DIR)/libmlx_Linux.a

C_FLAGS = -O3 -I$(MLX_DIR) -I$(INCLUDES_DIR) -I$(FT_PRINTF_DIR) -I$(SRC_DIR) -Wall -Wextra -Werror -MMD -MP
MAC_C_FLAGS = -O3 -I$(MLX_MAC_DIR) -I$(INCLUDES_DIR) -I$(FT_PRINTF_DIR) -I$(SRC_DIR) -Wall -Wextra -Werror -MMD -MP

# LFLAGS = -lmlx -framework OpenGL -framework AppKit
LFLAGS = -lXext -lX11 -lm

all:
	mkdir -p $(OBJ_DIR)
	make $(NAME)

$(NAME): $(OBJ) $(MINILIBX) $(LIBFTPRINTF)
	cc $(C_FLAGS) $(OBJ) $(MINILIBX) $(LIBFTPRINTF) $(LFLAGS) -o $(NAME)

$(MAC): $(OBJ) $(MINILIBX) $(LIBFTPRINTF)
	cc $(C_FLAGS) $(OBJ) $(MINILIBX) $(LIBFTPRINTF) $(LFLAGS) -o $(NAME)

$(MINILIBX):
	make -C $(MLX_DIR)

$(LIBFTPRINTF):
	make -C $(FT_PRINTF_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c $(INCLUDES)
	cc $(C_FLAGS) -c $< -o $@

clean:
	make -C $(FT_PRINTF_DIR) clean
	make -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(FT_PRINTF_DIR) fclean
	rm -f $(NAME)

bonus: all

re: fclean all

.PHONY: all clean fclean bonus
