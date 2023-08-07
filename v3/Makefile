# VAR DECLARATION
NAME			:= cub3D
NAME_BONUS		:= cub3D_bonus
CC				:= cc
FLAGS			:= -Wall -Wextra -Werror -Wno-unused-result -g #-fsanitize=address
MLXFLAGS		:= -lmlx -lXext -lX11 -lm -lz -lbsd
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
					parser/check_file.c parser/colors.c parser/error_parser.c parser/floodfill.c parser/map_utils.c parser/map_utils_2.c  parser/map.c \
					parser/parser_utils.c parser/parser.c parser/utils.c parser/mtr_util.c

SRCS_BONUS		:=	main_bonus.c \
					move/straight_bonus.c move/turn_bonus.c move/strafe_bonus.c move/move_router_bonus.c move/mouse_bonus.c \
					draw_utils/draw_img_bonus.c draw_utils/draw_pixel_bonus.c draw_utils/draw_walls_bonus.c draw_utils/create_rgb_bonus.c draw_utils/draw_background_bonus.c \
					draw_utils/draw_sprite_bonus.c \
					events/lock_mouse_bonus.c events/input_handler_bonus.c events/player_animation_bonus.c events/dda_bonus.c events/dda_utils_bonus.c  events/door_bonus.c \
					exit_game/exit_request_bonus.c exit_game/free_parser_bonus.c \
					setup_game/setup_bonus.c setup_game/setup_init_direction_bonus.c  setup_game/init_textures_bonus.c setup_game/init_calc_structs.c \
					minimap/draw_minimap_bonus.c \
					parser/check_file_bonus.c parser/colors_bonus.c parser/error_parser_bonus.c parser/floodfill_bonus.c parser/map_utils_bonus.c parser/map_bonus.c \
					parser/parser_utils_bonus.c parser/parser_bonus.c parser/utils_bonus.c parser/mtr_util_bonus.c parser/check_enemy_bonus.c parser/map_utils_2_bonus.c

# CREATE OBJS
OBJS			= ${SRCS:%.c=${OBJSDIR}/%.o}
OBJS_BONUS		= ${SRCS_BONUS:%.c=${OBJSDIR_BONUS}/%.o}

# COLORS
CLR_RMV			:= \033[0m
RED				:= \033[1;31m
GREEN			:= \033[1;32m
YELLOW			:= \033[1;33m
BLUE			:= \033[1;34m
CYAN			:= \033[1;36m


all: external_libs ${NAME}

# MANDATORY
${NAME}:		${OBJS}
				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME} ${CLR_RMV}..."
				${CC} ${OBJS} -L${MLX_DIR} ${LIBFT} ${MLXFLAGS} ${FLAGS} -o ${NAME}
				@echo "${GREEN}${NAME} created[0m 🎮 ✔️"

${OBJS}:		${OBJSDIR}/%.o: ${SRCDIR}/%.c
				@mkdir -p $(@D)
				${CC} ${FLAGS} -I. -O3 -c $< -o $@

# BONUS
bonus: external_libs ${NAME_BONUS}

${NAME_BONUS}:	${OBJS_BONUS}
				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME} ${CLR_RMV}..."
				${CC} ${OBJS_BONUS} -L${MLX_DIR} ${LIBFT} ${MLXFLAGS} ${FLAGS} -o ${NAME_BONUS}
				@echo "${GREEN}${NAME} bonus created[0m 🎮 ✔️"

${OBJS_BONUS}:	${OBJSDIR_BONUS}/%.o: ${SRCDIR_BONUS}/%.c
				@mkdir -p $(@D)
				${CC} ${FLAGS} -I. -O3 -c $< -o $@

external_libs:
				${MAKE} -C ${LIBFT_DIR}
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
