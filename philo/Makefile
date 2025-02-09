# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 15:55:27 by lmeubrin          #+#    #+#              #
#    Updated: 2025/02/09 16:21:05 by lmeubrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash
MAKEFLAGS += --warn-undefined-variables
.ONESHELL:


OBJ_DIR := obj
SRC_DIR := srcs
HDRS_DIR := include

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
TSAN_FLAGS := -fsanitize=thread
SANITIZE_FLAGS := $(ASAN_FLAGS) $(UBSAN_FLAGS)

SRCS := $(addprefix $(SRC_DIR)/, \
	main.c \
	init.c \
	destroy.c \
	utils.c \
	philos.c \
	routines.c \
	)

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HDRS := $(HDRS_DIR)/philo.h

#PRETTY
BOLD := $(shell printf '\033[1m')
RESET := $(shell printf '\033[0m')
RED := $(shell printf '\033[31;2m')
GREEN := $(shell printf '\033[32m')
YELLOW := $(shell printf '\033[33m')
CLEAR_LINE := $(shell printf '\033[2K')
CURSOR_UP := $(shell printf '\033[1A')

# Additional pretty printing variables
TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE := 0
PROGRESS_BAR_WIDTH := 40

define update_progress
    @printf "$(CLEAR_LINE)"
    @printf "\r$(YELLOW)Compiling: $(RESET)["
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
    @$(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
    @$(eval FILLED=$(shell echo $$(($(PERCENTAGE) * $(PROGRESS_BAR_WIDTH) / 100))))
    @$(eval EMPTY=$(shell echo $$(($(PROGRESS_BAR_WIDTH) - $(FILLED)))))
    @printf "%*s" ${FILLED} "" | tr ' ' '='
    @printf "%*s" ${EMPTY} "" | tr ' ' ' '
    @printf "] %3d%% %s" $(PERCENTAGE) "$<"
endef

.PHONY: all, clean, fclean, re, sanitize, asan, ubsan, leak, tsan

all: $(NAME)

run: all
	./$(NAME)
	
# Main program
$(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
	@printf "\n$(BOLD)Linking $(NAME)$(RESET)\n"
	$(CC) $(FINAL_CFLAGS) $(OBJS) $(FINAL_LDFLAGS) -o $@
	printf "\n$(GREEN)$(BOLD)Build successful!$(RESET)\n" || \
	printf "$(RED)$(BOLD)Build failed!$(RESET)\n"

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(call update_progress)
	@$(CC) $(FINAL_CFLAGS) $(INCLUDES) -c $< -o $@

# Create obj directory
$(OBJ_DIR):
	@mkdir -p $@

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

tsan: FINAL_CFLAGS = $(CFLAGS) $(TSAN_FLAGS)
tsan: FINAL_LDFLAGS = $(LDFLAGS) $(TSAN_FLAGS)
tsan: fclean $(NAME)

# Combined sanitizer
sanitize: FINAL_CFLAGS = $(CFLAGS) $(SANITIZE_FLAGS)
sanitize: FINAL_LDFLAGS = $(LDFLAGS) $(SANITIZE_FLAGS)
sanitize: fclean $(NAME)

clean:
	@printf "$(BOLD)Cleaning object files...$(RESET)\n"
	@rm -dRf $(OBJ_DIR)
	@printf "objs removed\n"

fclean: clean
	@printf "$(BOLD)Cleaning executables...$(RESET)\n"
	rm -f $(NAME)
	@echo "executable removed"

re: fclean all
