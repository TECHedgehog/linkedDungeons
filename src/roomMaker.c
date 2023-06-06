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

t_seed	seedGenerator(t_seed s, int *mapSize)
{
	s.name = "seed";
	s.totalSpaces = mapSize[0] * mapSize[1];

	s.emptyPercentage = 33;
	s.emptyRatio = s.totalSpaces * s.emptyPercentage / 100;

	s.roomPercentage = 20;
	s.minRooms = s.totalSpaces * s.roomPercentage / 100;
	
	srand((unsigned) time(NULL));
	
	s.roomsAmount = (rand() % ((s.totalSpaces - s.emptyRatio) - s.minRooms + 1)) + s.minRooms;
	
	s.emptySpaces = s.totalSpaces - s.roomsAmount;

	s.ramification = rand() % 76;

	return (s);
}

int		checkIfRoom(t_room **map,int direction, int *mapSize)
{
	(void)mapSize;
	int	x = 0;
	int	y = 0;

	switch (direction)
	{
	case 0:
		x = (*map)->x - 1;
		y = (*map)->y;
		if (x < 0)
			return (-1);
		else if ((*map)->mapS[x][y] != '.')
			return (-1);
		break;
	case 1:
		x = (*map)->x + 1;
		y = (*map)->y;
		if (x >= mapSize[0])
			return (-1);
		else if ((*map)->mapS[x][y] != '.')
			return (-1);
		break;
	case 2:
		x = (*map)->x;
		y = (*map)->y + 1;
		if (y >= mapSize[1])
			return (-1);
		else if ((*map)->mapS[x][y] != '.')
			return (-1);
		break;
	default:
		x = (*map)->x;
		y = (*map)->y - 1;
		if (y < 0)
			return (-1);
		else if ((*map)->mapS[x][y] != '.')
			return (-1);
	}
	return (1);
}

int		directionManager(t_room **map, int direction, int createOnSame, int *mapSize)
{
	int dAux = direction;

	if ((*map)->nextUP != NULL && (*map)->nextDW != NULL 
	&& (*map)->nextRT != NULL && (*map)->nextLF != NULL)
		return (-1);
	if (checkIfRoom(map, direction, mapSize) == -1)
		return (-3);
	switch (direction)
	{
		case 0:
			if ((*map)->nextUP != NULL)
			{
				while (dAux == direction)
					dAux = rand() % 4;
				directionManager(map, dAux, createOnSame, mapSize);
			}
			else
				addRoomUp(map, createOnSame);
			break;
		case 1:
			if ((*map)->nextDW != NULL)
			{
				while (dAux == direction)
					dAux = rand() % 4;
				directionManager(map, dAux, createOnSame, mapSize);
			}
			else
				addRoomDown(map, createOnSame);
			break;
		case 2:
			if ((*map)->nextRT != NULL)
			{
				while (dAux == direction)
					dAux = rand() % 4;
				directionManager(map, dAux, createOnSame, mapSize);
			}
			else
				addRoomRight(map, createOnSame);
			break;
		default:
			if ((*map)->nextLF != NULL)
			{
				while (dAux == direction)
					dAux = rand() % 4;
				directionManager(map, dAux, createOnSame, mapSize);
			}
			else
				addRoomLeft(map, createOnSame);
	}
	return (1);
}

void	generateRooms(t_room **map, int *mapSize)
{
	t_seed	s;
	int		roomCount = 0;
	int		direction;
	int		createOnSame;
	int		notRepeated = 1;
	int		loopLock = 0;
	//int h = 0;

	s = seedGenerator(s, mapSize);

	srand((unsigned) time(NULL));

	while (roomCount < s.roomsAmount - 1)
	{	
		loopLock++;
		createOnSame = (rand() % 101 <= s.ramification && notRepeated > 0) ? 1 : 0;
		direction = rand() % 4;
		notRepeated = directionManager(map, direction, createOnSame, mapSize);
		if (notRepeated > 0)
		{
			roomCount++;
			loopLock = 0;
		}
		else if (loopLock > 2)
			*map = (*map)->start;
		printMap(*map, mapSize);
		//printf("%d\n", h);
		system("sleep 0.5");
	}
	printf("%d\n\n", s.roomsAmount);
}

