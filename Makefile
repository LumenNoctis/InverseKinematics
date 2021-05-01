NAME = IK

FLAGS =
INCLUDES = -I includes/ -I includes/includes/SDL2/  -I includes/MT  -I includes/SDLX/

LIB_DIR = libs/
LIBRARIES = $(LIB_DIR)libSDL2.dylib $(LIB_DIR)libSDL2_ttf.dylib $(LIB_DIR)libSDL2_image.dylib
STATIC_LIB = -L -l $(LIB_DIR)libMT.a 

SDLX_DIR = SDLX/
MT_DIR = MT/
SRCS_DIR = srcs/
BIN_DIR = bin/

MT_SRCS =				\
	MT_matrix			\
	MT_v2				\
	MT_v3				\
	MT					\

SDLX_SRCS =				\
	SDLX_anim			\
	SDLX_init			\
	SDLX_input			\
	SDLX_render			\
	SDLX				\

SRCS_NAMES =			\
	debug				\
	ik					\
	main				\
	utils				\

C_FILES =				\
	$(addprefix $(SDLX_DIR), $(SDLX_SRCS))	\
	$(addprefix $(MT_DIR), $(MT_SRCS))		\
	$(SRCS_NAMES) 		\

SRCS = $(addsuffix .c, $(addprefix $(SRCS_DIR), $(C_FILES)))
OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(BIN_DIR) $(OBJS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) libs/libSDL2-2.0.so libs/libSDL2_ttf-2.0.so -lm

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)%.o: %.c
	mkdir -p $(BIN_DIR)$(dir $<)
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

run: re clean
	./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all