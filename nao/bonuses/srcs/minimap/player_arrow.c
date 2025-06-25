#include "liball.h"

static t_assist	player_arrow_setup(int x, int y, float angle, t_assist s)
{
	if (angle > 3 * PI / 4 && angle < 5 * PI / 4)
	{
		s.x = x + 6;
		s.y = y - 2;
		s.jstep = 0;
		s.istep = 1;
	}
	else if (angle > 5 * PI / 4 && angle < 7 * PI / 4)
	{
		s.x = x - 2;
		s.y = y + 6;
		s.jstep = 1;
		s.istep = 0;
	}
	else if (angle < PI / 4 || angle > 7 * PI / 4)
	{
		s.x = x - 6;
		s.y = y - 2;
		s.jstep = 0;
		s.istep = 1;
	}
	return (s);
}

void	player_arrow(t_img *fg, int x, int y, float angle)
{
	t_assist	s;
	int		i;
	int		j;

	if (angle > PI / 4 && angle < 3 * PI / 4)
	{
		s.x = x - 2;
		s.y = y - 6;
		s.jstep = 1;
		s.istep = 0;
	}
	else
		s = player_arrow_setup(x, y, angle, s);
	i = 0;
	j = 0;
	while (i < 4 && j < 4)
	{
		put_pixel(s.x + j, s.y + i, 0x00FF0000, fg);
		i += s.istep;
		j += s.jstep;
	}
}
