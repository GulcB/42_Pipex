/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:25:26 by gbodur            #+#    #+#             */
/*   Updated: 2025/02/25 12:01:44 by gbodur           ###   ########.fr       */
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
			return (ft_free(ppx->full_path), ppx->full_path = NULL, NULL);
		b_full_cmd = ft_strjoin(b_dir, ppx->cmd[0]);
		free(b_dir);
		if (access(b_full_cmd, F_OK | X_OK) == 0)
			return (ft_free(ppx->full_path), ppx->full_path = NULL, b_full_cmd);
		free(b_full_cmd);
	}
	return (ft_free(ppx->full_path), ppx->full_path = NULL, NULL);
}

// void	b_setup_cmd_exec(t_pipex *ppx, char **av, char **env, int cmd_i)
// {
// 	ppx->cmd_path[cmd_i] = find_cmd_path(ppx, env);
// 	if (!ppx->cmd_path[cmd_i])
// 	{
// 		ft_putstr_fd(av[cmd_i + 2 + ppx->heredoc_mode], 2);
// 		b_error_msg(ERR_CMD, 1);
// 	}
// 	if (cmd_i == ppx->cmd_count - 1)
// 	{
// 		if (dup2(ppx->fd1, 1) == -1)
// 			b_error_msg(ERR_DUP, 1);
// 		close(ppx->fd1);
// 	}
// 	if (execve(ppx->cmd_path[cmd_i], ppx->cmd, env) == -1)
// 	{
// 		free_list(ppx);
// 		b_error_msg(ERR_EXEC, 1);
// 	}
// }

void b_setup_cmd_exec(t_pipex *ppx, char **av, char **env, int cmd_i)
{
    debug_print("setup_cmd_exec: finding command path");
    ppx->cmd_path[cmd_i] = find_cmd_path(ppx, env);
    if (!ppx->cmd_path[cmd_i])
    {
        debug_print("setup_cmd_exec: command not found");
        ft_putstr_fd(av[cmd_i + 2 + ppx->heredoc_mode], 2);
        b_error_msg(ERR_CMD, 1);
    }
    debug_print("setup_cmd_exec: command found");
    
    if (cmd_i == ppx->cmd_count - 1)
    {
        debug_print("setup_cmd_exec: redirecting to output file");
        if (dup2(ppx->fd1, 1) == -1)
            b_error_msg(ERR_DUP, 1);
        close(ppx->fd1);
    }
    
    debug_print("setup_cmd_exec: executing command");
    
	if (execve(ppx->cmd_path[cmd_i], ppx->cmd, env) == -1)
    {
        debug_print("setup_cmd_exec: execve failed with error");
        perror("execve error");
        free_list(ppx);
        b_error_msg(ERR_EXEC, 1);
    }
    // if (execve(ppx->cmd_path[cmd_i], ppx->cmd, env) == -1)
    // {
    //     debug_print("setup_cmd_exec: execve failed");
    //     free_list(ppx);
    //     b_error_msg(ERR_EXEC, 1);
    // }
}

// void	process_heredoc_input(t_pipex *ppx, char **av, size_t delimiter_len)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		write(1, "heredoc>", 8);
// 		line = get_next_line(0);
// 		if (!line)
// 			break ;
// 		if (!ft_strncmp(line, av[2], delimiter_len))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(ppx->heredoc_fd[1], line, ft_strlen(line));
// 		free(line);
// 	}
// }

void process_heredoc_input(t_pipex *ppx, char **av, size_t delimiter_len)
{
    char *line;

    debug_print("heredoc_input: started");
    while (1)
    {
        write(1, "heredoc>", 8);
        line = get_next_line(0);
        if (!line)
        {
            debug_print("heredoc_input: null line");
            break;
        }
        if (!ft_strncmp(line, av[2], delimiter_len))
        {
            debug_print("heredoc_input: found delimiter");
            free(line);
            break;
        }
        write(ppx->heredoc_fd[1], line, ft_strlen(line));
        free(line);
    }
    debug_print("heredoc_input: completed");
}

void	process_heredoc(t_pipex *ppx, char **av)
{
<<<<<<< HEAD
	size_t	delimiter_len;

	delimiter_len = ft_strlen(av[2]);
	if (pipe(ppx->heredoc_fd) == -1)
		b_error_msg(ERR_PIPE, 1);
	process_heredoc_input(ppx, av, delimiter_len);
=======
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
>>>>>>> be6e12660cb3e3354e8eb35fc6694df14ecd7b62
	close(ppx->heredoc_fd[1]);
	if (dup2(ppx->heredoc_fd[0], 0) == -1)
		b_error_msg(ERR_DUP, 1);
	close(ppx->heredoc_fd[0]);
}

void	setup_files(t_pipex *ppx, char **av, int ac)
{
	if (ppx->heredoc_mode)
	{
<<<<<<< HEAD
		ppx->fd1 = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (ppx->fd1 < 0)
			b_error_msg(ERR_OUTFILE, 1);
		process_heredoc(ppx, av);
=======
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
>>>>>>> be6e12660cb3e3354e8eb35fc6694df14ecd7b62
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
