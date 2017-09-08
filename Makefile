NAME= lem-in
SRC= srcs/main.c \
	srcs/ft_put_lines.c \
	srcs/ft_put_solution.c \
	srcs/ft_multi_path.c \
	srcs/ft_put_multi_path.c \
	srcs/ft_dijkstra.c \
	srcs/ft_dijkstra_distance.c \
	srcs/parsing/ft_parse.c \
	srcs/parsing/ft_parse_flags.c \
	srcs/parsing/ft_get_lem_nbr.c \
	srcs/parsing/ft_get_case.c \
	srcs/parsing/ft_is_case_start.c \
	srcs/parsing/ft_get_last_attr.c \
	srcs/parsing/ft_get_last_modified_capacity.c \
	srcs/parsing/ft_parsing_actions.c \
	srcs/parsing/ft_get_new_tube.c \
	srcs/parsing/ft_get_new_room.c \
	srcs/parsing/ft_get_new_cmd.c \
	srcs/parsing/ft_get_new_note.c \
	srcs/parsing/ft_get_set_states.c \
	srcs/parsing/ft_check_integrity.c \
	srcs/ft_create_mem_block.c \
	srcs/ft_mem_block_push_back_elem.c \
	srcs/heap/ft_create_heap.c \
	srcs/heap/ft_free_heap.c \
	srcs/heap/ft_heap_add_elem.c \
	srcs/heap/ft_heap_remove_elem.c \
	srcs/heap/ft_make_heap.c \
	srcs/heap/ft_percolate_down.c \
	srcs/heap/ft_percolate_up.c \
	srcs/ft_put_lem_in_error.c

OBJ= $(SRC:.c=.o)
HDR_PATH= ./libft/includes/
CC= gcc
CC_FLAGS= -Ofast -v -Weverything -Wall -Wextra  -g3 -fsanitize=address -fsanitize-blacklist=my_ignores.txt #-Werror
#VPATH=./srcs:./obj:./includes/

all: submodule $(NAME)

submodule:
	@make -C libft/

$(NAME): $(OBJ)
	$(CC) $(CC_FLAGS) $^ -L./libft -lft -o $(NAME)
%.o : %.c
	$(CC) $(CC_FLAGS) $< -c -I$(HDR_PATH) -I./includes -o $@

clean:
	rm -f $(OBJ)
	make -C libft/ clean
fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
