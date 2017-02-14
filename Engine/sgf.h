#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"


int getCoordsFromLetter(char letter);

char* getLetterFromCoords(int c);

void loadStonesCoordinates(char* coords);

void loadSaveGame(const char* path);

char* getPlayerCoordinatesAsString(Player p);

void writeSaveGame(const char* path);

char* ajout_char(char *chaine, size_t n, char c);
