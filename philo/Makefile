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
NAME := philo
INCLUDES := -I$(HDRS_DIR)

#flags
CFLAGS := -Werror -Wall -Wextra -g
LDFLAGS :=

FINAL_CFLAGS = $(CFLAGS)
FINAL_LDFLAGS = $(LDFLAGS)

# Different sanitizer configurations
ASAN_FLAGS := -fsanitize=address
UBSAN_FLAGS := -fsanitize=undefined
LEAK_FLAGS := -fsanitize=leak

# # fsanitize
# SANITIZE_NAME := $(NAME)_sanitize
# SANITIZE_FLAGS := -fsanitize=address,undefined

OBJ_DIR := obj
SRC_DIR := srcs
HDRS_DIR := include

SRCS := $(addprefix $(SRC_DIR)/, \
	main.c \
	ft_strtoui.c \
	)

HDRS := $(HDRS_DIR)/philo.h

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#PRETTY
BOLD := $(shell printf '\033[1m')
RESET := $(shell printf '\033[0m')
RED := $(shell printf '\033[31;2m')
GREEN := $(shell printf '\033[32m')
YELLOW := $(shell printf '\033[33m')
CLEAR_LINE := $(shell printf '\033[2K')
CURSOR_UP := $(shell printf '\033[1A')

.PHONY: all, clean, fclean, re

all: $(NAME)

run: all
	./$(NAME)
	
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@printf "\n$(BOLD)Linking $(NAME)$(RESET)\n"
	$(CC) $(OBJS) $(FINAL_LDFLAGS) -o $@
	@printf "\n$(GREEN)$(BOLD)Build successful!$(RESET)\n" || \
	@printf "$(RED)$(BOLD)Build failed!$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS) | $(OBJ_DIR)
	@printf "$(BOLD)Compiling $(NAME)$(RESET)\n"
	$(CC) $(FINAL_CFLAGS) $(INCLUDES) -c $< -o $@

# Targets for different sanitizer builds
asan: FINAL_CFLAGS = $(CFLAGS) $(ASAN_FLAGS)
asan: FINAL_LDFLAGS = $(LDFLAGS) $(ASAN_FLAGS)
asan: fclean $(NAME)

ubsan: FINAL_CFLAGS = $(CFLAGS) $(UBSAN_FLAGS)
ubsan: FINAL_LDFLAGS = $(LDFLAGS) $(UBSAN_FLAGS)
ubsan: fclean $(NAME)

leak: FINAL_CFLAGS = $(CFLAGS) $(LEAK_FLAGS)
leak: FINAL_LDFLAGS = $(LDFLAGS) $(LEAK_FLAGS)
leak: fclean $(NAME)

# Combined sanitizer (your original sanitize target)
sanitize: FINAL_CFLAGS = $(CFLAGS) $(SANITIZE_FLAGS)
sanitize: FINAL_LDFLAGS = $(LDFLAGS) $(SANITIZE_FLAGS)
sanitize: fclean $(NAME)

clean:
	@rm -dRf $(OBJ_DIR)
	@echo "objs removed"

fclean: clean
	rm -f $(NAME)
	@echo "executable removed"

re: fclean all
