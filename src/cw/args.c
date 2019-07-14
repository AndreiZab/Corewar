#include "ft_cw.h"

int		ft_add_arg_handler(t_arg_handler **arg_h, char *on_arg,
			int (*f)(char *arg, int *arg_i))
{
	t_arg_handler	*arg;
	t_arg_handler	*finder;

	if (arg_h == NULL)
		return (FT_NULL);
	if ((arg = (t_arg_handler*)ft_malloc(sizeof(t_arg_handler))) == NULL)
		return (FT_MEMORY);
	if (on_arg != NULL)
		arg->on_arg = ft_strdup(on_arg);
	arg->f = f;
	if (*arg_h == NULL)
		*arg_h = arg;
	else
	{
		finder = *arg_h;
		while (finder->next)
			finder = finder->next;
		finder->next = arg;
	}
	return (arg);
}

int		ft_do_arg_handlers(t_corewar *cw, char *argv, int *arg_i)
{
	t_arg_handler	*curr;

	curr = cw->args_h;
	while (curr)
	{
		
		curr = curr->next;
	}
}

int		ft_process_args(t_corewar *cw, int argc, char **argv)
{
	int		arg_i;

	ft_add_arg_handler(&(cw->args_h), "-n", FUNC);
	ft_add_arg_handler(&(cw->arg_default), NULL, FUND_DEF);
	arg_i = 0;
	while (++arg_i < argc)
	{

	}
	return (FT_OK);
}