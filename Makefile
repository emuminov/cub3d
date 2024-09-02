NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -O2
XFLAGS = -lXext -lX11

OBJS_DIR = .obj/
SRC_DIR = src/
LIBFT_DIR = $(SRC_DIR)libft/
MLBX_DIR = $(SRC_DIR)minilibx-linux/

HEADERS = ./src/libft/libft.h ./src/libft/ft_printf/ft_printf.h \
		./src/libft/get_next_line/get_next_line.h include/cub3d.h \
		include/game_logic.h include/graphics.h include/math_funcs.h \
		include/parsing.h include/constants.h

# Compilation of functionality without main
SRCS_PARSING = $(addprefix parsing/, _arg_manager.c _keys_utils.c _parse_keys_colors.c _parse_keys_dir.c _parse_map.c _parse_map_utils.c _parsing.c _paths.c _utils.c extract_params_from_cub_file.c)
SRCS_GAME_LOGIC = $(addprefix game_logic/, _controls_handling.c _doors.c _exit_game.c _mlx_img_utils.c _mouse.c _movement.c dda.c init_animation_textures.c init_game.c)
SRCS_GRAPHICS = $(addprefix graphics/, _draw_utils.c _img_pixel_accessors.c _minimap.c render_3d_graphics.c _hands_animation.c)
SRCS_MATH_FUNCS = $(addprefix math_funcs/, grid_bounds_checking.c grid_pixel_conversions.c rgb_int_conversions.c rgb_transformations.c utils.c vectorf1.c vectorf2.c vectori.c)
SRCS =  main.c free.c $(SRCS_GAME_LOGIC) $(SRCS_GRAPHICS) $(SRCS_MATH_FUNCS) $(SRCS_PARSING)
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o)) 

.SILENT:

all : obj libft minilibx $(NAME)

hide_mouse :
	@$(MAKE) ADDITIONAL_FLAGS=-DHIDE_MOUSE

obj :
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/game_logic
	@mkdir -p $(OBJS_DIR)/graphics
	@mkdir -p $(OBJS_DIR)/math_funcs
	@mkdir -p $(OBJS_DIR)/parsing

minilibx :
	@make --no-print-directory -C $(MLBX_DIR)

libft :
	@make --no-print-directory -C $(LIBFT_DIR)

$(NAME) : $(OBJS)
	@#echo "$(Red)Check de la norme :${NC}"
	@#norminette $(SRC_DIR) $(HEADERS)
	@echo -n "$(Red)Compilation de cub3d ..${NC}" && sleep 0.2
	@echo -n "$(Red)\rCompilation de cub3d ...${NC}"
	$(CC) $^ $(CFLAGS) $(LIBFT_DIR)libft.a $(MLBX_DIR)libmlx.a -lm $(XFLAGS) $(ADDITIONAL_FLAGS) -o $(NAME) && sleep 0.1
	@echo "$(Green)\r------Compilation de cub3d finie !-------${NC}"

$(OBJS_DIR)%.o : $(SRC_DIR)%.c Makefile $(HEADERS)
	$(CC) $(CFLAGS) $(ADDITIONAL_FLAGS) -c $< -o $@

clean :
	@cd $(MLBX_DIR) && $(MAKE) --no-print-directory clean
	@cd $(LIBFT_DIR) && $(MAKE) --no-print-directory clean
	@rm -rf $(OBJS_DIR)

fclean :
	@cd $(MLBX_DIR) && $(MAKE) --no-print-directory clean
	@cd $(LIBFT_DIR) && $(MAKE) --no-print-directory fclean
	@rm -rf $(OBJS_DIR) $(NAME)

re : fclean
	$(MAKE) all

# allows printing of Makefile variables
# make print-SRCS ------> prints content of the SRCS
print-%: 
	@echo $*=$($*)

