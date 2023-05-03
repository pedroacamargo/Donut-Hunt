#ifndef __MAPHALLWAYS_H__
#define __MAPHALLWAYS_H__

void drawHallway(NormalRoom * newRoom, NormalRoom * room);

int isFloor(Position * door);

int isWall(Position * door, int displacement, char axis);



// These functions will calculate the distance between 2 doors in x axis or y axis
int calculateDistanceXAxis(Position * newDoor, Position * door, int n);
int calculateDistanceYAxis(Position * newDoor, Position * door, int n);


// This funcion will give the distance (each pixel = 1) in manhattan distance
int calculateDistance(NormalRoom * newRoom, NormalRoom * room, int displacement, char axis);

#endif