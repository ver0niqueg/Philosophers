/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:19:41 by vgalmich          #+#    #+#             */
/*   Updated: 2024/07/27 15:58:20 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_update_stash(char *stash)
{
	char	*new_stash;
	char	*ptr;
	int		len;

	ptr = gnl_strchr(stash, '\n');
	if (!ptr)
	{
		new_stash = NULL;
		return (ft_free(&stash));
	}
	else
		len = (ptr - stash) + 1;
	if (!stash[len])
		return (ft_free(&stash));
	new_stash = gnl_substr(stash, len, gnl_strlen(stash) - len);
	ft_free(&stash);
	if (!new_stash)
		return (NULL);
	return (new_stash);
}

char	*ft_extract_line(char *stash)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = gnl_strchr(stash, '\n');
	len = (ptr - stash) + 1;
	line = gnl_substr(stash, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_read_buffer(int fd, char *stash)
{
	int		rid;
	char	*buffer;

	rid = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&stash));
	buffer[0] = '\0';
	while (rid > 0 && !gnl_strchr(buffer, '\n'))
	{
		rid = read (fd, buffer, BUFFER_SIZE);
		if (rid > 0)
		{
			buffer[rid] = '\0';
			stash = gnl_strjoin(stash, buffer);
		}
	}
	free(buffer);
	if (rid == -1)
		return (ft_free(&stash));
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = {0};
	char		*line;

	if (fd < 0)
		return (NULL);
	if ((stash && !gnl_strchr(stash, '\n')) || !stash)
		stash = ft_read_buffer (fd, stash);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	if (!line)
		return (ft_free(&stash));
	stash = ft_update_stash(stash);
	return (line);
}
