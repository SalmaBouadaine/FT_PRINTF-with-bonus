NAME = libftprintf.a 
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
SRCS = ft_printf.c ft_print_nbr.c ft_print_char.c ft_print_hex.c ft_print_ptr.c
OBJS = $(SRCS:.c=.o)
SRCS_BONUS = format_check_bonus.c ft_print_char_bonus.c ft_printf_bonus.c ft_print_hex_bonus.c ft_print_nbr_bonus.c ft_print_ptr_bonus.c ft_print_str_bonus.c ft_print_unbr_bonus.c ft_utils_bonus.c
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): .mandatory

.mandatory: $(OBJS)
	rm -f $(NAME) .bonus
	ar rcs $(NAME) $(OBJS)
	touch .mandatory

bonus: .bonus

.bonus: $(OBJS_BONUS)
	rm -f $(NAME) .mandatory
	ar rcs $(NAME) $(OBJS_BONUS)
	touch .bonus

$(OBJS): ft_printf.h
$(OBJS_BONUS): ft_printf_bonus.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS) .bonus .mandatory

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
