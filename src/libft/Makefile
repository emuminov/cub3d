NAME=libft.a

SRCS=ft_atoi.c \
ft_atoi_base.c \
ft_atol.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_isspace.c \
ft_ltoa_base.c \
ft_ultoa_base.c \
ft_itoa.c \
ft_itoa_base.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_free_split.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_printf/ft_printf.c \
ft_printf/ft_printf_funcs.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strcmp.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c

OBJ=$(SRCS:%.c=%.o)

.SILENT :

HEADER=libft.h

CC=cc

CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(Red)Check de la norme de libft:${NC}"
	#@norminette
	@echo -n "$(Red)Compilation en cours .${NC}"
	@echo -n "$(Purple)\rCompilation en cours ..${NC}"  && sleep 0.2
	@echo -n "$(Blue)\rCompilation en cours ...${NC}" && sleep 0.5
	@echo "$(Green)\r------Compilation de libft finie !-------${NC}"
	ar cr $(NAME) $^

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I .


clean:
	@echo -n "$(Red).o en cours de suppression ...${NC}"
	@rm $(OBJ) $(OBJ_BONUS) -f && sleep 0.2
	@echo "$(Green)\r---------.o supprime !----------${NC}"

fclean: clean
	@echo -n "$(Red).a en cours de suppression...${NC}"
	@rm $(NAME) -f && sleep 0.2
	@echo "$(Green)\r---------.a supprime !----------${NC}"


re: fclean
	$(MAKE) all

.PHONY: all clean re fclean

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
