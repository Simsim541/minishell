/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:37:14 by mberri            #+#    #+#             */
/*   Updated: 2023/02/23 20:05:37 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	check_pipe_in_begin(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (is_white_space(line[i]))
			i++;
		if (line[i] == '|')
		{
			ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
			return (0);
		}
		return (1);
	}
	return (0);
}

void	quotes_counter(char c, int *db, int *s)
{
	if (c == '"')
		*db++;
	if (c == '\'')
		*s++;
}

int check_pipes(char *line)
{
	int	i;
	int	count;
	int	pipe;
	int	word;
    int db;
    int s;

	i = 1;
	word = 0;
	count = 0;
	pipe = 0;
    db = 0;
    s = 0;
	while (line[i])
	{
		while (!is_white_space(line[i]) && line[i] != '|'
			|| line[i] != '"' || line[i] != '\'')
			i++;
		if (i > count)
		{
			count = i;
			word++;
		}
		while (is_white_space(line[i]))
            i++;
        if (line[i] == '"' || line[i] == '\'')
        {
            quotes_counter(line[i], &db, &s);
            i++;
        }
		if (line[i] == '|' && (!(db % 2) || !(s % 2)))
		{
			pipe++;
			i++;
		}
        else if (line[i] == '|' && (db % 2) )
		while (is_white_space(line[i]))
			i++;
	}
	if (word <= pipe)
		return (0);
	return (1);
}
