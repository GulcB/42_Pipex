/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:24:11 by gbodur            #+#    #+#             */
/*   Updated: 2025/03/01 04:14:42 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	b_close_pipes(t_pipex *ppx)
{
	int	i;

	i = 0;
	while (i < ppx->cmd_count)
	{
		close(ppx->pipe_fd[i][0]);
		close(ppx->pipe_fd[i][1]);
		i++;
	}
}

void	b_free_pipes(t_pipex *ppx)
{
	int	i;

	i = 0;
	if (ppx->pipe_fd)
	{
		while (i < ppx->cmd_count)
		{
			free(ppx->pipe_fd[i]);
			i++;
		}
		free(ppx->pipe_fd);
		ppx->pipe_fd = NULL;
	}
}
