/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:33:15 by vgalmich          #+#    #+#             */
/*   Updated: 2024/06/04 17:29:37 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_count_word(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static char	*ft_create_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((sizeof(char) * (end - start +1)));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static void	ft_initialisation(size_t *i, int *j, int *start)
{
	*i = 0;
	*j = 0;
	*start = -1;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	int		j;
	int		start;

	ft_initialisation(&i, &j, &start);
	tab = ft_calloc((ft_count_word(s, c) + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			tab[j] = ft_create_word(s, start, i);
			if (!tab[j])
				return (ft_free(tab, j));
			start = -1;
			j++;
		}
		i++;
	}
	return (tab);
}
