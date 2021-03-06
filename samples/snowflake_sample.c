/*
 * @file    snowflake_port.c
 * @brief   SnowFlack 软件包示例文件
 * @author  2022alpha
 * @version v0.1.0 
 * @date    2022-03-18
*/

/*
 * 版权属于：yitter(yitter@126.com)
 * 代码翻译：amuluowin
 * 代码修订：yitter
 */

#include <stdio.h>
#include <stdbool.h>
#include "snowflake.h"

const int GenIdCount = 5000;
const bool multiThread = false;     //不使用多线程
const int threadCount = 50;         //多线程
const int method = 1;
const int workerid = 1;

/**
 * @brief   多线程生成ID
 */
void RunMultiThread(void)
{
    for (int i = 0; i < GenIdCount / threadCount; i++)
    {
        uint64_t id = snowflake_get_id();
        printf("ID: %lld\n", id);
    }
}

/**
 * @brief   单线程生成ID
 */
void RunSingle(void)
{
    for (int i = 0; i < GenIdCount; i++) // 
    {
        uint64_t id = snowflake_get_id();
        printf("ID: %lld\n", id);
    }
}

/**
 * @brief  生成ID
 */
int smowflake_sample(void) 
{
    snowflake_init(workerid, method,0,0);
    if (multiThread)
    {
        //创建多线程
        //单线程使用，暂无
    } 
    else 
    {
        RunSingle();
    }
    return 0;
}
