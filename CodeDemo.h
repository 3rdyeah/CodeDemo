#ifndef CODEDEMO_H_INCLUDED
#define CODEDEMO_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <sys/stat.h>
#include <iostream>
#include "typedef.h"

#define PLAM_DEBUG_MODE (1)
#define GET_FILE_BY_COOR (0)

LEVELDATA* GetLevelData(E_MTYPE eLevel);
LAYERGROUP* GetLayer(PLAMAREA* tPlamArea);
GRAPHGROUP* GetGraph(PLAMAREA* tPlamArea);
PLAMAREA*	GetPlamArea(FILE hMapFile, I4 nAreaX, I4 nAreaY);

#if GET_FILE_BY_COOR
C1* GetMapFilePath(E_MTYPE eLevel, I4 nLongitude, I4 Latitude);
void GetMapData(E_MTYPE eLevel, I4 nLongitude, I4 Latitude);
#else
C1* GetMapFilePath(E_MTYPE eLevel, I4 nAreaX, I4 nAreaY);
void GetMapData(E_MTYPE eLevel, I4 nAreaX, I4 nAreaY);
#endif

#if PLAM_DEBUG_MODE
#define PLAM_LOG_O PlamLogOut
#else
#define PLAM_LOG_O
#endif

#endif // CODEDEMO_H_INCLUDED