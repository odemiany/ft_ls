# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: odemiany <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/01 05:01:22 by odemiany          #+#    #+#              #
#    Updated: 2017/11/01 06:31:12 by odemiany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror -I./libft/includes 

LIB = libft/libft.a

SRCS =	additional_ft_for_operate.dir.c apply_sorting.c check_flags.c ft_for_long_output.c ft_for_long_output2.c ft_for_long_output3.c list_function.c main.c operate_dir.c operate_not_dir.c parse_params.c print_folder.c reverse_list.c split_dir_and_not_dir.c
BINS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(BINS)
	gcc -o $(NAME) $(BINS) $(FLAGS) $(LIB)

%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean: 
	/bin/rm -f $(BINS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
