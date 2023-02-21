/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:16:40 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/21 13:57:32 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	one_cmd(char *cmd, t_list *env)
{
	char	**args;
	int		ret;

	args = ft_split(cmd, ' ');
	if (args == NULL)
		return (1);
	ret = execute(args, env);
	free_array(args);
	return (ret);
}
