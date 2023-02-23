/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:56 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/21 19:05:17 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*new_mem;

	new_mem = malloc(sizeof(t_cmd));
	new_mem->command = NULL;
	new_mem->option = NULL;
	new_mem->argumet = NULL;
	new_mem->next = NULL;
	return (new_mem);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	int		ret;
	char	**args = NULL;
	t_cmd	*cmd;

	
	int i = 0;
	ret = 0;
	(void)ac;
	(void)av;
	line = "                echo \"hello\" how 'are 'you |    ls       -al | echo welcome";
	if (!check_quotes(line))
		return (0);
	line = expand_env(line, env);
	printf("line: %s\n", line);
	args = ft_split(line, '|');
	cmd = init_cmd();
	parse(cmd, args);
	while (cmd)
	{
		printf("command : %s,    argument: %s\n", cmd->command, cmd->argumet);
			cmd = cmd->next;
	}
	
	while(args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	/*if (args && *args)
		ft_execve(args, env);
	simple_pipe(ft_split("ls", ' '), args, env);*/
	return (0);
}