sus:
	@echo "$(IRed)           ⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀        $(NC)"
	@echo "$(IRed)        ⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀     $(NC)"
	@echo "$(IRed)        ⣼⣿⠋       ⢀⣀⣀⠈⢻⣿⣿⡄    $(NC)"
	@echo "$(IRed)       ⣸⣿⡏   ⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄   $(NC)"
	@echo "$(IRed)       ⣿⣿⠁  ⢰⣿⣿⣯⠁       ⠈⠙⢿⣷⡄ $(NC)"
	@echo "$(IRed)  ⣀⣤⣴⣶⣶⣿⡟   ⢸⣿⣿⣿⣆          ⣿⣷ $(NC)"
	@echo "$(IRed) ⢰⣿⡟⠋⠉⣹⣿⡇   ⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿ $(NC)"
	@echo "$(IRed) ⢸⣿⡇  ⣿⣿⡇    ⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃ $(NC)"
	@echo "$(IRed) ⣸⣿⡇  ⣿⣿⡇     ⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛⢻⣿⡇  $(NC)"
	@echo "$(IRed) ⠸⣿⣧⡀ ⣿⣿⡇                ⣿⣿⠃  $(NC)"
	@echo "$(IRed)  ⠛⢿⣿⣿⣿⣿⣇     ⣰⣿⣿⣷⣶⣶⣶⣶⠶ ⢠⣿⣿   $(NC)"
	@echo "$(IRed)       ⣿⣿     ⣿⣿⡇ ⣽⣿⡏⠁  ⢸⣿⡇   $(NC)"
	@echo "$(IRed)       ⣿⣿     ⣿⣿⡇ ⢹⣿⡆   ⣸⣿⠇   $(NC)"
	@echo "$(IRed)       ⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁ ⠈⠻⣿⣿⣿⣿⡿⠏    $(NC)"
	@echo "$(IRed)       ⠈⠛⠻⠿⠿⠿⠿⠋⠁              $(NC)"
	@echo "$(White)         ░█▀▀░█░█░█▀▀$(NC)"
	@echo "$(White)         ░▀▀█░█░█░▀▀█$(NC)"
	@echo "$(White)         ░▀▀▀░▀▀▀░▀▀▀$(NC)"

.PHONY : all clean fclean re obj libft print-% sus

# COLORS =======================================================================

# Reset
NC=\033[0m

# Regular Colors
Black=\033[0;30m
Red=\033[0;31m
Green=\033[0;32m
Yellow=\033[0;33m
Blue=\033[0;34m
Purple=\033[0;35m
Cyan=\033[0;36m
White=\033[0;37m

# Bold
BBlack=\033[1;30m
BRed=\033[1;31m
BGreen=\033[1;32m
BYellow=\033[1;33m
BBlue=\033[1;34m
BPurple=\033[1;35m
BCyan=\033[1;36m
BWhite=\033[1;37m

# Underline
UBlack=\033[4;30m
URed=\033[4;31m
UGreen=\033[4;32m
UYellow=\033[4;33m
UBlue=\033[4;34m
UPurple=\033[4;35m
UCyan=\033[4;36m
UWhite=\033[4;37m

# Background
On_Black=\033[40m
On_Red=\033[41m
On_Green=\033[42m
On_Yellow=\033[43m
On_Blue=\033[44m
On_Purple=\033[45m
On_Cyan=\033[46m
On_White=\033[47m

# High Intensity
IBlack=\033[0;90m
IRed=\033[0;91m
IGreen=\033[0;92m
IYellow=\033[0;93m
IBlue=\033[0;94m
IPurple=\033[0;95m
ICyan=\033[0;96m
IWhite=\033[0;97m

# Bold High Intensity
BIBlack=\033[1;90m
BIRed=\033[1;91m
BIGreen=\033[1;92m
BIYellow=\033[1;93m
BIBlue=\033[1;94m
BIPurple=\033[1;95m
BICyan=\033[1;96m
BIWhite=\033[1;97m

# High Intensity backgrounds
On_IBlack=\033[0;100m
On_IRed=\033[0;101m
On_IGreen=\033[0;102m
On_IYellow=\033[0;103m
On_IBlue=\033[0;104m
On_IPurple=\033[0;105m
On_ICyan=\033[0;106m
On_IWhite=\033[0;107m
