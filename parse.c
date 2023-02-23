/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:59:49 by mberri            #+#    #+#             */
/*   Updated: 2023/02/21 19:07:48 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_white_space(char c)
{
    if(c == ' ' || (c >= 9 && c <= 13))
        return(1);
    return (0);
}

void parse(t_cmd *cmd, char **commands)
{
    int i;
    int j;
    int start;
    t_cmd   *temp;

    i = 0;
    j = 0;
    temp = cmd;
    while (commands[i])
    {
        j = 0;
        start = 0;
        while (commands[i][j])
        {
            while (is_white_space(commands[i][j]))
                j++;
            if (!commands[i][j])
                break;
            start = j;
            while (commands[i][j] && !is_white_space(commands[i][j]))
                    j++;
            cmd->command = ft_substr(commands[i], start, j - start);
            while (commands[i][j] && is_white_space(commands[i][j]))
                j++;
            if (commands[i][j])
                cmd->argumet = ft_substr(commands[i], j, ft_strlen(commands[i]) - j);
            if (commands[i + 1])
            {
                cmd->next = init_cmd();
                cmd = cmd->next;
            }
            j = ft_strlen(commands[i]);
        }
        i++;
    }
    cmd = temp;
}