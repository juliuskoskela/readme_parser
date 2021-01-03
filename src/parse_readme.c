/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_readme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoskela <jkoskela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 17:35:55 by jkoskela          #+#    #+#             */
/*   Updated: 2021/01/03 03:22:50 by jkoskela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"

char		*parse_line(char *line)
{
	char	out[81];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] == '*' || line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		out[j] = line[i];
		while (line[i] == '\t')
		{
			out[j] = ' ';
			i++;
		}
		j++;
		i++;
	}
	out[j] = '\0';
	return (s_dup(out));
}

int			main(int argc, char **argv)
{
	int		fd;
	int		i;
	int		file_cnt;
	char	*line;
	char	*f_name = NULL;
	char	*f_proto = NULL;
	char	*f_info = NULL;
	char	*skip = s_dup("static");
	char	*tmp = s_new(7);

	line = NULL;
	file_cnt = 1;
	printf("name | prototype | description\n");
	printf("-----|-----------|------------\n");

	while (file_cnt < argc)
	{
		fd = open(argv[file_cnt], O_RDONLY);
		while (fd_readline(fd, &line))
		{
			if (i == 14)
			{
				tmp = s_ncpy(tmp, line, 6);
				tmp[7] = '\0';
				if (s_cmp(skip, tmp) == 0)
				{
					while (fd_readline(fd, &line))
					{
						tmp = s_ncpy(tmp, line, 6);
						tmp[7] = '\0';
						if (is_alnum(line[0]) && s_cmp(skip, tmp))
							break ;
					}
				}
				f_proto = parse_line(line);
				break ;
			}
			i++;
		}
		while (fd_readline(fd, &line))
		{
			if (line[0] == '/' && line[1] == '*')
				break ;
		}
		while (fd_readline(fd, &line))
		{
			if (is_alpha(line[3]))
			{
				f_name = parse_line(line);
				f_name[0] = c_tolower(f_name[0]);
				break ;
			}
		}
		while (fd_readline(fd, &line))
		{
			if (line[2] == '\t')
				f_info = s_join(f_info, parse_line(line));
		}
		printf("%s | `%s` | %s \n", f_name, f_proto, f_info);
		free(f_name);
		free(f_proto);
		free(f_info);
		f_name = NULL;
		f_proto = NULL;
		f_info = NULL;
		free(line);
		close(fd);
		i = 0;
		file_cnt++;
	}
	return (0);
}

// library/src -type f | tr '\r\n' ' '