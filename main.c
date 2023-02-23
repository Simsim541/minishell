/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:56 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/23 20:03:28 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**args;
	int		i;

	i = 0;
	(void)ac;
	(void)av;
	line = "      echosd\"dsds|ghgd\"  |    |  al   ls ";
	if (!check_quotes(line))
		return (0);
	if (!check_pipe_in_begin(line))
		return (0);
	if (!check_pipes(line))
	{
		printf("number of pipes is equal to number of argument\n");
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