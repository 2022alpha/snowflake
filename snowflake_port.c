/*
 * @file    snowflake_port.c
 * @brief   SnowFlack ����� Port Դ�ļ�
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
 * @brief   ѩ���㷨��ʼ��
 * @param   workerid ������
 * @param   method ѩ�����㷽ʽ
 * @param   worker_id_bit_length ������λ��
 * @param   Seq_bit_length ���к�λ��
 */
void snowflake_init(uint32_t workerid, uint8_t method, uint8_t worker_id_bit_length, uint8_t Seq_bit_length)
{
    /* ���� IdGeneratorOptions �����ڹ��캯�������� WorkerId */
    IdGeneratorOptions options = BuildIdGenOptions(workerid);

    /* ѩ�����㷽������1 - Ư���㷨 | 2 - ��ͳ�㷨��*/
    if (method == 1 || method == 2)
    {
        options.Method = method;
    }
    /* ������λ����Ĭ��ֵ6��ȡֵ��Χ [1, 15] */
    if (worker_id_bit_length >= 1 && worker_id_bit_length <= 15)
    {
        options.WorkerIdBitLength = worker_id_bit_length;
    }
    /* ������λ����Ĭ��ֵ6��ȡֵ��Χ [3, 21] */
    if (Seq_bit_length >= 3 && Seq_bit_length <= 21)
    {
        options.SeqBitLength = Seq_bit_length;
    }

    /* ������� */
    SetIdGenerator(options);
}

/**
 * @brief   ����ȫ�� ID
 * @return  ID
 */
uint64_t snowflake_get_id(void)
{
    /* ��Ҫ����ID������ NextId ����*/
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
    //���߳����пɲ�����
}

void snowflake_unlock(void)
{
    // rtthread
    //���߳����пɲ�����
}

/**
 * @brief   ��ȡ��ǰʱ�䣬���㷨ʹ��
 * @return  ��ǰʱ��
 */
uint64_t GetSystemCurrentMicroTime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((uint64_t)tv.tv_sec * 1000000 + tv.tv_usec);
 }
