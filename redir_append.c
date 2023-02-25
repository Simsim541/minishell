/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:40:30 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/24 19:45:26 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_two_var(int *db, int *s)
{
	*db = 0;
	*s = 0;
}

//check if there is a file name after the << symbol
static void	counter_quotes(char c, int *db, int *s)
{
	if (c == '"')
		db++;
	if (c =='\'')
		s++;
}

int	check_append_in(char *str)
{
	int	i;
	int	db;
	int	s;

	i = -1;
	init_two_var(&db, &s);
	while (str[++i] != '\0')
	{
		counter_quotes(str[i], &db, &s);		
		if ((str[i] == '<' && str[i + 1] == '<') && (str[i + 2] != '<'
				|| str[i + 2] != '>') && (!(db % 2) && !(s % 2)))
		{
			i += 2;
			while (str[i] == ' ')
				i++;
			if (str[i] == '\0')
				return (i);
			if (str[i - 1] == ' '
				&& (str[i] == '\0' || str[i] == '<' || str[i] == '>'
					|| str[i] == '|' || str[i] == ';' || str[i] == '&'
					|| str[i] == '\t' || str[i] == '\n'))
				return (i);
		}
	}
	return (0);
}

// check if there is a file name after the >> symbol

int	check_append_out(char *str)
{
	int	i;
	int	db;
	int	s;

	i = -1;
	init_two_var(&db, &s);
	while (str[++i] != '\0')
	{
		counter_quotes(str[i], &db, &s);
		if ((str[i] == '>' && str[i + 1] == '>') && (str[i + 2] != '>'
				|| str[i + 2] != '<') && (!(db % 2) && !(s % 2)))
		{
			i += 2;
			while (str[i] == ' ')
				i++;
			if (str[i] == '\0')
				return (i);
			if (str[i - 1] == ' '
				&& (str[i] == '\0' || str[i] == '<' || str[i] == '>'
					|| str[i] == '|' || str[i] == ';' || str[i] == '&'
					|| str[i] == '\t' || str[i] == '\n'))
				return (i);
		}
	}
	return (0);
}

// check in and out append redirections

void	check_append_in_out(char *str)
{
	int	check;

	check = 0;
	if (check_append_in(str) != 0)
		check = check_append_in(str);
	if (check_append_out(str) != 0)
		check = check_append_out(str);
	if (check != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (str[check] == '\0' || str[check] == ' ')
			ft_putstr_fd("newline'", 2);
		else
		{
			ft_putstr_fd(&str[check], 2);
			ft_putstr_fd("'", 2);
		}
		ft_putstr_fd("\n", 2);
	}
	else
		printf("OK\n");
}
