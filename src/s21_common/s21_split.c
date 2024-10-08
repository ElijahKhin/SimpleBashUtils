#include "s21_common.h"

static int	get_num_of_rows(char const *s, unsigned char c)
{
	int	number_of_rows;

	number_of_rows = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s)
			number_of_rows++;
		while (*s != c && *s)
			s++;
	}
	return (number_of_rows);
}

static void	fill_array(char ***array, char const *s, unsigned char c, int nor)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (nor-- > 0)
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		(*array)[j] = (char *)malloc(sizeof(char) * (i - start + 1));
		s21_strlcpy((*array)[j++], s + start, i - start + 1);
	}
	(*array)[j] = NULL;
}

char	**s21_split(char const *s, char c)
{
	char	**array;
	int		num_of_rows;

	num_of_rows = get_num_of_rows(s, c);
	array = (char **)malloc(sizeof(char *) * (num_of_rows + 1));
	fill_array(&array, s, c, num_of_rows);
	return (array);
}
