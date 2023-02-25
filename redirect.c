/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:51:57 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/25 15:38:35 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*else if (line[i] == '<')
{
	while (line[i] == '<' && stop--)
		ft_putchar_fd(line[i++], 2);
	return (0);
}*/

static void	counter_quotes(char c, int *db, int *s)
{
	if (c == '"')
		db++;
	if (c == '\'')
		s++;
}

static int	check_deplicate_of_redirection(char *line)
{
	int	i;
	int	redirection;
	int	stop;
	int y;

	stop = 0;
	i = -1;
	while (line[++i])
	{
		redirection = 0;
		while (line[i] == '>' || line[i] == '<')
		{
			redirection++;
			i++;
		}
		if (redirection > 2)
		{
			i -= redirection - 2;
			ft_putstr_fd("syntax error near unexpected token `", 2);
			if (line[i] == '>' || line[i] == '<')
			{
				y = i;
				while (stop-- && line[i] == line [y])
					ft_putchar_fd(line[i++], 2);
				ft_putchar_fd('\'', 2);
				return (0);
			}
		}
	}
	return (1);
}

// check if there is a file name after the < symbol
int	check_int(char *str)
{
	int	i;
	int	db;
	int	s;

	i = -1;
	db = 0;
	s = 0;
	while (str[++i] != '\0')
	{
		counter_quotes(str[i], &db, &s);
		if (str[i] == '<' && (!(db % 2) && !(s % 2)))
		{
			i++;
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

// check if there is a file name after the > symbol

int	check_out(char *str)
{
	int	i;
	int	db;
	int	s;

	i = -1;
	db = 0;
	s = 0;
	while (str[++i] != '\0')
	{
		counter_quotes(str[i], &db, &s);
		if (str[i] == '>' && (!(db % 2) && !(s % 2)))
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
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

// check in out

void	check_in_out(char *str)
{
	int	check;

	check = 0;
	if (check_int(str) != 0)
		check = check_int(str);
	else if (check_out(str) != 0)
		check = check_out(str);
	if (check != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		if (str[check] == ' ' || str[check] == '\0')
			ft_putstr_fd("`newline'", 2);
		else
		{
			ft_putchar_fd('`', 2);
			ft_putstr_fd(&str[check], 2);
			ft_putchar_fd('\'', 2);
		}	
		ft_putchar_fd('\n', 2);
	}
}

int	check_rediret(char	*line)
{
	int	i;

	i = 0;
	if (!check_deplicate_of_redirection(line))
		return (0);
	/*while (line[i])
	{
		if ((line[i] == '>' || (line[i] == '<')))
		{
			check_in_out(line);
			break ;
		}
		else if ((line[i] == '>' && line[i + 1] == '>')
			|| (line[i] == '<' && line[i + 1] == '<'))
		{
			check_append_in_out(line);
			break ;
		}
			i++;
	}*/
	return (1);
}
