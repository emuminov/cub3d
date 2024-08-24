NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
XFLAGS = -lXext -lX11

OBJS_DIR = .obj/
SRC_DIR = src/
LIBFT_DIR = $(SRC_DIR)libft/
MLBX_DIR = $(SRC_DIR)minilibx-linux/

HEADERS = ./src/libft/libft.h ./src/libft/ft_printf/ft_printf.h \
		./src/libft/get_next_line/get_next_line.h include/cub3d.h \

# Compilation of functionality without main
PARSING = $(addprefix parsing/, parse_keys_dir.c parse_keys_colors.c paths.c keys_utils.c arg_manager.c parsing.c utils.c)
SRCS_GAME_LOGIC = $(addprefix game_logic/, controls_handling.c dda.c doors.c init_game.c mouse.c movement.c update_game_state.c mlx_img_utils.c)
SRCS_GRAPHICS = $(addprefix graphics/, draw_utils.c minimap.c render_3d_graphics.c img_pixel_accessors.c)
SRCS_MATH_FUNCS = $(addprefix math_funcs/, grid_bounds_checking.c grid_pixel_conversions.c color.c utils.c vectorf1.c vectorf2.c vectori.c)
SRCS = main.c free.c $(PARSING)
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

SCRS_3D_TESTS = testing_3d_main.c init.c free.c $(SRCS_GAME_LOGIC) $(SRCS_GRAPHICS) $(SRCS_MATH_FUNCS) $(PARSING)
OBJS_3D_TESTS = $(addprefix $(OBJS_DIR), $(SCRS_3D_TESTS:.c=.o))

.SILENT :

all : obj libft minilibx $(NAME)

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
	@echo "$(Red)Check de la norme :${NC}"
	#@norminette $(SRC_DIR) $(HEADERS)
	@echo -n "$(Red)Compilation de cub3d ..${NC}" && sleep 0.2
	@echo -n "$(Red)\rCompilation de cub3d ...${NC}"
	$(CC) $^  $(XFLAGS) $(CFLAGS) $(LIBFT_DIR)libft.a $(MLBX_DIR)libmlx.a -o $(NAME) && sleep 0.1
	@echo "$(Green)\r------Compilation de cub3d finie !-------${NC}"

test3d : obj libft minilibx $(OBJS_3D_TESTS)
	$(CC) $(CFLAGS) $(OBJS_3D_TESTS) $(LIBFT_DIR)libft.a $(MLBX_DIR)libmlx.a -lXext -lX11 -lm -o test3d

$(OBJS_DIR)%.o : $(SRC_DIR)%.c Makefile $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

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
