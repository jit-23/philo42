NAME:= philo
CFLAGS:= -Wall -Werror -Wextra -fsanitize=thread

RED:=\033[0;31m
GREEN:= \033[0;32m
BLUE=\033[0;34m
default_colour=\033[0m

SRC_FILES:=  main.c \
				check_args.c \
				dinner.c \
				init_table.c \
				time_utils.c \
				utils.c \
				utils2.c \
				actions.c\


OBJ_FILES:= $(patsubst %.c, %.o, $(SRC_FILES))

SRC_PATH:= src/
OBJ_PATH:= obj/

SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

all: ${NAME}

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
		@mkdir -p ${OBJ_PATH}
		cc ${CFLAGS} -c $< -o $@ 

${NAME}: ${OBJ}
		cc ${CFLAGS}  -g ${OBJ} -o ${NAME}
		@echo "${GREEN}executable file: ./philo${default_colour}\n"

clean:
		@rm -fr ${OBJ_PATH}
		@echo "${RED}object files and directory deleted:${default_colour}"

fclean: clean
		@rm -f ${NAME}
		@echo "${RED}executable deleted:$(default_colour)"
		@echo "${RED}deleted all:$(default_colour)\n"

re : fclean all

.PHONY: all re clean fclean normi
.SIELNT:
          
