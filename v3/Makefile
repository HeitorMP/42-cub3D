# VAR DECLARATION
NAME			:= cub3D
NAME_BONUS		:= cub3D_bonus
CC				:= cc
FLAGS			:= -g #-Wall -Wextra -Werror -g #-fsanitize=address
MLXFLAGS		:= -lmlx -lXext -lX11 -lm -lbsd
RM				:= rm -f
SRCDIR			:= srcs
SRCDIR_BONUS	:= srcs_bonus
OBJSDIR			:= objs
OBJSDIR_BONUS	:= objs_bonus
LIBFT			:= ./libft/libft.a
LIBFT_DIR		:= ./libft
MLX_DIR			:= ./minilibx-linux

# SOURCE FILES
SRCS			:=	main.c \
					move/straight.c move/turn.c move/strafe.c move/move_router.c \
					draw_utils/draw_img.c draw_utils/draw_pixel.c draw_utils/draw_walls.c draw_utils/create_rgb.c draw_utils/draw_background.c \
					events/input_handler.c events/dda.c events/dda_utils.c \
					exit_game/exit_request.c exit_game/free_parser.c \
					setup_game/setup.c setup_game/setup_init_direction.c \
					parser/check_file.c parser/colors.c parser/error_parser.c parser/floodfill.c parser/map_utils.c parser/map.c \
					parser/parser_utils.c parser/parser.c parser/utils.c parser/mtr_util.c

SRCS_BONUS		:=	main_bonus.c \
					move/straight_bonus.c move/turn_bonus.c move/strafe_bonus.c move/move_router_bonus.c move/mouse_bonus.c \
					draw_utils/draw_img_bonus.c draw_utils/draw_pixel_bonus.c draw_utils/draw_walls_bonus.c draw_utils/create_rgb_bonus.c draw_utils/draw_background_bonus.c \
					draw_utils/draw_sprite_bonus.c \
					events/lock_mouse_bonus.c events/input_handler_bonus.c events/player_animation_bonus.c events/dda_bonus.c events/dda_utils_bonus.c  events/door_bonus.c \
					exit_game/exit_request_bonus.c \
					setup_game/setup_bonus.c setup_game/setup_init_direction_bonus.c \
					minimap/draw_minimap_bonus.c

OBJS			= ${SRCS:%.c=${OBJSDIR}/%.o}
OBJS_BONUS		= ${SRCS_BONUS:%.c=${OBJSDIR_BONUS}/%.o}

# COLORS
CLR_RMV			:= \033[0m
RED				:= \033[1;31m
GREEN			:= \033[1;32m
YELLOW			:= \033[1;33m
BLUE			:= \033[1;34m
CYAN			:= \033[1;36m

all: ${NAME}

# EXECUTION
${NAME}:		${OBJS} ${LIBFT} MLX
				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME} ${CLR_RMV}..."
				${CC} ${OBJS} -L${MLX_DIR} ${LIBFT} ${MLXFLAGS} ${FLAGS} -o ${NAME}
				@echo "${GREEN}${NAME} created[0m 🎮 ✔️"

bonus: ${NAME_BONUS}

${NAME_BONUS}:	${OBJS_BONUS} ${LIBFT} MLX
				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME} ${CLR_RMV}..."
				${CC} ${OBJS_BONUS} -L${MLX_DIR} ${LIBFT} ${MLXFLAGS} ${FLAGS} -o ${NAME_BONUS}
				@echo "${GREEN}${NAME} bonus created[0m 🎮 ✔️"

# CREATE OBJS
${OBJS}:		${OBJSDIR}/%.o: ${SRCDIR}/%.c
				@mkdir -p ${OBJSDIR}
				@mkdir -p ${OBJSDIR}/move
				@mkdir -p ${OBJSDIR}/setup_game
				@mkdir -p ${OBJSDIR}/exit_game
				@mkdir -p ${OBJSDIR}/draw_utils
				@mkdir -p ${OBJSDIR}/events
				@mkdir -p ${OBJSDIR}/parser
				${CC} -I. -O3 ${FLAGS} -c $< -o $@

${OBJS_BONUS}:	${OBJSDIR_BONUS}/%.o: ${SRCDIR_BONUS}/%.c
				@mkdir -p ${OBJSDIR_BONUS}
				@mkdir -p ${OBJSDIR_BONUS}/move
				@mkdir -p ${OBJSDIR_BONUS}/setup_game
				@mkdir -p ${OBJSDIR_BONUS}/exit_game
				@mkdir -p ${OBJSDIR_BONUS}/draw_utils
				@mkdir -p ${OBJSDIR_BONUS}/events
				@mkdir -p ${OBJSDIR_BONUS}/minimap
				${CC} -I. -O3 ${FLAGS} -c $< -o $@

${LIBFT}:
				${MAKE} -C ${LIBFT_DIR}
MLX:
				${MAKE} -C ${MLX_DIR}

clean:
				@ ${RM} -rf ${OBJSDIR}
				@ ${RM} -rf ${OBJSDIR_BONUS}
				@ ${MAKE} clean -C ${LIBFT_DIR}
				@ ${MAKE} clean -C ${MLX_DIR}
				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}objs ✔️"

fclean:			clean
				@ ${RM} ${NAME}
				@ ${RM} ${NAME_BONUS}
				@ ${MAKE} fclean -C ${LIBFT_DIR}
				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}binary ✔️"

re:				fclean all bonus