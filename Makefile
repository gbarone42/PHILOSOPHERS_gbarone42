CC      = gcc
CFLAGS  = -Werror -Wall -Wextra -pthread -g
NAME    = philo

SRC     = main.c errors.c init.c validate.c thread.c siesta.c observe.c# Add new source files here
SRCS    = $(SRC)
OBJ     = $(SRC:.c=.o)
OBJS    = $(OBJ:.o=.o)

INC     = -I ./includes/

.PHONY: all re clean fclean test philo philotest

all: $(NAME)

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

%.o: %.c
	@printf "\033[1;33m  Compiling $<...\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@printf "\033[1;31m\n"
	@echo "  _________________________________________________________"
	@echo " /                                                         \\"
	@echo "       Clearing the Threads of Temporary Existence...         "
	@echo "            💧 Threads may vanish, but wisdom remains.       "
	@echo "  _________________________________________________________"
	@echo "\033[0m"
	@rm -f $(OBJS)

fclean: clean
	@printf "\033[1;31m\n"
	@echo "  __________________________________________________________"
	@echo " /                                                          \\"
	@echo "       Erasing the Echoes of Philosophical Journey...         "
	@echo "          🔥 Let go of attachments, embrace the void.         "
	@echo "  __________________________________________________________"
	@echo "\033[0m"
	@rm -f $(NAME)

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
	