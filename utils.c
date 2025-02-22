/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:46:14 by gbodur            #+#    #+#             */
/*   Updated: 2025/02/19 16:45:00 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *ppx)
{
	if (ppx->fd[0] != -1)
	{
		close(ppx->fd[0]);
		ppx->fd[0] = -1;
	}
	if (ppx->fd[1] != -1)
	{
		close(ppx->fd[1]);
		ppx->fd[1] = -1;
	}
}

void	error_msg(char *err_msg, int exit_code)
{
	perror(err_msg);
	exit (exit_code);
}

void	ft_free(char **var)
{
	int	i;

	i = 0;
	if (!var)
		return ;
	while (var[i])
	{
		free(var[i]);
		i++;
	}
	free(var);
	var = NULL;
}

void	free_src(t_pipex *ppx)
{
	if (!ppx)
		return ;
	if (ppx->cmd)
	{
		ft_free(ppx->cmd);
		ppx->cmd = NULL;
	}
	if (ppx->path)
	{
		free(ppx->path);
		ppx->path = NULL;
	}
	if (ppx->full_path)
	{
		ft_free(ppx->full_path);
		ppx->full_path = NULL;
	}
}
