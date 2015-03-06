
#ifndef INNERLINK_HPP
# define INNERLINK_HPP

/**
 * Describes a level's inner links between maps.
 */
struct InnerLink
{
	struct Tip
	{
		int		map;
		int		chunk;
	};

	Tip start;
	Tip end;
};

#endif //!LINK_HPP
