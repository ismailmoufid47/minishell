/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:06:36 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/08 20:16:31 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef T_NODE
#  define T_NODE

typedef struct s_node
{
	int				value;
	int				sorted_index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;
# endif

typedef struct s_flags
{
	int	minus;
	int	width;
	int	precision;
	int	precision_value;
	int	zero;
	int	hash;
	int	space;
	int	plus;
}	t_flags;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_nbrlen(long nbr, int hex, int hash);
int		ft_putptr(unsigned long n, t_flags flags);
int		ft_puthex(unsigned int n, int upper, t_flags flags);
int		ft_putnbru(unsigned int n, t_flags flags);
int		ft_printf(const char *format, ...);
int		ft_putchar(char c, t_flags flags);
int		ft_putstr(char *str, t_flags flags);
int		ft_putnbr(long n, t_flags flags);
int		write_padding(int len, t_flags flags, char pad_char);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	*free_table(char **table, int size);
char	**ft_split(char const *s, char c);
void	ft_free_split(char **split);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t max_sub_len);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strnstr(const char *haystack, const char *needle, 
			size_t max_search);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_isprint(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen2(const char *line);
char	*ft_strjoin2(char *line, char *s2);
char	*ft_strdup2(char *s1);
int		ft_strchr2(const char *line, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr2(char *line, unsigned int start, size_t len);
char	*get_next_line(int fd);
#endif