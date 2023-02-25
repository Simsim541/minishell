/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:37:14 by mberri            #+#    #+#             */
/*   Updated: 2023/02/24 15:46:07 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//condition in check_pipes function forget why i use it
/*else if (line[i] == '|' && j > 0 && (!(db % 2) || !(s % 2))
			&& line[i + 1] == '\0')
			command++;*/

static int	check_pipe_in_begin(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (is_white_space(line[i]))
			i++;
		if (line[i] == '|')
			return (0);
		return (1);
	}
	return (0);
}

static void	quotes_counter(char c, int *db, int *s)
{
	if (c == '"')
		db++;
	if (c == '\'')
		s++;
}

int	number_of_pipes(char *line)
{
	int	i;
	int	db;
	int	s;
	int	pipe;

	pipe = 0;
	i = 0;
	db = 0;
	s = 0;
	while (line[i])
	{
		if (line[i] == '|' && (!(db % 2) && !(s % 2)))
			pipe++;
		quotes_counter(line[i], &db, &s);
		i++;
	}
	return (pipe);
}

int	check_pipes(char *line)
{
	int	i;
	int	command;
	int	db;
	int	s;
	int	j;

	init_var(&command, &db, &s, &j);
	i = -1;
	while (line[++i] && check_pipe_in_begin(line))
	{
		quotes_counter(line[i], &db, &s);
		while (!(is_white_space(line[i])) && line[i] != '|')
			j = i++;
		if (line[i] == '|' && j > 0 && (!(db % 2) || !(s % 2)))
		{
			command++;
			j = 0;
		}
		else if (line[i + 1] == '\0' && j > 0 && (!(db % 2) || !(s % 2)))
			command++;
	}
	if (command <= number_of_pipes(line))
		return (0);
	return (1);
}