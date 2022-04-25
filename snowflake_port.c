/*
 * @file    snowflake_port.c
 * @brief   SnowFlack 软件包 Port 源文件
 * @author  2022alpha
 * @version v0.1.0 
 * @date    2022-03-18
*/
#include <rtthread.h>
#include <stdint.h>
#include "idgenerator.h"
#include "yitidhelper.h"
#include <sys/time.h>
#include "snowflake_port.h"

/**
 * @brief   雪花算法初始化
 * @param   workerid 机器码
 * @param   method 雪花计算方式
 * @param   worker_id_bit_length 机器码位长
 * @param   Seq_bit_length 序列号位长
 */
void snowflake_init(uint32_t workerid, uint8_t method, uint8_t worker_id_bit_length, uint8_t Seq_bit_length)
{
    /* 创建 IdGeneratorOptions 对象，在构造函数中输入 WorkerId */
    IdGeneratorOptions options = BuildIdGenOptions(workerid);

    /* 雪花计算方法，（1 - 漂移算法 | 2 - 传统算法）*/
    if (method == 1 || method == 2)
    {
        options.Method = method;
    }
    /* 机器码位长，默认值6，取值范围 [1, 15] */
    if (worker_id_bit_length >= 1 && worker_id_bit_length <= 15)
    {
        options.WorkerIdBitLength = worker_id_bit_length;
    }
    /* 序列数位长，默认值6，取值范围 [3, 21] */
    if (Seq_bit_length >= 3 && Seq_bit_length <= 21)
    {
        options.SeqBitLength = Seq_bit_length;
    }

    /* 保存参数 */
    SetIdGenerator(options);
}

/**
 * @brief   生成全局 ID
 * @return  ID
 */
uint64_t snowflake_get_id(void)
{
    /* 需要生成ID，调用 NextId 方法*/
    return NextId();
}

uint32_t * snowflake_malloc(uint32_t size)
{
    uint32_t * ptr;
    ptr = rt_malloc(size);
    return ptr;
}

void snowflake_lock(void)
{
    // rtthread
    //单线程运行可不考虑
}

void snowflake_unlock(void)
{
    // rtthread
    //单线程运行可不考虑
}

/**
 * @brief   获取当前时间，供算法使用
 * @return  当前时间
 */
uint64_t GetSystemCurrentMicroTime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((uint64_t)tv.tv_sec * 1000000 + tv.tv_usec);
 }
