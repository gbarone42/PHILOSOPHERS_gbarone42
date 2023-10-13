#include "philo.h"

void	ft_error(void)
{
	write(1, "\n", 1);
	write(1, "\n\033[1;31mError\033[0m\n\n", 19);
	write(1, "     /\\_/\\     \n", 16);
	write(1, "    ( o.o )    \n", 16);
	write(1, "    > ^ <    42\n", 16);
	write(1, "\n", 1);
	write(1, "\n\033[1;31mError01\033[0m\n\n", 21);
	write(1, "\n", 1);
	exit(1);
}

void	ft_errorr(void)
{
	write(1, "\n", 1);
	write(1, "\n\033[1;31mError\033[0m\n\n", 19);
	write(1, "      ><(((°>      \n", 22);
	write(1, "    <°)))><       \n", 21);
	write(1, "   >°)))><        \n", 20);
	write(1, "  <°)))><         \n", 19);
	write(1, " ><°)))><          \n", 18);
	write(1, "       ><(((°>    \n", 22);
	write(1, " 42      <°)))><  \n", 21);
	write(1, "\n\033[1;31mError02\033[0m\n\n", 22);
	write(1, "\n", 1);
}


void	ft_errorrrr(void)
{
	write(1, "\n", 1);
	write(1, "   <°)))><       \n", 20);
	write(1, "\n\033[1;31mError\033[0m\n\n", 19);
	write(1, "     /\\_/\\     \n", 17);
	write(1, "    ( o.o )    \n", 16);
	write(1, "    > ^ <    42\n", 17);
	write(1, "\n", 1);
	write(1, "\n\033[1;31mError03\033[0m\n\n", 22);
	write(1, "\n", 1);
	exit(1);
}

