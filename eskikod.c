/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eskikod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:43:48 by gbodur            #+#    #+#             */
/*   Updated: 2025/02/22 13:43:49 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// // // pipex mandotary part:

// // #ifndef PIPEX_H
// // # define PIPEX_H

// // # include <unistd.h>
// // # include <fcntl.h>
// // # include <stdlib.h>
// // # include <stdio.h>
// // # include <sys/wait.h>
// // # include "libft/libft.h"

// // # define ERR_ARG "Invalid number of arguments\n"
// // # define ERR_PIPE "Pipe error.\n"
// // # define ERR_CMD "Command not found\n"
// // # define ERR_FORK "Fork error.\n"
// // # define ERR_EXEC "Exec format error.\n"
// // # define ERR_INFILE "Input file error.\n"
// // # define ERR_OUTFILE "Output file error.\n"
// // # define ERR_DUP "Dup2 error.\n"

// // typedef struct s_pipex
// // {
// // 	int			fd[2];
// // 	int			fd0;
// // 	int			fd1;
// // 	char		*path;
// // 	char		**full_path;
// // 	char		**cmd;
// // 	pid_t		pid1;
// // 	pid_t		pid2;
// // }				t_pipex;

// // void	fork_pipex(t_pipex *ppx, char **av, char **envp);
// // char	*get_cmd_path(t_pipex *ppx, char **envp);
// // void	child_process(t_pipex *ppx, char **av, char **envp);
// // void	parent_process(t_pipex *ppx, char **av, char **envp);
// // void	close_pipes(t_pipex *ppx);
// // void	error_msg(char *err_msg, int exit_code);
// // void	ft_free(char **var);
// // void	free_src(t_pipex *ppx);

// // #endif

// // #include "pipex.h"

// // void	close_pipes(t_pipex *ppx)
// // {
// // 	if (ppx->fd[0] != -1)
// // 	{
// // 		close(ppx->fd[0]);
// // 		ppx->fd[0] = -1;
// // 	}
// // 	if (ppx->fd[1] != -1)
// // 	{
// // 		close(ppx->fd[1]);
// // 		ppx->fd[1] = -1;
// // 	}
// // }
// // void	error_msg(char *err_msg, int exit_code)
// // {
// // 	perror(err_msg);
// // 	exit (exit_code);
// // }
// // void	ft_free(char **var)
// // {
// // 	int	i;

// // 	i = 0;
// // 	if (!var)
// // 		return ;
// // 	while (var[i])
// // 	{
// // 		free(var[i]);
// // 		i++;
// // 	}
// // 	free(var);
// // 	var = NULL;
// // }

// // void	free_src(t_pipex *ppx)
// // {
// // 	if (!ppx)
// // 		return ;
// // 	if (ppx->cmd)
// // 	{
// // 		ft_free(ppx->cmd);
// // 		ppx->cmd = NULL;
// // 	}
// // 	if (ppx->path)
// // 	{
// // 		free(ppx->path);
// // 		ppx->path = NULL;
// // 	}
// // 	if (ppx->full_path)
// // 	{
// // 		ft_free(ppx->full_path);
// // 		ppx->full_path = NULL;
// // 	}
// // }

// // #include "pipex.h"

// // void	fork_pipex(t_pipex *ppx, char **av, char **envp)
// // {
// // 	ppx->pid1 = fork();
// // 	if (ppx->pid1 < 0)
// // 	{
// // 		close_pipes(ppx);	
// // 		error_msg(ERR_FORK, 1);
// // 	}
// // 	else if (ppx->pid1 == 0)
// // 		child_process(ppx, av, envp);
// // 	else
// // 	{
// // 		ppx->pid2 = fork();
// // 		if (ppx->pid2 < 0)
// // 		{
// // 			close_pipes(ppx);
// // 			error_msg(ERR_FORK, 1);
// // 		}
// // 		else if (ppx->pid2 == 0)
// // 			parent_process(ppx, av, envp);
// // 		else
// // 		{
// // 			close_pipes(ppx);
// // 			waitpid(ppx->pid1, NULL, 0);	
// // 			waitpid(ppx->pid2, NULL, 0);	
// // 		}
// // 	}	
// // }

// // char	*get_cmd_path(t_pipex *ppx, char **envp)
// // {
// // 	int		i;
// // 	char	*dir;
// // 	char	*cmd_path;

// // 	if (ppx->cmd[0][0] == '/' && access(ppx->cmd[0], F_OK | X_OK) == 0)
// // 		return (ft_strdup(ppx->cmd[0]));
// // 	while (envp && *envp && ft_strncmp("PATH=", *envp, 5))
// // 		envp++;
// // 	if (!envp || !*envp)
// // 		return (NULL);
// // 	ppx->full_path = ft_split (*envp + 5, ':');
// // 	if (!ppx->full_path)
// // 		return (NULL);
// // 	i = -1;
// // 	while (ppx->full_path && ppx->full_path[++i])
// // 	{
// // 		dir = ft_strjoin(ppx->full_path[i], "/");
// // 		cmd_path = ft_strjoin(dir, ppx->cmd[0]);
// // 		free(dir);
// // 		if (access(cmd_path, F_OK | X_OK) == 0)
// // 			return (cmd_path);
// // 		free(cmd_path);
// // 	}
// // 	return (ft_free(ppx->full_path), NULL);
// // }

// // void	child_process(t_pipex *ppx, char **av, char **envp)
// // {
// // 	ppx->fd0 = open(av[1], O_RDONLY, 0644);
// // 	if (ppx->fd0 == -1)
// // 	{
// // 		close_pipes(ppx);
// // 		free_src(ppx);
// // 		error_msg(ERR_INFILE, 1);
// // 	}
// // 	if (dup2(ppx->fd0, 0) == -1 || dup2(ppx->fd[1], 1) == -1)
// // 	{
// // 		close(ppx->fd0);
// // 		close(ppx->fd[1]);
// // 		free_src(ppx);
// // 		error_msg(ERR_DUP, 1);
// // 	}
// // 	close(ppx->fd[0]);
// // 	ppx->cmd = ft_split(av[2], ' ');
// // 	ppx->path = get_cmd_path(ppx, envp);
// // 	if (!ppx->path)
// // 	{
// // 		free_src(ppx);
// // 		error_msg(ERR_CMD, 127);
// // 	}
// // 	execve(ppx->path, ppx->cmd, envp);
// // 	free_src(ppx);
// // 	error_msg(ERR_EXEC, 1);
// // }

// // void	parent_process(t_pipex *ppx, char **av, char **envp)
// // {
// // 	ppx->fd1 = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
// // 	if (ppx->fd1 == -1)
// // 	{
// // 		close_pipes(ppx);
// // 		free_src(ppx);
// // 		error_msg(ERR_OUTFILE, 1);
// // 	}
// // 	if (dup2(ppx->fd[0], 0) == -1 || dup2(ppx->fd1, 1) == -1)
// // 	{
// // 		close(ppx->fd[0]);
// // 		close(ppx->fd1);
// // 		free_src(ppx);
// // 		error_msg(ERR_DUP, 1);
// // 	}
// // 	close(ppx->fd[1]);
// // 	ppx->cmd = ft_split(av[3], ' ');
// // 	ppx->path = get_cmd_path(ppx, envp);
// // 	if (!ppx->path)
// // 	{
// // 		free_src(ppx);
// // 		error_msg(ERR_CMD, 127);
// // 	}
// // 	execve(ppx->path, ppx->cmd, envp);
// // 	free_src(ppx);
// // 	error_msg(ERR_EXEC, 1);
// // }

// // int	main(int ac, char **av, char **envp)
// // {
// // 	t_pipex	ppx;

// // 	ppx.cmd = NULL;
// // 	ppx.path = NULL;
// // 	ppx.full_path = NULL;
// // 	ppx.fd0 = -1;
// // 	ppx.fd1 = -1;

// // 	if (ac != 5)
// // 		error_msg(ERR_ARG, 1);
// // 	if (pipe(ppx.fd) == -1)
// // 		error_msg(ERR_PIPE, 1);
// // 	fork_pipex(&ppx, av, envp);
// // 	close_pipes(&ppx);
// // 	free_src(&ppx);
// // 	return (0);
// // }

// // // pipex bonus part:

// // #ifndef PIPEX_BONUS_H
// // # define PIPEX_BONUS_H

// // # include <unistd.h>
// // # include <fcntl.h>
// // # include <stdlib.h>
// // # include <stdio.h>
// // # include <sys/wait.h>
// // # include "../libft/libft.h"
// // # include "../gnl/get_next_line.h"

// // # define ERR_ARG "Invalid number of arguments\n"
// // # define ERR_FEW "Too few arguments\n"
// // # define ERR_PIPE "Pipe error.\n"
// // # define ERR_CMD "Command not found\n"
// // # define ERR_FORK "Fork error.\n"
// // # define ERR_EXEC "Exec format error.\n"
// // # define ERR_INFILE "Input file error.\n"
// // # define ERR_OUTFILE "Output file error.\n"

// // typedef struct s_pipex
// // {
// // 	pid_t		pid;
// // 	int			pipe_fd[2];
// // 	int			heredoc_fd[2];
// // 	int			fd0;
// // 	int			fd1;
// // 	int			heredoc_mode;
// // 	char		*path;
// // 	char		**full_path;
// // 	char		**cmd;
// // }				t_pipex;

// // void	b_child_process(t_pipex *ppx, char **av, char **envp, int i);
// // void	b_parent_process(t_pipex *ppx);
// // void	*create_fork_process(t_pipex *ppx, char **av, char **evp, int i);
// // void	init_pipeline(t_pipex *ppx, char **av, int ac);
// // char	*find_cmd_path(t_pipex *ppx, char **envp, int i);
// // void	process_heredoc(t_pipex *ppx, char **av);
// // void	error_msg(char *err_msg);
// // void	free_list(t_pipex *ppx);
// // void	ft_free(char **del);

// // #endif

// // #include "pipex_bonus.h"

// // void	error_msg(char *err_msg)
// // {
// // 	perror(err_msg);
// // 	exit (127);
// // }

// // void	free_list(t_pipex *ppx)
// // {
// // 	int	i;

// // 	i = 0;
// // 	while (ppx->cmd && ppx->cmd[i])
// // 		free(ppx->cmd[i++]);
// // 	free(ppx->cmd);
// // 	i = 0;
// // 	if (ppx->path)
// // 		free(ppx->path);
// // 	if (ppx->full_path)
// // 		free(ppx->full_path);
// // }

// // void	ft_free(char **del)
// // {
// // 	int	i;

// // 	if (!del)
// // 		return ;
// // 	i = 0;
// // 	while (del[i])
// // 	{
// // 		free(del[i]);
// // 		del[i] = NULL;
// // 		i++;
// // 	}
// // 	free(del);
// // 	del = NULL;
// // }

// // #include "pipex_bonus.h"

// // char	*find_cmd_path(t_pipex *ppx, char **envp, int i)
// // {
// // 	char	*b_dir;
// // 	char	*b_full_cmd;

// // 	if (ppx->cmd[0][0] == '/' && access(ppx->cmd[0], F_OK | X_OK) == 0)
// // 		return (ft_strdup(ppx->cmd[0]));
// // 	while (envp && *envp && ft_strncmp("PATH=", *envp, 5))
// // 		envp++;
// // 	if (!envp || !*envp)
// // 		return (NULL);
// // 	ppx->full_path = ft_split (*envp + 5, ':');
// // 	i = -1;
// // 	while (ppx->full_path && ppx->full_path[++i])
// // 	{
// // 		b_dir = ft_strjoin(ppx->full_path[i], "/");
// // 		if (!b_dir)
// // 			return (NULL);
// // 		b_full_cmd = ft_strjoin(b_dir, ppx->cmd[0]);
// // 		free(b_dir);
// // 		if (access(b_full_cmd, F_OK | X_OK) == 0)
// // 			return (b_full_cmd);
// // 		free(b_full_cmd);
// // 	}
// // 	return (ft_free(ppx->full_path), NULL);
// // }

// // void	process_heredoc(t_pipex *ppx, char **av)
// // {
// // 	char	*line;

// // 	if (pipe(ppx->heredoc_fd) == -1)
// // 		error_msg(ERR_PIPE);
// // 	while (1)
// // 	{
// // 		write(1, "heredoc>", 9);
// // 		line = get_next_line(0);
// // 		if (!line)
// // 			break ;
// // 		if (!ft_strncmp(line, av[2], ft_strlen(av[2]))
// // 			&& line[ft_strlen(av[2])] == '\n')
// // 		{
// // 			free(line);
// // 			break ;
// // 		}
// // 		write(ppx->heredoc_fd[1], line, ft_strlen(line));
// // 		free(line);
// // 	}
// // 	close(ppx->heredoc_fd[1]);
// // 	dup2(ppx->heredoc_fd[0], 0);
// // 	close(ppx->heredoc_fd[0]);
// // }

// // #include "pipex_bonus.h"

// // void	b_child_process(t_pipex *ppx, char **av, char **envp, int i)
// // {
// // 	close(ppx->pipe_fd[0]);
// // 	dup2(ppx->pipe_fd[1], 1);
// // 	close(ppx->pipe_fd[1]);
// // 	ppx->cmd = ft_split(av[i], ' ');
// // 	ppx->path = find_cmd_path(ppx, envp, i);
// // 	if (!ppx->path)
// // 	{
// // 		ft_putstr_fd(av[i], 2);
// // 		error_msg(ERR_CMD);
// // 	}
// // 	if (execve(ppx->path, ppx->cmd, envp) == -1)
// // 	{
// // 		free_list(ppx);
// // 		error_msg(ERR_EXEC);
// // 	}
// // }
// // void	b_parent_process(t_pipex *ppx)
// // {
// // 	close(ppx->pipe_fd[1]);
// // 	dup2(ppx->pipe_fd[0], 0);
// // 	close(ppx->pipe_fd[0]);
// // 	wait(NULL);
// // }

// // void	*create_fork_process(t_pipex *ppx, char **av, char **envp, int i)
// // {
// // 	if (ppx->heredoc_mode == 1)
// // 		i = 3;
// // 	else
// // 		i = 2;
// // 	if (pipe(ppx->pipe_fd) == -1)
// // 		error_msg(ERR_PIPE);
// // 	ppx->pid = fork();
// // 	if (ppx->pid < 0)
// // 		error_msg(ERR_FORK);
// // 	else if (ppx->pid == 0)
// // 		b_child_process(ppx, av, envp, i);
// // 	else
// // 		b_parent_process(ppx);
// // 	return (0);
// // }

// // void	init_pipeline(t_pipex *ppx, char **av, int ac)
// // {
// // 	if (!ppx->heredoc_mode)
// // 	{
// // 		ppx->fd0 = open(av[1], O_RDONLY);
// // 		if (ppx->fd0 < 0)
// // 			error_msg(ERR_INFILE);
// // 		ppx->fd1 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
// // 		if (ppx->fd1 < 0)
// // 			error_msg(ERR_OUTFILE);
// // 		dup2(ppx->fd0, 0);
// // 		close(ppx->fd0);
// // 	}
// // 	else
// // 	{
// // 		ppx->fd1 = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
// // 		if (ppx->fd1 < 0)
// // 			error_msg(ERR_OUTFILE);
// // 		process_heredoc(ppx, av);
// // 	}
// // }

// // int	main(int ac, char **av, char **envp)
// // {
// // 	t_pipex	ppx;
// // 	int		i;

// // 	i = 0;
// // 	ppx.heredoc_mode = 0;
// // 	if (ac < 5)
// // 		error_msg(ERR_ARG);
// // 	if (ft_strncmp(av[1], "here_doc", 8) == 0)
// // 		ppx.heredoc_mode = 1;
// // 	if (ac < 6 && ppx.heredoc_mode == 1)
// // 		error_msg(ERR_FEW);
// // 	init_pipeline(&ppx, av, ac);
// // 	while (i < ac - 2)
// // 	{
// // 		create_fork_process(&ppx, av, envp, i);
// // 		waitpid(ppx.pid, NULL, 0);
// // 		i++;
// // 	}
// // 	dup2(ppx.fd1, 1);
// // 	close(ppx.fd1);
// // 	free_list(&ppx);
// // 	return (0);
// // }

// #ifndef PIPEX_BONUS_H
// # define PIPEX_BONUS_H

// # include <unistd.h>
// # include <fcntl.h>
// # include <stdlib.h>
// # include <stdio.h>
// # include <sys/wait.h>
// # include "libft/libft.h"
// # include "get_next_line.h"

// # define ERR_ARG "Invalid number of arguments\n"
// # define ERR_PIPE "Pipe error\n"
// # define ERR_CMD "Command not found\n"
// # define ERR_FORK "Fork error\n"
// # define ERR_EXEC "Exec format error\n"
// # define ERR_FILE "File error\n"
// # define ERR_DUP "Dup2 error\n"

// typedef struct s_pipe
// {
// 	int		cmd_count;
// 	int		pipe_count;
// 	int		pipe_fd[2];
// 	int		infile;
// 	int		outfile;
// 	char	**cmd_paths;
// 	char	**cmd_args;
// 	char	**env;
// 	pid_t	pid;
// 	int		heredoc;
// 	char	*delimiter;
// }	t_pipe;

// char	*find_cmd(char *cmd, char **env);
// void	child_process(t_pipe *pipex, char **av, int i);
// void	close_pipes(t_pipe *pipex);
// void	ft_error(char *err);
// void	ft_free_parent(t_pipe *pipex);
// void	ft_free_child(t_pipe *pipex);
// void	get_heredoc(t_pipe *pipex, char *av);
// void	init_bonus(t_pipe *pipex, int ac, char **av, char **env);
// void	parent_process(t_pipe *pipex);

// #endif

// #include "pipex_bonus.h"

// static void	child_dup(t_pipe *pipex, int i)
// {
// 	if (i == 0 && pipex->heredoc == 0)
// 	{
// 		if (dup2(pipex->infile, 0) < 0)
// 			ft_error(ERR_DUP);
// 	}
// 	else if (i == 0 && pipex->heredoc == 1)
// 	{
// 		if (dup2(pipex->pipe_fd[0], 0) < 0)
// 			ft_error(ERR_DUP);
// 	}
// 	if (i == pipex->cmd_count - 1)
// 	{
// 		if (dup2(pipex->outfile, 1) < 0)
// 			ft_error(ERR_DUP);
// 	}
// 	else
// 	{
// 		if (dup2(pipex->pipe_fd[1], 1) < 0)
// 			ft_error(ERR_DUP);
// 	}
// }

// void	child_process(t_pipe *pipex, char **av, int i)
// {
// 	pipex->cmd_args = ft_split(av[i], ' ');
// 	if (!pipex->cmd_args)
// 		ft_error(ERR_CMD);
// 	pipex->cmd_paths[i] = find_cmd(pipex->cmd_args[0], pipex->env);
// 	if (!pipex->cmd_paths[i])
// 	{
// 		ft_free_child(pipex);
// 		ft_error(ERR_CMD);
// 	}
// 	child_dup(pipex, i);
// 	close_pipes(pipex);
// 	if (execve(pipex->cmd_paths[i], pipex->cmd_args, pipex->env) < 0)
// 	{
// 		ft_free_child(pipex);
// 		ft_error(ERR_EXEC);
// 	}
// }

// #include "pipex_bonus.h"

// void	ft_error(char *err)
// {
// 	perror(err);
// 	exit(1);
// }

// void	close_pipes(t_pipe *pipex)
// {
// 	close(pipex->pipe_fd[0]);
// 	close(pipex->pipe_fd[1]);
// }

// void	ft_free_parent(t_pipe *pipex)
// {
// 	int	i;

// 	i = 0;
// 	close(pipex->infile);
// 	close(pipex->outfile);
// 	if (pipex->heredoc)
// 		unlink(".heredoc_tmp");
// 	while (i < pipex->cmd_count)
// 	{
// 		free(pipex->cmd_paths[i]);
// 		i++;
// 	}
// 	free(pipex->cmd_paths);
// }

// void	ft_free_child(t_pipe *pipex)
// {
// 	int	i;

// 	i = 0;
// 	while (pipex->cmd_args[i])
// 	{
// 		free(pipex->cmd_args[i]);
// 		i++;
// 	}
// 	free(pipex->cmd_args);
// }

// #include "pipex_bonus.h"

// #include "pipex_bonus.h"

// static char	*get_path(char *cmd, char **paths)
// {
// 	char	*tmp;
// 	char	*command;

// 	while (*paths)
// 	{
// 		tmp = ft_strjoin(*paths, "/");
// 		command = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (access(command, 0) == 0)
// 			return (command);
// 		free(command);
// 		paths++;
// 	}
// 	return (NULL);
// }

// char	*find_cmd(char *cmd, char **env)
// {
// 	char	**paths;
// 	char	*path;
// 	int		i;

// 	i = 0;
// 	while (env[i] && ft_strncmp("PATH=", env[i], 5))
// 		i++;
// 	if (!env[i])
// 		return (NULL);
// 	paths = ft_split(env[i] + 5, ':');
// 	path = get_path(cmd, paths);
// 	ft_free_matrix(paths);
// 	return (path);
// }

// void	get_heredoc(t_pipe *pipex, char *av)
// {
// 	int		file;
// 	char	*lne;

// 	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (file < 0)
// 		ft_error(ERR_FILE);
// 	while (1)
// 	{
// 		write(1, "heredoc> ", 9);
// 		lne = get_next_line(0);
// 		if (!lne)
// 			break ;
// 		if (!ft_strncmp(lne, av, ft_strlen(av)) && lne[ft_strlen(av)] == '\n')
// 		{
// 			free(lne);
// 			break ;
// 		}
// 		write(file, lne, ft_strlen(lne));
// 		free(lne);
// 	}
// 	close(file);
// 	pipex->infile = open(".heredoc_tmp", O_RDONLY);
// 	if (pipex->infile < 0)
// 	{
// 		unlink(".heredoc_tmp");
// 		ft_error(ERR_FILE);
// 	}
// }

// void	init_bonus(t_pipe *pipex, int ac, char **av, char **env)
// {
// 	pipex->cmd_count = ac - 3 - pipex->heredoc;
// 	pipex->cmd_paths = malloc(sizeof(char *) * pipex->cmd_count);
// 	if (!pipex->cmd_paths)
// 		ft_error(ERR_CMD);
// 	pipex->env = env;
// 	if (pipex->heredoc)
// 		get_heredoc(pipex, av[2]);
// 	else
// 	{
// 		pipex->infile = open(av[1], O_RDONLY);
// 		if (pipex->infile < 0)
// 			ft_error(ERR_FILE);
// 	}
// 	if (pipex->heredoc)
// 		pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else
// 		pipex->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (pipex->outfile < 0)
// 		ft_error(ERR_FILE);
// }

// #include "pipex_bonus.h"

// void	parent_process(t_pipe *pipex)
// {
// 	close_pipes(pipex);
// 	waitpid(pipex->pid, NULL, 0);
// }

// static void	execute_cmd(t_pipe *pipex, char **av, int i)
// {
// 	if (pipe(pipex->pipe_fd) < 0)
// 		ft_error(ERR_PIPE);
// 	pipex->pid = fork();
// 	if (pipex->pid < 0)
// 		ft_error(ERR_FORK);
// 	if (pipex->pid == 0)
// 		child_process(pipex, av, i);
// 	else
// 		parent_process(pipex);
// }

// int	main(int ac, char **av, char **env)
// {
// 	t_pipe	pipex;
// 	int		i;

// 	if (ac < 5)
// 		ft_error(ERR_ARG);
// 	pipex.heredoc = 0;
// 	if (ft_strncmp("here_doc", av[1], 9) == 0)
// 	{
// 		pipex.heredoc = 1;
// 		if (ac < 6)
// 			ft_error(ERR_ARG);
// 	}
// 	init_bonus(&pipex, ac, av, env);
// 	i = 2 + pipex.heredoc;
// 	while (i < ac - 1)
// 	{
// 		execute_cmd(&pipex, av, i);
// 		i++;
// 	}
// 	ft_free_parent(&pipex);
// 	return (0);
// }
