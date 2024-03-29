NAME = ft_malcom
INCLUDES = ./includes
SRC_PATH = ./sources
OBJ_PATH = $(SRC_PATH)/debug
SRC_NAMES = main.c parser.c error.c debug.c nslookup.c interfaces.c mac.c ip.c \
arp.c verbose.c poisoning.c time.c flooding.c ihm.c interactive.c icmp.c mini_nmap.c
OBJ_NAMES = $(SRC_NAMES:.c=.o)
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAMES))
OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAMES))
LUTILS_PATH = ./libft
LUFLAGS = -L$(LUTILS_PATH) -lft
IFLAGS = -I$(INCLUDES)
CFLAGS = -Wall -Wextra -Werror 
DFLAGS = 
CC = clang

all: $(NAME)

welcome:
	@clear
	@figlet ft_malcom | lolcat 2>/dev/null
	@$(eval SHELL:=/bin/bash)
	@echo -e "\n"

$(OBJ_PATH):
	@mkdir $@
	@$(eval SHELL:=/bin/bash)
	@echo -e "\e[4;35mBuilding ft_malcom sources:\e[0m"

$(NAME): welcome $(OBJ_PATH) $(OBJS)
	@$(eval SHELL:=/bin/bash)
	@echo -e "✅ Source files: $(shell echo $(SRC_NAMES) | wc -w) / $(shell echo $(SRC_NAMES) | wc -w)\033[0m --> \033[1;32m[Done]\033[0m\n"
	@echo -e "\e[4;35mBuilding Libft:\e[0m"
	@make -C $(LUTILS_PATH) --no-print-directory
	@$(CC) $(DFLAGS) -o $@ $(OBJS) $(LUFLAGS)
	@echo -e "\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $? -o $@
	@$(eval SHELL:=/bin/bash)
	@echo -e "🔧 Source files: $(shell ls -1 $(OBJ_PATH) | wc -l) / $(shell echo $(SRC_NAMES) | wc -w)\r\c"

clean:
	@rm -rf $(OBJ_PATH)
	@make -C $(LUTILS_PATH) fclean --no-print-directory

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
