#include "CodeDemo.h"
#include "PlamAdp.h"
using namespace std;

#define MAPPATH_LEN 30

LEVELDATA* GetLevelData(E_MTYPE eLevel)
{
    LEVELDATA* leveldata = (LEVELDATA*)PlamMalloc(sizeof(LEVELDATA));
    memset(leveldata, 0, sizeof(LEVELDATA));
    switch(eLevel)
    {
        case 1:
            leveldata->cLvFlag = 'i';
            leveldata->nMapBase = 6250;
            leveldata->nRangeW = 112500;
            leveldata->nRangeH = 75000;
            break;
        case 2:
            leveldata->cLvFlag = 'j';
            leveldata->nMapBase = 25000;
            leveldata->nRangeW = 450000;
            leveldata->nRangeH = 300000;
            break;
        case 3:
            leveldata->cLvFlag = 'k';
            leveldata->nMapBase = 100000;
            leveldata->nRangeW = 1800000;
            leveldata->nRangeH = 1200000;
            break;
        case 4:
            leveldata->cLvFlag = 'l';
            leveldata->nMapBase = 200000;
            leveldata->nRangeW = 3600000;
            leveldata->nRangeH = 2400000;
            break;
        case 5:
            leveldata->cLvFlag = 'm';
            leveldata->nMapBase = 400000;
            leveldata->nRangeW = 7200000;
            leveldata->nRangeH = 4800000;
            break;
        case 6:
            leveldata->cLvFlag = 'n';
            leveldata->nMapBase = 800000;
            leveldata->nRangeW = 14400000;
            leveldata->nRangeH = 9600000;
            break;
        case 7:
            leveldata->cLvFlag = 'o';
            leveldata->nMapBase = 1600000;
            leveldata->nRangeW = 28800000;
            leveldata->nRangeH = 19200000;
            break;
        case 8:
            leveldata->cLvFlag = 'p';
            leveldata->nMapBase = 6400000;
            leveldata->nRangeW = 115200000;
            leveldata->nRangeH = 76800000;
            break;
        case 9:
            leveldata->cLvFlag = 'q';
            leveldata->nMapBase = 25600000;
            leveldata->nRangeW = 460800000;
            leveldata->nRangeH = 307200000;
            break;
        default:
            break;
    }
    leveldata->nAreaW = leveldata->nRangeW / 4;
    leveldata->nAreaH = leveldata->nRangeH / 4; 
    return leveldata;
}

C1* GetMapFilePath(E_MTYPE eLevel, I4 nAreaX, I4 nAreaY)
{
    C1* szMapPath = (C1*)PlamMalloc(MAPPATH_LEN);
    if (!szMapPath)
    {
        PlamFree(szMapPath);
        szMapPath = NULL;
        return NULL;
    }
    memset(szMapPath, 0, MAPPATH_LEN);

    LEVELDATA* tLevelData = GetLevelData(eLevel);
    I4 nMapCodeX = nAreaX / 4;
    I4 nMapCodeY = nAreaY / 4;
    
    sprintf(szMapPath, 
        "./files/%c00/%04x/%04x/%04x%04x%s", 
        tLevelData->cLvFlag, 
        nMapCodeX / 16, 
        nMapCodeY / 16, 
        nMapCodeX / 4, 
        nMapCodeY / 4, 
        EXT);

    PlamFree(tLevelData);
    tLevelData = NULL;
    return szMapPath;
}

