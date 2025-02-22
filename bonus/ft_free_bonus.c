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
	while (ppx->cmd && ppx->cmd[i])
		free(ppx->cmd[i++]);
	free(ppx->cmd);
	i = 0;
	if (ppx->cmd_path)
		free(ppx->cmd_path);
	if (ppx->full_path)
		free(ppx->full_path);
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
	del = NULL;
}
