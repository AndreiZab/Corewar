/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:18:52 by larlyne           #+#    #+#             */
/*   Updated: 2019/07/12 16:37:55 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);

void			*ft_memcpy(void *dst, const void *src,
				size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);

char			*ft_strnew(size_t size);
size_t			ft_strlen(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_atoi(const char *str);

void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putnbr(int n);

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);

void			*ft_realloc(void *src, size_t old_size, size_t new_size);
int				ft_putstrn_fd(int fd, char *str, int n);
int				ft_putstrn(char *str, int n);
int				ft_putcharn_fd(int fd, char c, int n);
void			ft_putendl_fd(char const *str, int fd);
int				ft_isint(const char *str);

char			*ft_strdup(const char *s1);
void			*ft_memchr(const void *s, int c, size_t n);

/*
** Larlyne's String
** ft_lstr_new_empty - вернет пустую созданную строку
** ft_lstr_new - вернет строку из %c символов %n длины
** ft_lstr_from_raw - создать lstr с указывающий на %str
** ft_lstr_new_copy - копировать %str в новый lstr
** ft_lstr_insert_c - добавляет символ %c %count раз в позицию %index
** ft_lstr_insert_s - добавляет строку %str в позицию %index
** ft_lstr_insert_sn - добавляет %n символов строки %str
** ft_lstr_place_c - заменяет %count символов начиная с %index
**  на символ %c, если длины строки недостаточно, она будет продлена
** ft_lstr_place_s - помещает строку %str в позицию %index
**  поверх существующих символов
** ft_lstr_place_sn - помещает %len символов строки %s в позицию %index
**  поверх существующих символов
** в позицию %index, но не больше чем в строке %str
** ft_lstr_put_fd - выводит строку в поток %fd
** ft_lstr_put - выводит строку в стандартный поток вывода
** ft_lstr_destroy - уничтожает строку
** ft_lstr_minimize - уменьшает объем памяти занимаемый строкой
**	путем избавления от неиспользуемой части
*/

typedef struct	s_lstr
{
	char	*str;
	int		length;
	int		capacity;
}				t_lstr;

t_lstr			*ft_lstr_new_empty(void);
t_lstr			*ft_lstr_new(char c, int n);
t_lstr			*ft_lstr_new_raw(char *str);
t_lstr			*ft_lstr_new_copy(char *str);

void			ft_lstr_insert_c(t_lstr *lstr, char c, int count, int index);
void			ft_lstr_insert_s(t_lstr *lstr, char *str, int index);
void			ft_lstr_insert_sn(t_lstr *lstr, char *str, int len, int index);

void			ft_lstr_put_fd(t_lstr *lstr, int fd);
void			ft_lstr_put(t_lstr *lstr);

void			ft_lstr_destroy(t_lstr **lstr);
void			ft_lstr_minimize(t_lstr *lstr);
int				ft_lstr_resize(t_lstr *lstr, int new_length);

#endif
