/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:25:26 by gbodur            #+#    #+#             */
/*   Updated: 2025/02/22 13:43:18 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_cmd_path(t_pipex *ppx, char **envp)
{
	char	*b_dir;
	char	*b_full_cmd;
	int		i;

	if (ppx->cmd[0][0] == '/' && access(ppx->cmd[0], F_OK | X_OK) == 0)
		return (ft_strdup(ppx->cmd[0]));
	while (envp && *envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!envp || !*envp)
		return (NULL);
	ppx->full_path = ft_split (*envp + 5, ':');
	i = -1;
	while (ppx->full_path && ppx->full_path[++i])
	{
		b_dir = ft_strjoin(ppx->full_path[i], "/");
		if (!b_dir)
			return (NULL);
		b_full_cmd = ft_strjoin(b_dir, ppx->cmd[0]);
		free(b_dir);
		if (access(b_full_cmd, F_OK | X_OK) == 0)
			return (b_full_cmd);
		free(b_full_cmd);
	}
	return (ft_free(ppx->full_path), NULL);
}

void	process_heredoc(t_pipex *ppx, char **av)
{
	char	*line;
	size_t	delimiter_len;

	delimiter_len = 0;
	if (pipe(ppx->heredoc_fd) == -1)
		b_error_msg(ERR_PIPE, 1);
	while (1)
	{
		write(1, "heredoc>", 10);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strlen(line) == delimiter_len + 1 && 
            line[delimiter_len] == '\n' &&
            !ft_strncmp(line, av[2], delimiter_len))
		{
			free(line);
			break ;
		}
		write(ppx->heredoc_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(ppx->heredoc_fd[1]);
	dup2(ppx->heredoc_fd[0], 0);
	close(ppx->heredoc_fd[0]);
}

void	child_dup(t_pipex *ppx, int i)
{
	if (i == 0 && ppx->heredoc_mode == 0)
	{
		if (dup2(ppx->fd0, 0) == -1)
			b_error_msg(ERR_DUP, 1);
	}
	else if (i == 0 && ppx->heredoc_mode == 1)
	{
		if (dup2(ppx->pipe_fd[0], 0) == -1)
			b_error_msg(ERR_DUP, 1);
	}
	if (i == ppx->cmd_count - 1)
	{
		if (dup2(ppx->fd1, 1) == -1)
			b_error_msg(ERR_DUP, 1);
	}
	else
	{
		if (dup2(ppx->pipe_fd[1], 0) == -1)
			b_error_msg(ERR_DUP, 1);
	}
}
