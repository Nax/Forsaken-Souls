#include "IEntity.hpp"

using namespace lm;

const EntityData gEntityData[] =
{
	{
		"Cross",
		ImageId::Cross,
		42,
		21,
		1.0,
		100,
		200,
		0,
		4,
		10,
		 // Begin Bounding box
		{
			{23, 48},{25, 44}, {26, 26}, {25, 46}, {19, 48}
		},
		// End Bounding box
		// Start Transitions
		{
			// Begin From Stand
			{
				{},
				{0, 14},
				{},
				{},
				{}
			},
			// End From stand
			{

			},
		},
		// End Transitions
		// Start Animations
		{
			{32, 5}, {15, 16}, {}, {}, {}
		}
		// End Animations
	}
};