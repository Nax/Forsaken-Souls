
#ifndef LINK_HPP
# define LINK_HPP

/**
 * Describes a link between levels, including each end's map and chunk.
 */
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

#endif // !LINK_HPP
