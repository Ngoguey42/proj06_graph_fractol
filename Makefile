#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/04 11:28:17 by ngoguey           #+#    #+#              #
#    Updated: 2014/12/25 11:38:33 by ngoguey          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol

# LIBFT
LFTPATH = libft/
LFTIPATH = -I $(LFTPATH)includes/
LFT = -L $(LFTPATH) -lft

OBJPATH = obj
SRCPATH = .
INCLUDE = -I ./

# MULTI THREAD
THREADFLAGS = -D NUMTHREAD=8
DRAWFILES = draw_screen_async.c

## SINGLE THREAD
# THREADFLAGS = 
# DRAWFILES = draw_screen_sync.c


# MLX
CC = gcc
GRAPHLIB = -L/usr/X11/lib -lmlx -lXext -lX11
GRAPHINC =
SPECIALFILES = com_mlx.c pause_mlx.c putpix_mlx.c

## SDL
# CC = /bin/i686-w64-mingw32-gcc.exe
# GRAPHLIB = -L/lib/SDL/ -lmingw32 -lSDLmain -lSDL 
# GRAPHINC = -I /usr/include/
# SPECIALFILES = com_sdl.c putpix_sdl.c pause_sdl.c


LIBS = $(LFT) $(GRAPHLIB)
INCLUDES = $(INCLUDE) $(LFTIPATH) $(GRAPHINC)

BASEFLAGS = -Wall -Wextra
CFLAGS = $(BASEFLAGS) $(THREADFLAGS) -Werror -O2
DEBUGFLAGS = $(BASEFLAGS) $(THREADFLAGS) -g

LFTCALL = all
LFTRE = re
LFTG = g
LFTGRE = gre

SRCSFILES = main.c events.c events_keys.c movements.c $(SPECIALFILES)\
init_env.c themes.c \
$(DRAWFILES)\
draw_row.c draw_screenpart.c fractal_functions.c\
debug.c

SRC = $(addprefix $(SRCPATH)/,$(SRCSFILES))
OBJECTS = $(SRC:$(SRCPATH)/%.c=$(OBJPATH)/%.o)

RM = rm -rf

Y = \033[0;33m
R = \033[0;31m
G = \033[0;32m
E = \033[39m

all: l $(NAME)

$(NAME): $(OBJECTS)
	@echo -e "$(Y)[COMPILING FRACTOL] $(G) $(CC) -o $@ $(CFLAGS) objs.o $(LIBS) $(E)"
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIBS)
	@echo -e "$(Y)[COMPILING FRACTOL DONE]$(E)"

$(OBJECTS): $(OBJPATH)/%.o : $(SRCPATH)/%.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $(LIBS) -c $<

clean:
	$(RM) $(OBJPATH)

fclean: clean
	$(RM) $(NAME)

l:
	@echo -e "$(Y)[COMPILING LIBFT] $(G) make -C $(LFTPATH) $(LFTCALL) $(E)"
	make -C $(LFTPATH) $(LFTCALL)
	@echo -e "$(Y)[COMPILING LIBFT DONE]$(E)"

g: _g _gft all

# re rules
re: fclean all
rel: _relft l
rea: _relft re

# gre rules
gre: _g re
grel: _greft l
grea: _g _greft re

# eval rules
_g:
	$(eval CFLAGS = $(DEBUGFLAGS))
_relft:
	$(eval LFTCALL = $(LFTRE))
_gft:
	$(eval LFTCALL = $(LFTG))
_greft:
	$(eval LFTCALL = $(LFTGRE))
