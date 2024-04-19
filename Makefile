# Standard
NAME				= so_long

# Directories
LIBFT				= ./libft/libft.a
MINILIBX			= ./minilibx-linux/libmlx.a
INC				= inc/
SRC_DIR				= srcs/
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra -I
MFLAGS				= -Lminilibx-linux -lmlx_Linux -lX11 -lXext
RM					= rm -f

# Source Files
SO_LONG_DIR		=	$(SRC_DIR)so_long/main.c \
					$(SRC_DIR)so_long/check_map.c \
					$(SRC_DIR)so_long/init_and_free.c \
					$(SRC_DIR)so_long/hook_inputs.c \
					$(SRC_DIR)so_long/display_map.c

# Concatenate all source files
SRCS 				= $(SO_LONG_DIR)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules
start:				
					@make all

$(LIBFT):
					@make -C ./libft

$(MINILIBX):		
					@make -C ./minilibx-linux

all: 				$(NAME)

$(NAME): 			$(OBJ) $(LIBFT) $(MINILIBX)
					@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) $(MINILIBX) $(MFLAGS) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C ./libft
					@make clean -C ./minilibx-linux

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@$(RM) $(MINILIBX)

re: fclean all

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re
