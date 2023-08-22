CC      = gcc
CFLAGS  = -Werror -Wall -Wextra -pthread -g
NAME    = philo_bonus

MODE    = none
ifeq ($(MODE), pretty)
    CFLAGS  += -D DEBUG_FORMATTING=1
endif
ifeq ($(MODE), debug)
    CFLAGS  += -D DEBUG_FORMATTING=1 -fsanitize=thread -g
endif

SRC     = newphil.c errors.c func01.c func02.c  # Add new source files here
SRCS    = $(SRC)
OBJ     = $(SRC:.c=.o)
OBJS    = $(OBJ:.o=.o)

INC     = -I ./includes/

.PHONY: all re clean fclean test philo philotest

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "\n\033[1;36m  ==> Compilation complete! Run './$(NAME)' to start the program.\033[0m\n"

%.o: %.c
	@printf "\033[1;33m  Compiling $<...\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

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