NAME = philo

# Directories
SRC_DIR = src
OBJ_DIR = objs
INCLUDE_DIR = includes

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Header files
HDRS = $(wildcard $(INCLUDE_DIR)/*.h)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -I$(INCLUDE_DIR) -pthread
RM = rm -rf
MKDIR = mkdir -p

# Color codes
CLR_RMV = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
CYAN = \033[1;36m
GOLD = \033[1;33m

# Rule to compile individual source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS)
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[2K\r${BLUE}[BUILD - $(NAME)]${CLR_RMV} '$<' ${END}"

# Build the executable
$(NAME): $(OBJS)
	@printf "\033[1;36m\n"
	@echo "  _________________________________________________________"
	@echo " /                                                         \\"
	@echo "     Welcome to the Realm of Wisdom and Threads!           "
	@echo "            📚🔮🌌 The Multiverse Awaits! 🌌🔮📚             "
	@echo "                                                          "
	@echo "     Unravel the secrets of existence through the         "
	@echo "     profound journey of philosophers and threads.       "
	@echo "     Each thread a philosopher, each moment an           "
	@echo "     opportunity for enlightenment.                     "
	@echo "                                                          "
	@echo "            Be the code hero philosophers need!         "
	@echo "  _________________________________________________________"
	@echo "\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "\n\033[1;36m  ==> Compilation complete! Embark on your quest with './$(NAME)'.\033[0m\n"

all: $(NAME)

clean:
	@printf "\033[1;31m\n"
	@echo "  _________________________________________________________"
	@echo " /                                                         \\"
	@echo "       Clearing the Threads of Temporary Existence...         "
	@echo "            💧 Threads may vanish, but wisdom remains.       "
	@echo "  _________________________________________________________"
	@echo "\033[0m"
	@$(RM) $(OBJ_DIR)
	@echo "${YELLOW}${CLR_RMV}"

fclean: clean
	@printf "\033[1;31m\n"
	@echo "  __________________________________________________________"
	@echo " /                                                          \\"
	@echo "       Erasing the Echoes of Philosophical Journey...         "
	@echo "          🔥 Let go of attachments, embrace the void.         "
	@echo "  __________________________________________________________"
	@echo "\033[0m"
	@$(RM) $(NAME)
	@echo "${RED}${CLR_RMV}"

re: fclean all
	@printf "\033[1;35m\n"
	@echo "  __________________________________________________________"
	@echo " /                                                          \\"
	@echo "    Rekindling the Flames of Enlightenment...                 "
	@echo "      ✨ Threads reawaken, wisdom shines anew.                "
	@echo "  __________________________________________________________"
	@echo "\033[0m"

test:
	@printf "\033[1;32m\n"
	@echo "  ________________________________________________________"
	@echo " /                                                        \\"
	@echo "       Welcome to Philosopher's Test!                        "
	@echo "                                                              "
	@echo "  To test your program, run './$(NAME)' with arguments:     "
	@echo "                                                              "
	@echo "  Usage: ./$(NAME) num_of_philosophers time_to_die            "
	@echo "         time_to_eat time_to_sleep [num_of_times]            "
	@echo "                                                              "
	@echo "  🎯 num_of_philosophers: Number of philosophers            "
	@echo "  ⏰ time_to_die: Time in milliseconds before a              "
	@echo "              philosopher dies without eating               "
	@echo "  🍽️ time_to_eat: Time in milliseconds it takes for a       "
	@echo "              philosopher to eat                            "
	@echo "  💤 time_to_sleep: Time in milliseconds a philosopher      "
	@echo "             sleeps after eating                            "
	@echo "  🔄 num_of_times (optional): Number of times each          "
	@echo "             philosopher must eat                           "
	@echo "                                                              "
	@echo "  ➡️ Example: ./$(NAME) 5 800 200 200                        "
	@echo "\033[0m"

.PHONY: all clean fclean re test philo philotest