# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 15:48:13 by yokamura          #+#    #+#              #
#    Updated: 2023/06/13 16:20:52 by ykusano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
OBJ_DIR		:=	obj
SRC_DIR		:=	src

CC			:=	cc
CFLAGS		:=	-I $(shell brew --prefix readline)/include -Wall -Werror -Wextra
MFLAGS		:=	-Wall -Werror -Wextra -L$(shell brew --prefix readline)/lib -lreadline
HEADERS		:=  includes

SRCS_NAME	:=	main.c \
				free/last_free.c \
				tokenizer/lst_node_token.c tokenizer/tokenizer.c \
				tokenizer/delete_node.c tokenizer/path_expansion.c tokenizer/type_classify.c \
				tokenizer/word_join.c tokenizer/error_tokenize.c tokenizer/space_split.c \
				tokenizer/space_split_utils.c tokenizer/token_free.c tokenizer/expand_line.c \
				tokenizer/path_expansion2.c tokenizer/set_under_env.c tokenizer/expand_line2.c \
				envp_lst/envlst_create.c envp_lst/envlst_add.c envp_lst/envlst_new.c \
				envp_lst/envnode_new.c envp_lst/envlst_free.c envp_lst/cumbersome_env.c \
				envp_lst/cumbersome_env2.c \
				conf_in_out/conf_normal/heredoc.c conf_in_out/conf_normal/conf_in_out.c \
				conf_in_out/conf_normal/decide_out.c conf_in_out/conf_normal/decide_in.c \
				conf_in_out/conf_pipe/conf_in_out_pipe.c conf_in_out/conf_pipe/decide_in_except_heredoc.c \
				conf_in_out/conf_pipe/decide_in_pipe.c conf_in_out/conf_pipe/heredoc_except_last_p.c \
				conf_in_out/conf_pipe/heredoc_pipe.c conf_in_out/conf_pipe/heredoc_pipe_conf.c \
				conf_in_out/conf_pipe/is_heredoc.c conf_in_out/conf_pipe/just_files_pipe.c \
				conf_in_out/conf_normal/heredoc_expand.c \
				make_cmds_files_lst/make_new_lst.c make_cmds_files_lst/make_cmds_exec.c \
				make_cmds_files_lst/make_files.c make_cmds_files_lst/make_nodes.c \
				make_cmds_files_lst/free_cmds_files.c \
				builtin/echo.c builtin/cd.c builtin/pwd.c builtin/export.c builtin/env.c \
				builtin/unset.c builtin/unset_utils.c builtin/exit.c builtin/is_builtin.c builtin/export_utils.c \
				exec/just_files.c exec/exec_avec_pipe.c exec/child_process.c exec/parent_process.c \
				exec/exec_main.c exec/exec_sans_pipe.c exec/search_path.c \
				minishell_utils/ft_bzero.c minishell_utils/ft_strdup.c minishell_utils/ft_strchr.c \
				minishell_utils/ft_strlcpy.c minishell_utils/ft_strlcat.c minishell_utils/ft_strlen.c \
				minishell_utils/ft_strncpy.c minishell_utils/ft_strcmp.c minishell_utils/ft_isalnum.c \
				minishell_utils/ft_memcpy.c minishell_utils/ft_cmd_count.c minishell_utils/ft_atol.c \
				minishell_utils/ft_strndup.c minishell_utils/ft_strncmp.c minishell_utils/ft_ltoa.c \
				minishell_utils/ft_putstr_fd.c minishell_utils/error_write.c minishell_utils/ft_getenv.c \
				minishell_utils/vers_strlen.c \
				signal/signal.c signal/signal_heredoc.c \
				envp_strs/envp_create.c envp_strs/envp_no.c \
				check_utils/check_line.c \

SRCS	:= $(addprefix $(SRC_DIR)/, $(SRCS_NAME))
OBJECTS	:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME):	$(OBJECTS)
	$(CC) $(MFLAGS) -I $(HEADERS) -o $(NAME) $(OBJECTS)
	echo > ~/.inputrc set echo-control-characters off

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
