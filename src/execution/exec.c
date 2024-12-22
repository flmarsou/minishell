/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andi <andi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:53:50 by andi              #+#    #+#             */
/*   Updated: 2024/12/23 00:21:20 by andi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exec_builtin(char **command, t_environ **environ)
{
	unsigned int i;
	unsigned int builtin;
	

	i = 1;
	if (ft_strcmp(command[0], "cd") == 0)
		ft_cd(command, &builtin);
	else if (ft_strcmp(command[0], "echo") == 0)
		ft_echo(command, &builtin);
	else if (ft_strcmp(command[0], "pwd") == 0)
		ft_pwd(&builtin);
	else if (ft_strcmp(command[0], "unset") == 0)
		while (command[i])
			ft_unset(environ, command[i++], &builtin);
	else if (ft_strcmp(command[0], "export") == 0)
		while (command[i])
			ft_export(environ, command[i++], &builtin);
	else if (ft_strcmp(command[0], "env") == 0)
		ft_env(*environ, &builtin);
	else if (ft_strcmp(command[0], "exit") == 0)
	{
	
	}
	if (builtin == 1)
		return (true);
	return (false);
}

void handle_redirections(t_parser *parser)
{
    int fd;
	unsigned int i;

	i = 0;
    while (i < parser->nbr_of_redirs)
    {
        if (parser->token[i] == HEREDOC)
            fd = heredoc(parser->type[i][1]); // Handle HEREDOC (<<).
        else if (parser->token[i] == OUTPUT_REDIRECT)
            fd = open(parser->type[i][1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (parser->token[i] == APPEND_REDIRECT)
            fd = open(parser->type[i][1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else if (parser->token[i] == INPUT_REDIRECT)
            fd = open(parser->type[i][1], O_RDONLY);
        if (fd == -1)
            ft_perror("redirection");
        if (parser->token[i] == INPUT_REDIRECT || parser->token[i] == HEREDOC)
            dup2(fd, STDIN_FILENO); // Redirect input.
        else
            dup2(fd, STDOUT_FILENO); // Redirect output.

        close(fd); // Close the file descriptor after duplication.
		i++;
    }
}

void exec(t_parser *parser, unsigned int groups, t_environ *environ)
{
	int pipefd[2];
    int prev_fd;
    pid_t pid;
	unsigned int i;

	i = 0;
	prev_fd = -1;
	pid = fork();
	while (i < parser->nbr_of_redirs)
	{
		if (i < groups - 1)
			pipe(pipefd);
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (prev_fd != -1)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
		if (i < groups - 1) // If not the last command, set pipe output as STDOUT.
		{
			close(pipefd[0]); // Close unused read end.
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		handle_redirections(&parser[i]);
		if (exec_builtin(parser[i].command, environ) == false)
			exec_execve();
		if (prev_fd != -1)
			close(prev_fd); // Close previous pipe read end.
		if (i < groups - 1)
		{
			close(pipefd[1]); // Close current pipe write end.
			prev_fd = pipefd[0]; // Save read end for the next command.
		}
		i++;
	}
	i = 0;
	// Wait for all child processes to finish.
	while (i < groups)
	{
		wait(NULL);
		i++;	
	}
}
