#ifndef RUSH_02

# define RUSH_02

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}					t_dict;

int					is_number_str(char *str);
void				free_dict(t_dict *dict);
int					ft_strlen(char *str);
int					ft_isspace(char c);
int					ft_isdigit(char c);
char				*ft_strdup(char *src);
char				*trim_spaces(char *str);
t_dict				*parse_dict(const char *filename);
void				free_dict(t_dict *dict);
int					ft_strcmp(char *s1, char *s2);
void				ft_putstr(char *str);
void				ft_putchar(char c);
#endif