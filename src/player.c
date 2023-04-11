#include "player.h"
#include <stdlib.h>

Player * playerSetUp() {
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));

  // playerMove(14,14,newPlayer);

  return newPlayer;
}