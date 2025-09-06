/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dictionary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsirelkh <hsirelkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 13:05:46 by hsirelkh          #+#    #+#             */
/*   Updated: 2025/09/06 16:26:07 by hsirelkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "rush02.h"


int	add_entry(t_dict **dict, char *key, char *value)
{
	t_dict	*new;
	t_dict	*cur;

	new = (t_dict *)malloc(sizeof(t_dict));
	if (!new)
		return (0);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!*dict)
	{
		*dict = new;
	}
	else
	{
		cur = *dict;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (1);
}

int	parse_line(t_dict **dict, char *line)
{
	int		i;
	int		colon_index;
	int		j;
	char	*key;
	char	*value;
	char	*key_dup;
	char	*value_dup;

	i = 0;
	// Skip leading spaces/tabs
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	// Find colon
	colon_index = -1;
	j = i;
	while (line[j])
	{
		if (line[j] == ':')
		{
			colon_index = j;
			break ;
		}
		j++;
	}
	if (colon_index == -1)
		return (0);
	// Temporarily replace colon with '\0' to split key and value
	line[colon_index] = '\0';
	key = trim_spaces(line + i);
	value = trim_spaces(line + colon_index + 1);
	if (!is_number_str(key) || !value[0])
	{
		line[colon_index] = ':'; // restore colon before returning
		return (0);
	}
	key_dup = ft_strdup(key);
	value_dup = ft_strdup(value);
	line[colon_index] = ':'; // restore colon
	if (!key_dup || !value_dup)
	{
		free(key_dup);
		free(value_dup);
		return (0);
	}
	if (!add_entry(dict, key_dup, value_dup))
	{
		free(key_dup);
		free(value_dup);
		return (0);
	}
	return (1);
}

char	*read_file(const char *filename)
{
	int		fd;
	char	*buffer;
	char	temp[1024];
	ssize_t	bytes_read;
	int		total_len;
	char	*new_buffer;
	int		i;
	int		j;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	buffer = NULL;
	total_len = 0;
	while ((bytes_read = read(fd, temp, 1024)) > 0)
	{
		new_buffer = (char *)malloc(total_len + bytes_read + 1);
		if (!new_buffer)
		{
			free(buffer);
			close(fd);
			return (NULL);
		}
		// Copy old buffer
		i = 0;
		while (i < total_len)
		{
			new_buffer[i] = buffer[i];
			i++;
		}
		// Copy new bytes
		j = 0;
		while (j < bytes_read)
		{
			new_buffer[total_len + j] = temp[j];
			j++;
		}
		new_buffer[total_len + bytes_read] = '\0';
		free(buffer);
		buffer = new_buffer;
		total_len += bytes_read;
	}
	close(fd);
	if (bytes_read < 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

t_dict	*parse_dict(const char *filename)
{
	char	*buffer;
	t_dict	*dict;
	int		i;
	int		line_start;

	buffer = read_file(filename);
	if (!buffer)
		return (NULL);
	dict = NULL;
	i = 0;
	line_start = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			if (!parse_line(&dict, buffer + line_start))
			{
				free_dict(dict);
				free(buffer);
				return (NULL);
			}
			line_start = i + 1;
		}
		i++;
	}
	// Last line (no trailing \n)
	if (buffer[line_start] != '\0')
	{
		if (!parse_line(&dict, buffer + line_start))
		{
			free_dict(dict);
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (dict);
}
