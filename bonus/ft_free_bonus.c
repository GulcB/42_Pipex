/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:24:11 by gbodur            #+#    #+#             */
/*   Updated: 2025/02/22 13:34:14 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	b_error_msg(char *err_msg, int exit_code)
{
	perror(err_msg);
	exit (exit_code);
}

void	free_list(t_pipex *ppx)
{
	int	i;

	i = 0;
	if (ppx->cmd_path)
	{
		while (i < ppx->cmd_count * 2 && ppx->cmd_path[i])
		{
			free(ppx->cmd_path[i]);
			i++;
		}
		free(ppx->cmd_path);
		ppx->cmd_path = NULL;
	}
	i = 0;
	if (ppx->cmd)
	{
		while (ppx->cmd[i])
			free(ppx->cmd[i++]);
		free(ppx->cmd);
		ppx->cmd = NULL;
	}
	ft_free_fullpath(ppx);
}

void	ft_free_fullpath(t_pipex *ppx)
{
	int	i;

	i = 0;
	if (ppx->full_path)
	{
		while (ppx->full_path[i])
			free(ppx->full_path[i++]);
		free(ppx->full_path);
		ppx->full_path = NULL;
	}
}

void	ft_free(char **del)
{
	int	i;

	if (!del)
		return ;
	i = 0;
	while (del[i])
	{
		free(del[i]);
		del[i] = NULL;
		i++;
	}
	free(del);
}
