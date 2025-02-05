# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 15:55:27 by lmeubrin          #+#    #+#              #
#    Updated: 2025/02/05 14:41:31 by lmeubrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash
MAKEFLAGS += --warn-undefined-variables
.ONESHELL:

CC := cc
CFLAGS = -Werror -Wall -Wextra -g
INCLUDES := -I$(HDRS_DIR)
NAME := philo

# fsanitize
SANITIZE_NAME := $(NAME)_sanitize
SANITIZE_FLAGS := -fsanitize=address,undefined

OBJ_DIR := obj
SRC_DIR := src
HDRS_DIR := include

SRCS := $(addprefix $(SRC_DIR)/, \
		main.c \
		ft_strtoui.c \
		)

HDRS := $(addprefix $(HDRS_DIR)/, \
		philo.h \
		)

OBJS := $(/SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)

#PRETTY
BOLD := \033[1m
RESET := \033[0m
RED := \033[31;2m
GREEN := \033[32m
YELLOW := \033[33m

.PHONY: all, clean, fclean, re

all: $(NAME)

run: all
	./$(NAME)
	
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@echo -e "$(BOLD)Linking $(NAME)$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo -e "$(BOLD)$(YELLOW)$(NAME)$(RESET) successfully compiled."

$(OBJ_DIR)/%.o: %.c $(HDRS)
	mkdir -p $(OBJ_DIR)
	@echo -e "$(BOLD)Compiling $(NAME)$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -dRf $(OBJ_DIR)
	@echo "objs removed"

fclean: clean
	rm -f $(NAME)
	@echo "executable removed"

re: fclean all

sanitize: CFLAGS += $(SANITIZE_FLAGS)
sanitize: LDFLAGS += $(SANITIZE_FLAGS)

sanitize: CFLAGS += $(SANITIZE_FLAGS)
sanitize: re
