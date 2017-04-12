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

NAMENM = ft_nm
NAMEOT = ft_otool
# LIBFT
LFTPATH = libft/
LFTIPATH = -I $(LFTPATH)
LFT = -L $(LFTPATH) -lft


OBJPATHNM = obj_nm
SRCPATHNM = src_nm

OBJPATHOT = obj_ot
SRCPATHOT = src_ot

INCLUDE = -I ./includes/


CC = clang


LIBS = $(LFT)
INCLUDES = $(INCLUDE) $(LFTIPATH) 


BASEFLAGS = -Wall -Wextra
CFLAGS = $(BASEFLAGS) -Werror -O2 -g 


LFTCALL = all
LFTRE = re

SRCSFILESNM  =	main.c \
				nm_64.c \
				nm_32.c \
				nm_lib.c \
				utils.c \
				utils2.c \
				utils3.c \
				bin.c \
				seg_sect.c \
				seg_sect32.c \
				manage_list.c \
				print_list.c 

SRCSFILESOT  =	main.c \
				common_otool.c \
				handle_otool_fat.c \
				handle_otool_lib.c \
				handle_otool_32_64.c


SRCNM = $(addprefix $(SRCPATHNM)/,$(SRCSFILESNM))
OBJECTSNM = $(SRCNM:$(SRCPATHNM)/%.c=$(OBJPATHNM)/%.o)

SRCOT = $(addprefix $(SRCPATHOT)/,$(SRCSFILESOT))
OBJECTSOT = $(SRCOT:$(SRCPATHOT)/%.c=$(OBJPATHOT)/%.o)

RM = rm -rf

Y = \033[0;33m
R = \033[0;31m
G = \033[0;32m
E = \033[39m

all: l $(NAMENM) $(NAMEOT)

$(NAMENM): $(OBJECTSNM) 
	@echo "$(Y)[COMPILING NM] $(G) $(CC) -o $@ $(CFLAGS) objs.o $(LIBS) $(E)"
	@$(CC)  -o $@ $(CFLAGS) -g $(OBJECTSNM) $(INCLUDES) $(LIBS)
	@echo "$(Y)[COMPILING NM DONE]$(E)"

$(OBJECTSNM): $(OBJPATHNM)/%.o : $(SRCPATHNM)/%.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<

$(NAMEOT): $(OBJECTSOT) 
	@echo "$(Y)[COMPILING OT] $(G) $(CC) -o $@ $(CFLAGS) objs.o $(LIBS) $(E)"
	@$(CC)  -o $@ $(CFLAGS) -g $(OBJECTSOT) $(INCLUDES) $(LIBS)
	@echo "$(Y)[COMPILING OT DONE]$(E)"

$(OBJECTSOT): $(OBJPATHOT)/%.o : $(SRCPATHOT)/%.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<

clean:
	$(RM) $(OBJPATHNM)
	$(RM) $(OBJPATHOT)

fclean: clean
	$(RM) $(NAMENM)
	$(RM) $(NAMEOT)

l:
	@echo "$(Y)[COMPILING LIBFT] $(G) make -C $(LFTPATH) $(LFTCALL) $(E)"
	@make -C $(LFTPATH) $(LFTCALL)
	@echo "$(Y)[COMPILING LIBFT DONE]$(E)"

re: fclean all
