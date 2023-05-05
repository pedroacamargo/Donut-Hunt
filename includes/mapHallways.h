#ifndef __MAPHALLWAYS_H__
#define __MAPHALLWAYS_H__

// The main function for the hallways creation, every auxiliar function created inside this file is performing some role in this function
// If you give 2 rooms, the 2 rooms will be connected
void drawHallway(NormalRoom * newRoom, NormalRoom * room, Tile ** map);

// This function will return 0 if in the given tile there is a floor ('.'), otherwise will return 1.
// door -> Needs to be a Position typedef
int isFloor(Position * door);

// This function is in case the first iteration and the door is in the top/bottom of the room, if this happens, 
// the door will go a pixel above/below and undo the repositioning of the door in X axis, 
// just to don't overwrite the room walls and happens to have a hallway inside the wall.
int isWall(Position * door, int displacement, char axis);



int calculateDistanceXAxis(Position * newDoor, Position * door, int n);
int calculateDistanceYAxis(Position * newDoor, Position * door, int n);
// These functions will calculate the distance between 2 doors in x axis or y axis


// This funcion will give the distance (each pixel = 1) in manhattan distance
int calculateDistance(NormalRoom * newRoom, NormalRoom * room, int displacement, char axis);

#endif