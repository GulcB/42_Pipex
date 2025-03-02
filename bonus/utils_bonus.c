/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:25:26 by gbodur            #+#    #+#             */
/*   Updated: 2025/03/03 01:03:06 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	b_error_msg(char *err_msg, int exit_code)
{
	perror(err_msg);
	exit (exit_code);
}

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
			return (ft_free(ppx->full_path), ppx->full_path = NULL, NULL);
		b_full_cmd = ft_strjoin(b_dir, ppx->cmd[0]);
		free(b_dir);
		if (access(b_full_cmd, F_OK | X_OK) == 0)
			return (ft_free(ppx->full_path), ppx->full_path = NULL, b_full_cmd);
		free(b_full_cmd);
	}
	return (ft_free(ppx->full_path), ppx->full_path = NULL, NULL);
}

void	b_setup_cmd_exec(t_pipex *ppx, char **av, char **env, int cmd_i)
{
	ppx->cmd_path[cmd_i] = find_cmd_path(ppx, env);
	if (!ppx->cmd_path[cmd_i])
	{
		ft_putstr_fd(av[cmd_i + 2 + ppx->heredoc_mode], 2);
		b_error_msg(ERR_CMD, 127);
	}
	if (cmd_i == ppx->cmd_count - 1)
	{
		if (dup2(ppx->fd1, 1) == -1)
			b_error_msg(ERR_DUP, 1);
		close(ppx->fd1);
	}
	if (execve(ppx->cmd_path[cmd_i], ppx->cmd, env) == -1)
	{
		free_list(ppx);
		b_error_msg(ERR_EXEC, 126);
	}
}

void	process_heredoc(t_pipex *ppx, char **av)
{
	char	*line;

	if (pipe(ppx->heredoc_fd) == -1)
		b_error_msg(ERR_PIPE, 1);
	while (1)
	{
		write(1, "heredoc>", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, av[2], ft_strlen(av[2])))
		{
			free(line);
			break ;
		}
		write(ppx->heredoc_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(ppx->heredoc_fd[1]);
	if (dup2(ppx->heredoc_fd[0], 0) == -1)
		b_error_msg(ERR_DUP, 1);
	close(ppx->heredoc_fd[0]);
}

void	setup_files(t_pipex *ppx, char **av, int ac)
{
	if (ppx->heredoc_mode)
	{
		ppx->fd1 = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (ppx->fd1 < 0)
			b_error_msg(ERR_OUTFILE, 1);
		process_heredoc(ppx, av);
	}
	else
	{
		ppx->fd0 = open(av[1], O_RDONLY);
		if (ppx->fd0 < 0)
			b_error_msg(ERR_INFILE, 1);
		ppx->fd1 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (ppx->fd1 < 0)
			b_error_msg(ERR_OUTFILE, 1);
		if (dup2(ppx->fd0, 0) == -1)
			b_error_msg(ERR_DUP, 1);
		close(ppx->fd0);
	}
}