C1* GetMapPath(E_MTYPE eLevel, I4 nLongitude, I4 Latitude)
{
    C1* szMapPath = (C1*)PlamMalloc(MAPPATH_LEN);
    if (!szMapPath)
    {
        PlamFree(szMapPath);
        szMapPath = NULL;
        return NULL;
    }
    memset(szMapPath, 0, MAPPATH_LEN);

    LEVELDATA* tLevelData = GetLevelData(eLevel);
    I4 nMapCodeX = ((LONGST + nLongitude) * CIRVAL) / tLevelData->nRangeW + 1;
    I4 nMapCodeY = ((LATST + Latitude) * CIRVAL) / tLevelData->nRangeH + 1;

    sprintf(szMapPath, 
        "./files/%c00/%04x/%04x/%04x%04x%s", 
        tLevelData->cLvFlag, 
        nMapCodeX / 16, 
        nMapCodeY / 16, 
        nMapCodeX / 4, 
        nMapCodeY / 4, 
        EXT);

    PlamFree(tLevelData);
    tLevelData = NULL;
    return szMapPath;
}

//void GetMapData(E_MTYPE eLevel, I4 nLongitude, I4 Latitude)
void GetMapData(E_MTYPE eLevel, I4 nAreaX, I4 nAreaY)
{
    I4 nFileSize = -1;
    I4 nRet = 0;
    I4 nSeek = 0;
    C1* szMapPath = NULL;
    C1* szFilePath = NULL;
    C1* pDataBuf = NULL;
    PLAMAREA* tPlamArea = NULL; //区域结构*16 = 地图数据
    MAPHEADER* tMapHeader = NULL; //地图文件头
    MANAGERPART* tMngPart = NULL; //地图管理数据
    MAPDATA* tMapData = NULL; //地图数据
    FILE* hMapFile = NULL;

    do{
        //if (!(szFilePath = GetMapFilePath(eLevel, nLongitude, Latitude)))
        if (!(szFilePath = GetMapFilePath(eLevel, nAreaX, nAreaY)))
        {
            PlamPrint("GetMapPath Failed\n");
            break;
        }
        PlamPrint("GetMapPath  = %s\n", szFilePath);
        if (!(hMapFile = fopen(szMapPath, "rb")))
        {
            PlamPrint("Open Map File Failed\n");
            break;
        }
        PlamPrint("Open Map File Succeed\n");
        struct stat stbuf;
        if (stat(szMapPath, &stbuf) == 0) 
        {
            nFileSize = stbuf.st_size;
            PlamPrint("%d\n", nFileSize);
        }
        else
        {
            PlamPrint("Get Map File Size Failed\n");
            break;
        }
        tMapHeader = (MAPHEADER*)PlamMalloc(sizeof(MAPHEADER));
        memset(tMapHeader, 0, sizeof(MAPHEADER));

        pDataBuf = (C1*)PlamMalloc(nFileSize);
        memset(pDataBuf, 0, nFileSize);
        fread(pDataBuf, 1, nFileSize, hMapFile);
        cout<<&pDataBuf<<endl;
    }while(0);

    if (szMapPath)
    {
        PlamFree(szMapPath);
        szMapPath = NULL;
    }  
    if (pDataBuf)
    {
        PlamFree(pDataBuf);
        pDataBuf = NULL;
    }
    if (tMapHeader)
    {
        PlamFree(tMapHeader);
        tMapHeader = NULL;
    }
    if (hMapFile)
    {
        fclose(hMapFile);
        hMapFile = NULL;
    }
}

LAYERGROUP* GetLayer(PLAMAREA* tPlamArea)
{
    LAYERGROUP* tLayer = (LAYERGROUP*)PlamMalloc(sizeof(LAYERGROUP));
    memset(tLayer, 0, sizeof(LAYERGROUP));
    return 0;
}

GRAPHGROUP* GetGraph(PLAMAREA* tPlamArea)
{
    GRAPHGROUP* tGraph = (GRAPHGROUP*)PlamMalloc(sizeof(GRAPHGROUP));
    memset(tGraph, 0, sizeof(GRAPHGROUP));
    return 0;
}

int main()
{    
    GetMapData(e_mtype_i, 12000, 20000);
    
    PlamPrint("%d\n", sizeof(PLAMMAP));
    PlamPrint("%d\n", g_alloc_sum);
    PlamPrint("helloworld\n");
    return 0;
}