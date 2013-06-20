#ifndef TYPEDEF_H_INCLUDED
#define TYPEDEF_H_INCLUDED

#define LONGST  180 //经度计算起始点
#define LATST   90 //维度计算起始点
#define CIRVAL  3600000 //元周,毫秒为单位
#define EXT     ".mm" //地图后缀名

typedef unsigned char U1;
typedef unsigned short U2 ;
typedef unsigned int U4;
typedef char I1;
typedef short I2 ;
typedef int I4;
typedef char C1;


typedef enum{
    //e_mtype_g = 1,
   // e_mtype_h,
    e_mtype_i = 1,
    e_mtype_j,
    e_mtype_k,
    e_mtype_l,
    e_mtype_m,
    e_mtype_n,
    e_mtype_o,
    e_mtype_p,
    e_mtype_q,
} E_MTYPE;


typedef struct _LEVELDATA{
    E_MTYPE eLevel;
    C1 cLvFlag;
    I4 nMapBase;
    I4 nRangeW;
    I4 nRangeH;
    I4 nAreaW;
    I4 nAreaH;
} LEVELDATA;

typedef struct _AREAHEADER
{
    C1 data[100];
} AREAHEADER;

typedef struct _WORDGROUP
{
    struct LAYERHEADER
    {

    } tWordHeader;
    struct LAYERDATA
    {

    } tWordData;
} WORDGROUP;

typedef struct _LAYERGROUP
{
    struct LAYERHEADER
    {

    } tLayerHeader;
    struct LAYERDATA
    {

    } tLayerData;
} LAYERGROUP;

typedef struct _GRAPHGROUP
{
    struct GRAPHHEADER
    {

    } tShapeHeader;
    struct GRAPHDATA
    {
        struct GRAPHTYPE
        {

        } tGraphType;
    } tGraphData;
} GRAPHGROUP;

typedef struct _PLAMAREA
{
    AREAHEADER tAreaHeader; //区域Header
    U1 CharFlag; //文字标签
    WORDGROUP rWordGroup; //文字信息
    U1 LayerFlag; //Layer标签
    LAYERGROUP tLayerGroup; //Layer信息
    U1 GraphFlag; //图形标签
    GRAPHGROUP tGraphGroup; //图形信息
} PLAMAREA;

typedef struct _MAPTYPE
{
    U1 dataType;
    C1 dataChar;
    C1 maptypeChar;
    U1 seriesCode;
} MAPTYPE;

typedef struct _MAPHEADER
{
    C1 formatType[4];
    MAPTYPE tMapType;
    U1 formatVer;
    U1 formatCorr;
    U1 dataVer;
    U1 dataCorr;
    U1 wordCode;
    U1 areasumX;
    U1 areasumY;
    C1 reserved;
} MAPHEADER;

typedef struct _MANAGERPART
{
    U2 nMapCodeX;
    U2 nMapCodeY;
    U4 nDataOffset;
} MANAGERPART;

typedef struct _MAPDATA
{
    U4 nAreaInfo[16]; //区域信息*16
    U4 nAreaDataSize; //区域地图数据Size
    PLAMAREA tPlamArea[16]; //区域数据*16
} MAPDATA;

typedef struct _PLAMMAP
{
    MAPHEADER tMapHeader;
    MANAGERPART tMngPart[16]; //地图管理数据*16
    MAPDATA tMapData[16]; //地图数据*(n<16)
} PLAMMAP;

#endif // TYPEDEF_H_INCLUDED