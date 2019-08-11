#include "corewar.h"

int		main(int argc, char **argv)
{
	int			status;
	t_corewar	*cw;

	status = COREWAR_STATUS_OK;
	cw = corewar_init(&status);
	if (status >= 0)
		status = process_arguments(cw, argc, argv);
	if (status >= 0)
		status = check_players(cw);
	if (status >= 0)
		status = prepare_for_battle(cw);
	if (status >= 0 && (cw->options & COREWAR_OPT_VISUALIZER))
		status = ft_init_sdl(cw);
	if (status >= 0)
	{
		show_players(cw);
		status = corewar_play(cw);
	}
	ft_quit(cw);
	corewar_free(&cw);
	return ((status >= 0) ? 0 : status);
}