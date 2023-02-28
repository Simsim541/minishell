/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:37:14 by mberri            #+#    #+#             */
/*   Updated: 2023/02/27 17:32:30 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//condition in check_pipes function forget why i use it
/*else if (line[i] == '|' && j > 0 && (!(db % 2) || !(s % 2))
			&& line[i + 1] == '\0')
			command++;*/

static void	init_variable(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

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

int	check_command(char *str)
{
	int	i;
	int	y;
	int	x;

	init_variable(&x, &y, &i);
	while (str[i] && str[i] != '|')
	{
		while (is_white_space(str[i]))
			i++;
		while (str[i] == '!' || str[i] == ')' || str[i] == '('
			|| str[i] == '[' || str[i] == ']'
			|| str[i] == '?' || str[i] == '`')
		{
			y++;
			i++;
		}
		while (str[i] == '>' || str[i] == '<' || str[i] == '&')
			x = i++;
		if (y == 1 && !x)
			return (1);
		else if (x && !y)
			return (1);
	}
	return (0);
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