int		addRoomUp(t_room **map, int createOnSame)
{
	t_room *newRoom;

	if ((newRoom = malloc(sizeof(t_room))) == NULL)
		return (-1);

	newRoom->n = (*map)->n + 1;
	newRoom->x = (*map)->x - 1;
	newRoom->y = (*map)->y;

	newRoom->mapS = (*map)->mapS;
	newRoom->mapS[newRoom->x][newRoom->y] = 'U';
	newRoom->is_walkable = 1;

	newRoom->nextUP = NULL;
	newRoom->nextDW = *map;
	newRoom->nextRT = NULL;
	newRoom->nextLF = NULL;

	newRoom->start = (*map)->start;

	newRoom->roomsNumber = (*map)->roomsNumber++;
	newRoom->clue = "Dare to pass!";

	(*map)->nextUP = newRoom;

	if (createOnSame)
		return (1);
	*map = newRoom;
	return (1);
}

int		addRoomDown(t_room **map, int createOnSame)
{
	t_room *newRoom;

	if ((newRoom = malloc(sizeof(t_room))) == NULL)
		return (-1);

	newRoom->n = (*map)->n + 1;
	newRoom->x = (*map)->x + 1;
	newRoom->y = (*map)->y;

	newRoom->mapS = (*map)->mapS;
	newRoom->mapS[newRoom->x][newRoom->y] = 'D';
	newRoom->is_walkable = 1;

	newRoom->nextUP = *map;
	newRoom->nextDW = NULL;
	newRoom->nextRT = NULL;
	newRoom->nextLF = NULL;

	newRoom->start = (*map)->start;

	newRoom->roomsNumber = (*map)->roomsNumber++;
	newRoom->clue = "Dare to pass!";

	(*map)->nextDW = newRoom;

	if (createOnSame)
		return (1);
	*map = newRoom;
	return (1);
}

int		addRoomRight(t_room **map, int createOnSame)
{
	t_room *newRoom;

	if ((newRoom = malloc(sizeof(t_room))) == NULL)
		return (-1);

	newRoom->n = (*map)->n + 1;
	newRoom->x = (*map)->x;
	newRoom->y = (*map)->y + 1;

	newRoom->mapS = (*map)->mapS;
	newRoom->mapS[newRoom->x][newRoom->y] = 'R';
	newRoom->is_walkable = 1;

	newRoom->nextUP = NULL;
	newRoom->nextDW = NULL;
	newRoom->nextRT = NULL;
	newRoom->nextLF = *map;

	newRoom->start = (*map)->start;

	newRoom->roomsNumber = (*map)->roomsNumber++;
	newRoom->clue = "Dare to pass!";

	(*map)->nextRT = newRoom;

	if (createOnSame)
		return (1);
	*map = newRoom;
	return (1);
}

int		addRoomLeft(t_room **map, int createOnSame)
{
	t_room *newRoom;

	if ((newRoom = malloc(sizeof(t_room))) == NULL)
		return (-1);

	newRoom->n = (*map)->n + 1;
	newRoom->x = (*map)->x;
	newRoom->y = (*map)->y - 1;

	newRoom->mapS = (*map)->mapS;
	newRoom->mapS[newRoom->x][newRoom->y] = 'L';
	newRoom->is_walkable = 1;

	newRoom->nextUP = NULL;
	newRoom->nextDW = NULL;
	newRoom->nextRT = *map;
	newRoom->nextLF = NULL;

	newRoom->start = (*map)->start;

	newRoom->roomsNumber = (*map)->roomsNumber++;
	newRoom->clue = "Dare to pass!";

	(*map)->nextLF = newRoom;

	if (createOnSame)
		return (1);
	*map = newRoom;
	return (1);
}