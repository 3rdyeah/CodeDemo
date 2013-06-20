#ifndef __PLAMADP_H__
#define __PLAMADP_H__

#include <stdarg.h>
#include <malloc.h>
#include <memory.h>
#include "typedef.h"

#define PlamPrint printf

I4 g_alloc_sum = 0;

void *PlamMalloc(I4 nLen)
{
    g_alloc_sum++;
    return (void *)malloc(nLen);
}

void PlamFree(void *pBuffer)
{
    if (NULL != pBuffer)
    {
        g_alloc_sum--;
        free(pBuffer);
    }
}

void PlamLogOut(C1* format, ... )
{
	//SYSTEMTIME tiLogTime;
	//mimoU8 szSysTime[11] = {0};
	C1 buff[1024] = {0};

	va_list ap;
	va_start(ap, format);
	vsnprintf(buff, sizeof(buff), format, ap);
	va_end(ap);

	FILE* hLogFIle = fopen("./Log/PlamLog.log", "a+");
	if (hLogFIle)
	{
	    	fwrite(format, 1, strlen(format) + 1, hLogFIle);
	}
	fclose(hLogFIle);
};

#endif //__PLAMADP_H__