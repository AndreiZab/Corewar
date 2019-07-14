#include "ft_cw.h"

/*
** Larlyne's code :)
**/

/*
** RU
** Модуль обработки аргументов:
** ft_argh_add - добавить обработчик
** ft_argh_do - находит обработчик для аргумента.
** 	Если для данного аргумента не задан обработчик
** 	будет выполнен стандартный обработчик
** ft_argh_free - удаляет список обработчиков из памяти
*/

int		ft_argh_add(t_arg_handler **arg_h, char *on_arg,
			int (*f)(t_corewar *cw, int argc, char **arg, int *arg_i))
{
	t_arg_handler	*arg;
	t_arg_handler	*finder;

	if (arg_h == NULL)
		return (FT_NULL);
	if ((arg = (t_arg_handler*)ft_memalloc(sizeof(t_arg_handler))) == NULL)
		return (FT_MEMORY);
	if (on_arg != NULL)
		arg->on_arg = ft_strdup(on_arg);
	arg->f = f;
	//Переделать под добавление в начало массива - так быстрее
	if (*arg_h == NULL)
		*arg_h = arg;
	else
	{
		finder = *arg_h;
		while (finder->next)
			finder = finder->next;
		finder->next = arg;
	}
	return (FT_OK);
}

int		ft_argh_do(t_corewar *cw, int argc, char **argv, int *arg_i)
{
	t_arg_handler	*curr;

	curr = cw->argh;
	while (curr)
	{
		if (ft_strcmp(argv[*arg_i], curr->on_arg) == 0)
			return (curr->f(cw, argc, argv, arg_i));
		curr = curr->next;
	}
	return (cw->argh_default->f(cw, argc, argv, arg_i));
}

void	ft_argh_free(t_arg_handler **arg_h)
{
	t_arg_handler	*curr;
	t_arg_handler	*next;

	if (arg_h == NULL)
		return ;
	curr = *arg_h;
	while (curr)
	{
		next = curr->next;
		if (curr->on_arg)
			free(curr->on_arg);
		free(curr);
		curr = next;
	}
	*arg_h = NULL;
}