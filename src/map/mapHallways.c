#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

void drawHallway(NormalRoom * newRoom, NormalRoom * room, Tile ** map,int cols, int rows) {
  // Function scope variables
  int distance = calculateDistance(newRoom,room,0,'x'); // distance between room doors in manhattan distance
  char axis = 'x'; // gives the axis 'x' || 'y' 
  int axisSwap = 0; // 1 = Hallway axis changes | 0 = Hallway axis didn't change
  int isFirst = 1; // 1 = It's the first call of the function drawHallway() // 0 = != 1st call
  drawDoor(newRoom,map);
  drawRoom(*newRoom,map,cols,rows);

  while (distance != 0) {
    
    // Loop scope variables
    int xDist = calculateDistanceXAxis(&newRoom->door,&room->door,0); // Distance in x axis in manhattan distance
    int yDist = calculateDistanceYAxis(&newRoom->door,&room->door,0); // Distance in y axis in manhattan distance
    int displacement = 1; // The displacement to calculate the new distance

    // This is to place the last hallway tile 1 pixel away in x/y 
    if (newRoom->doorAxis == 'x') {
      yDist--;
    } else {
      xDist--;
    }

    if ((yDist + xDist) == 0) break;

    mvprintw(2,5,"xDist: %d | yDist: %d | xDist + yDist = %d",xDist,yDist,((xDist + yDist)));


    int sizeForbiddenToPass = 2;
    char blocks[] = {'#','.'};

    // this code is remediating in the case the hallway has a wall in front of it
    for (int i = 0; i < sizeForbiddenToPass; i++) {
      
      // fix a bug -> the first iteration the hallway will be inside a wall, then the code needs to jump 1 iteration
      if (isFirst == 1) {
        // buildWalls(room,axis,isFirst,axisSwap);
        if (axis == 'x') {
          isWall(&room->door,1,'x',map);
          buildWalls(room,axis,isFirst,axisSwap,map);
        } else if (axis == 'y') {
          isWall(&room->door,1,'y',map);
          buildWalls(room,axis,isFirst,axisSwap,map);
        }
        isFirst = 0;
        break;
      }


      if ((map[room->door.y][room->door.x + 1].ch == blocks[i] || map[room->door.y][room->door.x - 1].ch == blocks[i] || xDist == 0) && axis == 'x') {
        // function to check which way is faster
        int distanceX = calculateDistanceXAxis(&newRoom->door,&room->door,0);
        int newDistanceX = calculateDistanceXAxis(&newRoom->door,&room->door,1);

        if (xDist == 0) {
          axis = 'y';
          axisSwap = 1;
        } else if (distanceX > newDistanceX) {
          room->door.x += 1;
          if (isFloor(&room->door,map) == 1) {
            room->door.x -= 1;
          } else if (map[room->door.y][room->door.x].ch == '#') {
            map[room->door.y][room->door.x].ch = '+';
            map[room->door.y][room->door.x].color = COLOR_PAIR(2);
          }
        } else if (distanceX < newDistanceX) {
          room->door.x -= 1;
          if (isFloor(&room->door,map) == 1) {
            room->door.x += 1;
          } else if (map[room->door.y][room->door.x].ch == '#') {
            map[room->door.y][room->door.x].ch = '+';
            map[room->door.y][room->door.x].color = COLOR_PAIR(2);
          }
        }



      } else if (( map[room->door.y + 1][room->door.x].ch == blocks[i] || map[room->door.y - 1][room->door.x].ch == blocks[i] || yDist == 0) && axis == 'y') {
        // function to check which way is faster
        int distanceY = calculateDistanceYAxis(&newRoom->door,&room->door,0);
        int newDistanceY = calculateDistanceYAxis(&newRoom->door,&room->door,1);

        if (yDist == 0) {
          axis = 'x';
          axisSwap = 1;

        } else if (distanceY > newDistanceY) {
          room->door.y += 1;
          if (isFloor(&room->door, map) == 1) {
            room->door.y -= 1;
            map[room->door.y][room->door.x].color = COLOR_PAIR(2);
          } else if (map[room->door.y][room->door.x].ch == '#') {
            map[room->door.y][room->door.x].ch = '+';
            map[room->door.y][room->door.x].color = COLOR_PAIR(2);
          }
        } else if (distanceY < newDistanceY) {
          room->door.y -= 1;
          if (isFloor(&room->door, map) == 1) {
            room->door.y += 1;
            map[room->door.y][room->door.x].color = COLOR_PAIR(2);
          } else if (map[room->door.y][room->door.x].ch == '#') {
            map[room->door.y][room->door.x].ch = '+';
            map[room->door.y][room->door.x].color = COLOR_PAIR(2);
          }
        }
      }
    }




    int newDistance = calculateDistance(newRoom,room,displacement,axis); // The new distance to see if the distance with axis + 1 will increase or decrease, if distance > newDistance, the distance between two doors decreased and the hallway have to go this way, otherwise, go to the opposite way



    if (distance < newDistance) {
      // if distance increased, go to the opposite way
      if (axis == 'x') {
        // go left
        room->door.x -= 1;
        if (isFloor(&room->door, map) != 0) 
        map[room->door.y][room->door.x].ch = '+';
        map[room->door.y][room->door.x].color = COLOR_PAIR(2);
      } else if (axis == 'y') {
        // go up
        room->door.y -= 1;
        if (isFloor(&room->door, map) != 0) 
        map[room->door.y][room->door.x].ch = '+';
       map[room->door.y][room->door.x].color = COLOR_PAIR(2);
      }
    } else if (distance > newDistance) {
      if (axis == 'x') {
        // go right
        room->door.x += 1;
        if (isFloor(&room->door, map) != 0) 
        map[room->door.y][room->door.x].ch = '+';
        map[room->door.y][room->door.x].color = COLOR_PAIR(2);
      } else if (axis == 'y') {
        // go down
        room->door.y += 1;
        if (isFloor(&room->door, map) != 0)
        map[room->door.y][room->door.x].ch = '+';
        map[room->door.y][room->door.x].color = COLOR_PAIR(2);
      }
    }

    buildWalls(room,axis,isFirst,axisSwap,map);
    axisSwap = 0;
    distance = calculateDistance(newRoom,room,0,axis); // update the distance between two doors
  }
}



