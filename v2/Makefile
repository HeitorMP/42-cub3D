# VAR DECLARATION
NAME		:= cub3D
CC			:= cc
FLAGS		:= -Wall -Wextra -Werror -g #-fsanitize=address
MLXFLAGS	:= -lmlx -lXext -lX11 -lm -lbsd
RM			:= rm -f
SRCDIR		:= srcs
OBJSDIR		:= objs
LIBFT		:= ./libft/libft.a
LIBFT_DIR	:= ./libft
MLX_DIR		:= ./minilibx-linux

# SOURCE FILES
SRCS		:=	main.c \
				move/straight.c move/turn.c move/strafe.c move/move_router.c move/mouse.c \
				draw_utils/draw_img.c draw_utils/draw_pixel.c draw_utils/draw_walls.c \
				events/lock_mouse.c events/input_handler.c \
				exit_game/exit_request.c \
				setup_game/setup.c setup_game/setup_init_direction.c

OBJS		= ${SRCS:%.c=${OBJSDIR}/%.o}

# COLORS
CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m

all: ${NAME}

# EXECUTION
${NAME}:	${OBJS} ${LIBFT} mlx
			@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME} ${CLR_RMV}..."
			${CC} ${OBJS} -L${MLX_DIR} ${LIBFT} ${MLXFLAGS} ${FLAGS} -o ${NAME}
			@echo "${GREEN}${NAME} created[0m 🎮 ✔️"

${OBJS}:	${OBJSDIR}/%.o: ${SRCDIR}/%.c
			@mkdir -p ${OBJSDIR}
			@mkdir -p ${OBJSDIR}/move
			@mkdir -p ${OBJSDIR}/setup_game
			@mkdir -p ${OBJSDIR}/exit_game
			@mkdir -p ${OBJSDIR}/draw_utils
			@mkdir -p ${OBJSDIR}/events
			${CC} -I. -O3 ${FLAGS} -c $< -o $@

${LIBFT}:
			${MAKE} -C ${LIBFT_DIR}
mlx:
			${MAKE} -C ${MLX_DIR}

# CREATE OBJS
clean:
			@ ${RM} -rf ${OBJSDIR}
			@ ${MAKE} clean -C ${LIBFT_DIR}
			@ ${MAKE} clean -C ${MLX_DIR}
			@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ ${MAKE} fclean -C ${LIBFT_DIR}
			@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}binary ✔️"

re:			fclean all
