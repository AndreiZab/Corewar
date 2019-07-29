#include "ft_cw.h"

t_corewar	*ft_cw_alloc(int *err)
{
	t_corewar *cw;

	if ((cw = (t_corewar*)ft_memalloc(sizeof(t_corewar))) == NULL)
	{
		*err = FT_MEMORY;
		return (NULL);
	}
	if (ft_player_new(&cw->players) == NULL)
	{
		free(cw);
		*err = FT_MEMORY;
		return (NULL);
	}
	*err = FT_OK;
	return (cw);
}

void		ft_cw_free(t_corewar **cw)
{
	if (cw == NULL || *cw == NULL)
		return ;
	ft_argh_free(&((*cw)->argh));
	ft_argh_free(&((*cw)->argh_default));
	ft_commh_free(&((*cw)->commh));
	ft_commh_free(&((*cw)->commh_default));
	ft_carriage_list_free(&((*cw)->carriages));
	ft_player_list_free(&((*cw)->players));
	if ((*cw)->map)
		free((*cw)->map);
	//if ((*cw)->v)
	//	ft_vis_free((*cw));
	free(*cw);
	*cw = NULL;
}