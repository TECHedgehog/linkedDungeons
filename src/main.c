/***************************************************************
*                      Author: Eric Llaca                      *
*                      Source Language: c                      *
*                                                              *
*                   --- Code Description ---                   *
*                     _            _            _              *
*                    | |          | |          | |             *
*                    | | _  _ __  | | _____  __| |             *
*        888         | || || '_ \ | |/ / _ \/ _` |             *
*        888         | || || | | ||   <  __/ (_| |             *
*        888         |_||_||_| |_||_|\_\___|\__,_|             *
*    .d88888888  88888888b.  .d88b.  .d88b.  .d88b. 88888b.    *
*   d88" 888888  888888 "88bd88P"88bd8P  Y8bd88""88b888 "88b   *
*   888  888888  888888  888888  88888888888888  888888  888   *
*   Y88b 888Y88b 888888  888Y88b 888Y8b.    Y88..88P888  888   *
*    "Y88888 "Y88888888  888 "Y88888 "Y8888  "Y88P" 888  888   *
*                                888                           *
*                           Y8b d88P                           *
*                            "Y88P"                            *
***************************************************************/

#include "linked_dungeons.h"

void	initMap(t_room *map, int *mapSize)
{
	map->n = 0;
	map->x = mapSize[0] / 2;
	map->y = mapSize[1] / 2;
	map->is_walkable = 1;
	map->roomsNumber = 0;
	map->clue = NULL;
	map->mapS = NULL;
	map->nextUP = NULL;
	map->nextDW = NULL;
	map->nextRT = NULL;
	map->nextLF = NULL;
	map->start = map;

	map->mapS = malloc(mapSize[0] * sizeof(char*) + 1);

	int		i;
	int		j;

	for (i = 0; i < mapSize[0]; i++) {
		map->mapS[i] = malloc(mapSize[1] * sizeof(char) + 1);
		for (j = 0; j < mapSize[1]; j++)
			map->mapS[i][j] = '.';
		map->mapS[i][j] = 0;
	}
	map->mapS[map->x][map->y] = 'O';
	map->mapS[i] = NULL;
}

void	printMap(t_room *map, int *mapSize)
{
	int		i;
	int		j;

	for (i = 0; i < mapSize[0]; i++)
	{
		for (j = 0; j < mapSize[1]; j++)
			printf(" %c ", map->mapS[i][j]);
		printf("\n");
	}
	printf("\n");
}

void	createWindow()
{
	InitWindow(500, 500, "Template-4.0.0");

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
    
        EndDrawing();
    }
    
    CloseWindow();
}

int		main(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	createWindow();
	/* t_room	*map;

	//printf("%d - %s", argc, argv[1]);

	map = malloc(sizeof(t_room));

	int		mapSize[2];
	int		playerPos[2];
	int		i = 0;

	mapSize[0] = 15;
	mapSize[1] = 15;
	playerPos[0] = 0;
	playerPos[1] = 0;

	(void)playerPos;
	(void)i;

	//printGameTitle();
	//initMap(map, mapSize);
	//generateRooms(&map, mapSize);

	//printMap(map, mapSize);

	//map = map->start;
	//freeMaps(map, mapSize); */
	return (0);
}