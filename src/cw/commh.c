#include "ft_cw.h"

int				ft_commh_add(t_comm_handler **commh, char command, int cycles,
					int (*f)(t_corewar *cw, t_carriage *carr))
{
	t_comm_handler	*comm;

	if ((comm = (t_comm_handler*)ft_memalloc(sizeof(t_comm_handler))) == NULL)
		return (FT_MEMORY);
	comm->comm = command;
	comm->cycles = cycles;
	comm->f = f;
	if (*commh != NULL)
		comm->next = *commh;
	*commh = comm;
	return (FT_OK);
}

t_comm_handler	*ft_commh_by_byte(t_corewar *cw, char command)
{
	t_comm_handler	*commh;

	commh = cw->commh;
	while (commh)
	{
		if (command == commh->comm)
			return (commh);
		commh = commh->next;
	}
	return (cw->commh_default);
}