int isFloor(Position * door, Tile ** map) {
  if (map[door->y][door->x].ch == '.') {
    return 0;
  }
  return 1;
}



int isWall(Position * door, int displacement, char axis, Tile ** map) {
  if (axis == 'x') {

    if (map[door->y][door->x + displacement].ch == '#') {

      if (map[door->y + displacement][door->x].ch != '.' && map[door->y + displacement][door->x].ch != '#') {
        door->y += 1;
        map[door->y][door->x].ch = '+';
        map[door->y][door->x].color = COLOR_PAIR(2);
        return 0;
      } else if (map[door->y - displacement][door->x].ch != '.' && map[door->y - displacement][door->x].ch != '#') {
        door->y -= 1;
        map[door->y][door->x].ch = '+';
        map[door->y][door->x].color = COLOR_PAIR(2);
        return 0;
      }
    }

  } else if (axis == 'y') {

    if (map[door->y + displacement][door->x].ch == '#') {

      if (map[door->y][door->x + displacement].ch != '.' && map[door->y][door->x + displacement].ch != '#') {
        door->x += 1;
        map[door->y][door->x].ch = '+'; 
        map[door->y][door->x].color = COLOR_PAIR(2);
        
        return 0;
      } else if (map[door->y][door->x - displacement].ch  != '.' || map[door->y][door->x - displacement].ch  != '#') {
        door->x -= 1;
        map[door->y][door->x].ch = '+'; 
        map[door->y][door->x].color = COLOR_PAIR(2);
        
        return 0;
      }
    }
  }

  return 1;
}


// ############## Distance calc functions ####################


int calculateDistance(NormalRoom * newRoom, NormalRoom * room, int displacement, char axis) {
  if (axis == 'y') {
    int xDistance = calculateDistanceXAxis(&newRoom->door,&room->door,0);
    int yDistance = calculateDistanceYAxis(&newRoom->door,&room->door,displacement);

    return xDistance + yDistance;
  } else if (axis == 'x') {
    int xDistance = calculateDistanceXAxis(&newRoom->door,&room->door,displacement);
    int yDistance = calculateDistanceYAxis(&newRoom->door,&room->door,0);

    return xDistance + yDistance;
  }
  return 0;
}

int calculateDistanceXAxis(Position * newDoor, Position * door, int n) {
  return fabs((double) newDoor->x - ((double) door->x + n));
}

int calculateDistanceYAxis(Position * newDoor, Position * door, int n) {
  return fabs((double) newDoor->y  - ((double) door->y + n));
}