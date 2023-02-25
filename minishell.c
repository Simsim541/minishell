/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:56 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/25 15:53:23 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	check_init(char *line)
{
	
}*/

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**args;
	int		i;

	i = 0;
	(void)ac;
	(void)av;
	line = "| | | ";
	if (!check_quotes(line))
		return (0);
	if (!check_pipes(line))
	{
		ft_putstr_fd(" Syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	if (!check_rediret(line))
	{
		ft_putchar_fd('\n', 2);
		return (0);
	}
	line = expand_env(line, env);
	args = ft_split(line, '|');
	while (args[i])
	{
		printf("args : %s\n", args[i]);
		i++;
	}
	//ft_exec_pipe(args, env);
	return (0);
}