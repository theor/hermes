//
// Created by theor on 2022-07-29.
//


#include "Arduino.h"
#include "SDL.h"

unsigned long millis() { return SDL_GetPerformanceCounter()*1000 / (double)SDL_GetPerformanceFrequency(); }

unsigned long random() { return rand(); }

unsigned long random(long max) { return rand() % max; }

unsigned long random(long min, long max) { return min + (rand() % (max - min)); }
