#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "rush02.h"

// Utility function to write a string to stdout
void ft_putstr(char *str)
{
    int len = 0;
    while (str[len])
        len++;
    write(1, str, len);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char) *s1 - (unsigned char) *s2);
}

// Utility function to write a newline
void ft_putchar(char c)
{
    write(1, &c, 1);
}


int	is_number_str(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
void	free_dict(t_dict *dict)
{
	t_dict	*tmp;

	while (dict)
	{
		tmp = dict;
		dict = dict->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_strdup(char *src)
{
	int		count;
	char	*dest;

	count = 0;
	while (src[count])
		count++;
	dest = malloc(sizeof(char) * (count) + 1);
	if (!dest)
		return (NULL);
	count = 0;
	while (src[count])
	{
		dest[count] = src[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}

char	*trim_spaces(char *str)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	// Move start forward while space
	while (str[start] && ft_isspace(str[start]))
		start++;
	end = start;
	while (str[end])
		end++;
	end--; // move to last char
	while (end >= start && ft_isspace(str[end]))
	{
		str[end] = '\0';
		end--;
	}
	return (str + start);
}
