#include "Level.h"
Level::Level(b2World& World, Render* renderer)
{
	//First Layer of Platforms....................................................
	//initial platfrom on the first level.

	//platforms[0] = new Platform(50, 600, 100, 10, World, renderer, 1);
	platforms[1] = new Platform(150, 700, 100, 10, World, renderer, 1);
	platforms[2] = new Platform(250, 700, 100, 10, World, renderer, 1);
	platforms[3] = new Platform(349, 700, 100, 10, World, renderer, 1);
	platforms[4] = new Platform(449, 700, 100, 10, World, renderer, 1);
	platforms[5] = new Platform(549, 700, 100, 10, World, renderer, 1);
	platforms[6] = new Platform(649, 700, 100, 10, World, renderer, 1);
	platforms[7] = new Platform(749, 700, 100, 10, World, renderer, 1);
	platforms[7] = new Platform(849, 700, 100, 10, World, renderer, 1);
	platforms[7] = new Platform(949, 700, 100, 10, World, renderer, 1);
	platforms[7] = new Platform(1049, 700, 100, 10, World, renderer, 1);



	//platforms[0] = new Platform(50, 600, 100, 10, World, renderer, 1);
	platforms[1] = new Platform(150, 600, 100, 10, World, renderer, 1);
	//platforms[2] = new Platform(1049, 600, 100, 10, World, renderer, 1);
	platforms[3] = new Platform(349, 600, 100, 10, World, renderer, 1);
	platforms[4] = new Platform(449, 600, 100, 10, World, renderer, 1);
	platforms[5] = new Platform(749, 600, 100, 10, World, renderer, 1);
	platforms[6] = new Platform(849, 600, 100, 10, World, renderer, 1);
	//platforms[7] = new Platform(949, 600, 100, 10, World, renderer, 1);

	//Access to second level 
	platforms[8] = new Platform(1050, 500, 100, 10, World, renderer, 1);

	//Second level................................................................

	//platforms[9] = new Platform(150, 400, 100, 10, World, renderer, 1);
	//platforms[10] = new Platform(250, 400, 100, 10, World, renderer, 1);
	//platforms[11] = new Platform(349, 400, 100, 10, World, renderer, 1);
	platforms[12] = new Platform(449, 400, 100, 10, World, renderer, 1);
	platforms[13] = new Platform(549, 400, 100, 10, World, renderer, 1);
	platforms[14] = new Platform(649, 400, 100, 10, World, renderer, 1);
	platforms[15] = new Platform(749, 400, 100, 10, World, renderer, 1);
	platforms[16] = new Platform(849, 400, 100, 10, World, renderer, 1);
	//platforms[17] = new Platform(949, 400, 100, 10, World, renderer, 1);

	//Access to level three.....................................................
	platforms[18] = new Platform(170, 300, 100, 10, World, renderer, 1);
	platforms[9] = new Platform(190, 400, 100, 10, World, renderer, 1);

	//Level Three...............................................................
	platforms[19] = new Platform(250, 200, 100, 10, World, renderer, 1);
	platforms[20] = new Platform(349, 200, 100, 10, World, renderer, 1);
	platforms[21] = new Platform(449, 200, 100, 10, World, renderer, 1);
	platforms[22] = new Platform(549, 200, 100, 10, World, renderer, 1);
	platforms[23] = new Platform(649, 200, 100, 10, World, renderer, 1);
	platforms[24] = new Platform(749, 200, 100, 10, World, renderer, 1);
	//platforms[25] = new Platform(849, 200, 100, 10, World, renderer, 1);
	//platforms[26] = new Platform(949, 200, 100, 10, World, renderer, 1);
	platforms[27] = new Platform(1030, 100, 100, 10, World, renderer, 1);
	platforms[25] = new Platform(930, 100, 100, 10, World, renderer, 1);
	platforms[26] = new Platform(1030, 200, 100, 10, World, renderer, 1);

	//Walls. These will act as walls for the level bounds and give the level a "Tower" feel.
	platforms[28] = new Platform(100, 0, 120, 800, World, renderer, 2);
	platforms[29] = new Platform(1150, 0, 120, 800, World, renderer, 2);
	platforms[28] = new Platform(100, -700, 120, 800, World, renderer, 2);
	platforms[29] = new Platform(1150, -700, 120, 800, World, renderer, 2);
	platforms[28] = new Platform(100, 800, 120, 800, World, renderer, 2);
	platforms[29] = new Platform(1150, 800, 120, 800, World, renderer, 2);
}
