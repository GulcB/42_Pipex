/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:33:17 by gbodur            #+#    #+#             */
/*   Updated: 2025/02/19 16:45:39 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_pipex(t_pipex *ppx, char **av, char **envp)
{
	ppx->pid1 = fork();
	if (ppx->pid1 < 0)
	{
		close_pipes(ppx);
		error_msg(ERR_FORK, 1);
	}
	else if (ppx->pid1 == 0)
		child_process(ppx, av, envp);
	else
	{
		ppx->pid2 = fork();
		if (ppx->pid2 < 0)
		{
			close_pipes(ppx);
			error_msg(ERR_FORK, 1);
		}
		else if (ppx->pid2 == 0)
			parent_process(ppx, av, envp);
		else
		{
			close_pipes(ppx);
			waitpid(ppx->pid1, NULL, 0);
			waitpid(ppx->pid2, NULL, 0);
		}
	}
}

char	*get_cmd_path(t_pipex *ppx, char **envp)
{
	int		i;
	char	*dir;
	char	*cmd_path;

	if (ppx->cmd[0][0] == '/' && access(ppx->cmd[0], F_OK | X_OK) == 0)
		return (ft_strdup(ppx->cmd[0]));
	while (envp && *envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!envp || !*envp)
		return (NULL);
	ppx->full_path = ft_split (*envp + 5, ':');
	if (!ppx->full_path)
		return (NULL);
	i = -1;
	while (ppx->full_path && ppx->full_path[++i])
	{
		dir = ft_strjoin(ppx->full_path[i], "/");
		cmd_path = ft_strjoin(dir, ppx->cmd[0]);
		free(dir);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (ft_free(ppx->full_path), NULL);
}

void	child_process(t_pipex *ppx, char **av, char **envp)
{
	ppx->fd0 = open(av[1], O_RDONLY, 0644);
	if (ppx->fd0 == -1)
	{
		close_pipes(ppx);
		free_src(ppx);
		error_msg(ERR_INFILE, 1);
	}
	if (dup2(ppx->fd0, 0) == -1 || dup2(ppx->fd[1], 1) == -1)
	{
		close(ppx->fd0);
		close(ppx->fd[1]);
		free_src(ppx);
		error_msg(ERR_DUP, 1);
	}
	close(ppx->fd[0]);
	ppx->cmd = ft_split(av[2], ' ');
	ppx->path = get_cmd_path(ppx, envp);
	if (!ppx->path)
	{
		free_src(ppx);
		error_msg(ERR_CMD, 127);
	}
	execve(ppx->path, ppx->cmd, envp);
	free_src(ppx);
	error_msg(ERR_EXEC, 1);
}

void	parent_process(t_pipex *ppx, char **av, char **envp)
{
	ppx->fd1 = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (ppx->fd1 == -1)
	{
		close_pipes(ppx);
		free_src(ppx);
		error_msg(ERR_OUTFILE, 1);
	}
	if (dup2(ppx->fd[0], 0) == -1 || dup2(ppx->fd1, 1) == -1)
	{
		close(ppx->fd[0]);
		close(ppx->fd1);
		free_src(ppx);
		error_msg(ERR_DUP, 1);
	}
	close(ppx->fd[1]);
	ppx->cmd = ft_split(av[3], ' ');
	ppx->path = get_cmd_path(ppx, envp);
	if (!ppx->path)
	{
		free_src(ppx);
		error_msg(ERR_CMD, 127);
	}
	execve(ppx->path, ppx->cmd, envp);
	free_src(ppx);
	error_msg(ERR_EXEC, 1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	ppx;

	ppx.cmd = NULL;
	ppx.path = NULL;
	ppx.full_path = NULL;
	ppx.fd0 = -1;
	ppx.fd1 = -1;
	if (ac != 5)
		error_msg(ERR_ARG, 1);
	if (pipe(ppx.fd) == -1)
		error_msg(ERR_PIPE, 1);
	fork_pipex(&ppx, av, envp);
	close_pipes(&ppx);
	free_src(&ppx);
	return (0);
}
