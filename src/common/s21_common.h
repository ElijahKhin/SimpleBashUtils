#ifdef __cplusplus
extern "C" {
#endif

	#ifndef S21_COMMON_H
	# define S21_COMMON_H
	# define MAX_INT 2147483647
	# define MIN_INT -2147483648
	# include <stdlib.h>
	# include <stdio.h>
	
	
	int		ft_isdigit(int c);
	size_t	ft_strlen(const char *s);
	size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
	int		ft_atoi(const char *str);
	char	*ft_substr(char const *s, unsigned int start, size_t len);
	char	**ft_split(char const *s, char c);
	char	*ft_itoa(int n);
	
	#endif
#ifdef __cplusplus
}
#endif
