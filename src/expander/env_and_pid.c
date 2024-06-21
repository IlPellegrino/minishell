/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:46:33 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/21 17:16:32 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*check_name(const char *name)
{
	int	len;

	len = -1;
	while (name[++len])
	{
		if (ft_isdigit(name[0]))
			return (0);
		else if (name[0] == SQ || name[0] == DQ)
			return (0);
		else if ((!ft_isalnum(name[len]) && name[len] != US))
			return ((char *)name);
	}
	return (0);
}

void	init_counters(t_exp *exp)
{
	exp->pos = -1;
	exp->begin = 0;
	exp->len = 0;
}

char	*make_expansion(t_exp *exp, char *to_expand)
{
	char	*tmp;

	to_expand = ft_strtrim(to_expand, " ");
	while (to_expand[++exp->pos] && to_expand[exp->pos] != '=')
		exp->begin++;
	if (to_expand[exp->pos] != '\0')
		while (to_expand[++exp->pos])
			exp->len++;
	exp->res = ft_calloc(sizeof (char *), exp->len + 1);
	if (!exp->res)
		return (NULL);
	exp->len = -1;
	if (!to_expand[exp->begin])
		exp->begin--;
	while (to_expand[++exp->begin])
		exp->res[++exp->len] = to_expand[exp->begin];
	if (is_token(exp->res))
		exp->res = make_quotes(exp->res);
	tmp = ft_btrim(exp->res, " ");
	free(exp->res);
	exp->res = ft_strdup(tmp);
	return (exp->res);
}

char	*ft_getenv(const char *name, t_shell *shell)
{
	int		i;
	t_exp	exp;

	i = -1;
	while (shell->envp[++i])
	{
		exp.len = 0;
		while (shell->envp[i][exp.len] && shell->envp[i][exp.len] != '=')
			exp.len++;
		if (check_name(name))
			return (ft_strjoin("$", name));
		if (exp.len == (int)ft_strlen(name))
		{
			init_counters(&exp);
			if (!ft_strncmp(name, shell->envp[i], ft_strlen(name)))
				return (make_expansion(&exp, shell->envp[i]));
		}
	}
	return (NULL);
}

char	*expand_pid(void)
{
	int		fd;
	char	*buffer;
	char	*pid;
	int		i;

	buffer = ft_calloc(sizeof(char *), 21);
	fd = open("/proc/self/stat", O_RDONLY, 0777);
	if (fd == -1)
		return (perror("minishell"), NULL);
	if (read(fd, buffer, 20) == -1)
		return (free(buffer), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != SPACE)
		i++;
	pid = ft_calloc(sizeof(char *), i + 1);
	i = -1;
	while (buffer[++i] != SPACE && buffer[i])
		pid[i] = buffer[i];
	free(buffer);
	return (pid);
}
