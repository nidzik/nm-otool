#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nidzik <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/11 10:34:54 by nidzik            #+#    #+#              #
#    Updated: 2017/02/27 19:17:22 by nidzik           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_nm

# LIBFT
LFTPATH = libft/
LFTIPATH = -I $(LFTPATH)
LFT = -L $(LFTPATH) -lft


OBJPATH = obj
SRCPATH = .
INCLUDE = -I ./


CC = clang


LIBS = $(LFT)
INCLUDES = $(INCLUDE) $(LFTIPATH) 


BASEFLAGS = -Wall -Wextra
CFLAGS = $(BASEFLAGS) -Werror -O2 -g 


LFTCALL = all
LFTRE = re

SRCSFILES = main.c \
			nm_64.c \
			nm_32.c \
			nm_lib.c \
			utils.c \
			utils2.c \
			seg_sect.c \
			seg_sect32.c \
			manage_list.c \
			manage_list_res.c \
			bin.c

SRC = $(addprefix $(SRCPATH)/,$(SRCSFILES))
OBJECTS = $(SRC:$(SRCPATH)/%.c=$(OBJPATH)/%.o)

RM = rm -rf

Y = \033[0;33m
R = \033[0;31m
G = \033[0;32m
E = \033[39m

all: l $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(Y)[COMPILING NM] $(G) $(CC) -o $@ $(CFLAGS) objs.o $(LIBS) $(E)"
	@$(CC)  -o $@ $(CFLAGS) -g $(OBJECTS) $(INCLUDES) $(LIBS)
	@echo "$(Y)[COMPILING NM DONE]$(E)"

$(OBJECTS): $(OBJPATH)/%.o : $(SRCPATH)/%.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<

clean:
	$(RM) $(OBJPATH)

fclean: clean
	$(RM) $(NAME)

l:
	@echo "$(Y)[COMPILING LIBFT] $(G) make -C $(LFTPATH) $(LFTCALL) $(E)"
	@make -C $(LFTPATH) $(LFTCALL)
	@echo "$(Y)[COMPILING LIBFT DONE]$(E)"

re: fclean all
