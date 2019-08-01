#include "ft_cw.h"

static void ft_show_players_info(t_corewar *cw)
{
	t_player	*pl;
	t_carriage	*carr;
	int			i;

	pl = cw->players;
	while (pl)
	{
		ft_putstr("Player ");
		ft_putnbr(pl->id);
		ft_putstr(" '");
		ft_putstr(pl->name);
		ft_putstr("' ('");
		ft_putstr(pl->comment);
		ft_putstr("') :\n");
		carr = cw->carriages;
		while (carr)
		{
			if (carr->player_id == -pl->id)
			{
				ft_putstr("\tCarriage (PC = ");
				ft_putnbr(carr->pc);
				ft_putstr(", Live on = ");
				ft_putnbr(carr->cycle_live);
				ft_putstr("): ");
				i = -1;
				while (++i < REG_NUMBER)
				{
					ft_putstr("\n\t\trg[");
					ft_putnbr(i + 1);
					ft_putstr("] = ");
					ft_putnbr(carr->rg[i]);
					ft_putstr("; ");
				}
				ft_putchar('\n');
			}
			carr = carr->next;
		}
		pl = pl->next;
	}
}

int ft_show_dump(t_corewar *cw)
{
	int		i;
	int		j;
	char	*byte;

	i = -1;
	while (++i * FT_DUMP_ROW_SIZE < MEM_SIZE)
	{
		ft_putstr("0x");
		byte = casting_uc_hex(i * FT_DUMP_ROW_SIZE, 4);
		ft_putstr(byte);
		free(byte);
		ft_putstr(" :");
		j = 0;
		while (j < FT_DUMP_ROW_SIZE && j + i * FT_DUMP_ROW_SIZE < MEM_SIZE)
		{
			if ((byte = casting_uc_hex(cw->map[j + i * FT_DUMP_ROW_SIZE], 2))
					== NULL)
				return (FT_MEMORY);
			ft_putchar(' ');
			ft_putstr(byte);
			free(byte);
			++j;
		}
		ft_putchar('\n');
	}
	if (cw->pinfo)
		ft_show_players_info(cw);
	return (FT_OK);
}
