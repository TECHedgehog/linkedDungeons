#ifndef LINKED_DUNGEONS_H
# define LINKED_DUNGEONS_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <time.h>
# include <raylib.h>
# include <raymath.h>
# include <stdbool.h>

typedef struct	s_seed
{
// Optional. Will be useful for saving maps by name.
	char	*name;
	int		seed;
// Total number of spaces available in map to create rooms (mapSize X * mapSizeY)
	int		totalSpaces;
// Total number of rooms generated in the map. Never exceeds total number of spaces less emptyRatio.
	int		roomsAmount;
// Percentage of empty spaces in map over totalSpaces.
	int		emptyPercentage;
// Amount of minimum empty map spaces. Based on emptyPercentage over totalSpaces.
	int		emptyRatio;
// Amount of spaces left empty after room generation.
	int		emptySpaces;
// Percentage of rooms over totalSpaces.
	int		roomPercentage;
// Minimum amount of rooms generated based on roomPercentage over totalSpaces.
	int		minRooms;
// Chance of creating new branches in map (Percentage).
	int		ramification;
}				t_seed;


typedef struct	s_room
{
// Room number in order of creation.
	int		n;
// Coordinate X in map.
	int		x;
// Coordinate Y in map.
	int		y;
	int		is_walkable;
// Total number of rooms created in map.
	int		roomsNumber;
// Small clue for puzzle like levels. Multiple usages.
	char	*clue;
// Map represantation in 2D array (X, Y).
	char	**mapS;
// Pointer to room heading North.
	void	*nextUP;
// Pointer to room heading South.
	void	*nextDW;
// Pointer to room heading East.
	void	*nextRT;
// Pointer to room heading West.
	void	*nextLF;
	void	*start;
}				t_room;

		// Initializes origin map Node. Coordinates X and Y will be the
		// center of map based on mapSize. Every map space will be set to '0'
void	initMap(t_room *map, int *mapSize);
void	printMap(t_room *map, int *mapSize);
void	freeMaps(t_room *map, int *mapSize);
void	printGameTitle();
void	generateRooms(t_room **map, int *mapSize);

int		addRoomUp(t_room **map, int createOnSame);
int		addRoomDown(t_room **map, int createOnSame);
int		addRoomRight(t_room **map, int createOnSame);
int		addRoomLeft(t_room **map, int createOnSame);

#endif