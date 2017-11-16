/**********************************************************************
* 版权所有 (C)2017, Renleilei
*
* 文件名称：DelExpiredFiles.c
* 文件标识：无
* 内容摘要：创建现场删除过期文件
* 其它说明：无
* 当前版本：V1.0
* 作    者：Renleilei
* 完成日期：20170729
*
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// 重定义数据类型
typedef signed   int    INT32;
typedef unsigned int    UINT32;
typedef unsigned char   UINT8;

// 函数声明
void Sleep(UINT32 iCountMs);
void DelExpiredFiles(UINT8 *pszFileSaveDir, UINT32 iFileSaveDays);
INT32 main();


/**********************************************************************
* 功能描述：主函数
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：无
* 修改日期        版本号     修改人            修改内容
* -------------------------------------------------------------------
* 20170806        V1.0      Renleilei          创建
* 20170806        V1.1      Renleilei          Modified
***********************************************************************/
INT32 main()
{   
    UINT8  szFileSaveDir[1024] = {0};
    UINT32 iFileSaveDays       = 0;

    // 获取过期文件目录
    snprintf(szFileSaveDir, sizeof(szFileSaveDir) - 1, "%s/TestLog/", getenv("HOME"));

    // 获取过期文件保留天数
    iFileSaveDays = 10;

    while (1)
    {
        printf("==========Now, It's time to begin to delete expired files.===========\n"); 
        // 调用函数删除满足条件的过期文件
        DelExpiredFiles(szFileSaveDir, iFileSaveDays);

        Sleep(5 * 60 * 1000);    // 休息5分钟之后继续

        printf("Sleep 5 minutes, then go ahead.\n"); 
    }

    return 0;
}


/**********************************************************************
* 功能描述： 程序休眠
* 输入参数： iCountMs-休眠时间(单位:ms)
* 输出参数： 无
* 返 回 值： 无
* 其它说明： 无
* 修改日期       版本号       修改人        修改内容
* ------------------------------------------------------------------
* 20150729       V1.0     Zhou Zhaoxiong     创建
********************************************************************/ 
void Sleep(UINT32 iCountMs)
{
    struct timeval t_timeout = {0};

    if (iCountMs < 1000)
    {
        t_timeout.tv_sec  = 0;
        t_timeout.tv_usec = iCountMs * 1000;
    }
    else
    {
        t_timeout.tv_sec  = iCountMs / 1000;
        t_timeout.tv_usec = (iCountMs % 1000) * 1000;
    }
    select(0, NULL, NULL, NULL, &t_timeout);    // 调用select函数阻塞程序
}


/*----------------------------------------------------
* 功能描述: 删除超期的过期文件
* 输入参数: pszFileSaveDir-过期文件保存目录
            iFileSaveDays-过期文件保存天数
* 输出参数: 无
* 返 回 值: 无
* 其他说明: 无
* 修改日期       版本号      修改人        修改内容
* ----------------------------------------------------
* 20150729       V1.0     Zhou Zhaoxiong     创建
----------------------------------------------------*/
void DelExpiredFiles(UINT8 *pszFileSaveDir, UINT32 iFileSaveDays)
{
    UINT8 szCmdBuf[1024] = {0};

    if (pszFileSaveDir == NULL)
    {
        printf("DelExpiredFiles: input parameter is NULL!\n");
        return;
    }

    // 执行shell命令删除过期文件(过期文件的后缀为.c)
    snprintf(szCmdBuf, sizeof(szCmdBuf) - 1, "find %s -name \"*.c\" -ctime +%d -exec rm -f {} \\;", pszFileSaveDir, iFileSaveDays);

    system(szCmdBuf);

    printf("DelExpiredFiles: exec command [%s] to delete expired files successfully!\n", szCmdBuf);
}

