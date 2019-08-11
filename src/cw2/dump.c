#include "corewar.h"

void		dump_carriages_by_owner(t_corewar *cw, unsigned char owner_id)
{
	t_carriage	*carr;
	int			rg_i;

	carr = cw->carrs;
	while (carr)
	{
		if (carr->owner_id == owner_id)
		{
			ft_putstr("\n\t== Position: ");
			ft_putnbr(carr->pc);
			ft_putstr((carr->carry) ? "\n\tCarry: Yes" : "\n\tCarry: No");
			ft_putstr("\n\tLast live instruction: ");
			ft_putnbr(carr->live_cycle);
			ft_putstr("\n\tRegisters:");
			rg_i = -1;
			while (++rg_i < REG_NUMBER)
			{
				ft_putstr("\n\t\trg[");
				ft_putnbr(rg_i + 1);
				ft_putstr("] = ");
				ft_putnbr(carr->rg[rg_i]);
			}
		}
		carr = carr->next;
	}
}

void		dump_players(t_corewar *cw)
{
	t_player	*pl;
	int			i;

	i = -1;
	while (++i < cw->players_count)
	{
		pl = cw->players + i;
		ft_putstr("\n== Player ");
		ft_putnbr(i + 1);
		ft_putstr(", Champion: '");
		ft_putstr(pl->name);
		ft_putstr((pl->dead) ? "'\nDead: Yes" : "'\nDead: No");
		ft_putstr("\nLast live instruction: ");
		ft_putnbr(pl->live);
		ft_putstr("\nLive carriages:");
		dump_carriages_by_owner(cw, i + 1);
	}
}

void		corewar_dump_info(t_corewar *cw)
{
	ft_putstr("=== DUMP INFO ===\nCycle: ");
	ft_putnbr(cw->cycle);
	dump_players(cw);
	ft_putchar('\n');
}

static int	print_address(int address)
{
	char	*addr;

	if ((addr = casting_uc_hex(address, 4)) == NULL)
		return (COREWAR_STATUS_FATAL);
	ft_putstr("0x");
	ft_putstr(addr);
	ft_putstr(" :");
	free(addr);
	return (COREWAR_STATUS_OK);
}

void		print_byte(unsigned char byte)
{
	char	*alpha;

	alpha = "0123456789abcdef";
	ft_putchar(' ');
	ft_putchar(alpha[byte / 16]);
	ft_putchar(alpha[byte % 16]);
}

int			corewar_dump(t_corewar *cw)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % COREWAR_DUMP_COLUMNS == 0)
			print_address(i);
		if (cw->options & COREWAR_OPT_COLORS)
			ft_setcolor(cc_current, (cw->players_map[i] >= 1 &&
				cw->players_map[i] <= 6) ? cw->players_map[i] : cc_default);
		print_byte(cw->map[i]);
		if ((i + 1)  % COREWAR_DUMP_COLUMNS == 0)
			ft_putstr(" \n"); //Исправить на \n в релизе
		if (cw->options & COREWAR_OPT_COLORS)
			ft_setcolor(cc_default, cc_default);
	}
	if (cw->options & COREWAR_OPT_DUMP_INFO)
		corewar_dump_info(cw);
	return (COREWAR_STATUS_OK);
}