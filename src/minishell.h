/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:17:39 by sham              #+#    #+#             */
/*   Updated: 2021/11/28 13:47:10 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#define MAX_PATH 4096

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

enum e_cmd_type
{
	CMD = 0,
	ARG,
	IN_DISCRIPOTR, // input
	OUT_DISCRIPOTR, // output
	OPTION,
	CMD_TYPE_MAX
};

struct s_cmd
{
	char *cmd;
	char *arg; // **arg
	char *discriptor[2]; // null, 0:input, 1:output
	int option;
}	typedef t_cmd;

struct s_data
{
	void *contents;
	struct s_data *next;
}	typedef t_data;

struct s_list
{
	void *front;
	int size;
}	typedef t_list;

int	add_list(t_list *list, t_data *new_data);
int *add_cmd_list(t_list *list, t_cmd *new_cmd);
int free_cmd_list (t_list *list);
void print_cmd_list(t_list *list);

#endif
