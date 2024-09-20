#ifdef __cplusplus
extern "C" {
#endif

	#ifndef S21_COMMON_H
	# define S21_COMMON_H
	# define MAX_INT 2147483647
	# define MIN_INT -2147483648
	# include <stdlib.h>
	# include <stdio.h>
	# include <string.h>
	
	
	int		s21_isdigit(int c);
	size_t	s21_strlen(const char *s);
	size_t	s21_strlcpy(char *dst, const char *src, size_t dstsize);
	int		s21_atoi(const char *str);
	char	*s21_substr(char const *s, unsigned int start, size_t len);
	char	**s21_split(char const *s, char c);
	char	*s21_itoa(int n);
	
	#endif
#ifdef __cplusplus
}
#endif
