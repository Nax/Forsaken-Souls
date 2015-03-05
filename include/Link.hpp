
#ifndef LINK_HPP
# define LINK_HPP

struct Link
{
	struct Tip
	{
		int		level;
		int		map;
		int		chunk;
	};

	Tip start;
	Tip end;
};

#endif //!LINK_HPP
