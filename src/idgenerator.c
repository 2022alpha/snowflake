/*
 * 版权属于：yitter(yitter@126.com)
 * 开源地址：https://github.com/yitter/idgenerator
 */
#include <errno.h>
#include "idgenerator.h"

static inline uint64_t WorkerM1Id(void) 
{
    return WorkerM1NextId(_idGenerator->Worker);
}

static inline uint64_t WorkerM2Id(void) 
{
    return WorkerM2NextId(_idGenerator->Worker);
}

extern IdGenerator *GetIdGenInstance(void) 
{
    if (_idGenerator != NULL)
        return _idGenerator;
    else 
    {
        _idGenerator = (IdGenerator *)snowflake_malloc(sizeof(IdGenerator));
        _idGenerator->Worker = NewSnowFlakeWorker();
        return _idGenerator;
    }
}

/**
 * @brief   检测算法参数合法性并设定，选择计算方法
 * param    初始 options 参数
 */
extern void SetOptions(IdGeneratorOptions options) 
{
    if (GetIdGenInstance() == NULL) 
    {
        exit(1);
    }

    /* 1.BaseTime 时间初始值设定 */
    if (options.BaseTime == 0) 
    {
        /* 时间初始值 */
        _idGenerator->Worker->BaseTime = 1582136402000;
    } 
    else if (options.BaseTime < 631123200000 || options.BaseTime > uGetCurrentTime()) 
    {
        /* 时间初始值错误 */
        perror("BaseTime error.");
        exit(1);
    } 
    else 
    {
        _idGenerator->Worker->BaseTime = options.BaseTime;
    }

    /* 2.WorkerIdBitLength 机器码位长设定*/
    /* 机器码位长，默认值6，取值范围 [1, 15] */
    if (options.WorkerIdBitLength <= 0)
    {
        perror("WorkerIdBitLength error.(range:[1, 15])");
        exit(1);
    }
    /* 序列数位长+机器码位长不超过22 */
    if (options.SeqBitLength + options.WorkerIdBitLength > 22) 
    {
        perror("error：WorkerIdBitLength + SeqBitLength <= 22");
        exit(1);
    } 
    else 
    {
        _idGenerator->Worker->WorkerIdBitLength = options.WorkerIdBitLength <= 0 ? 6 : options.WorkerIdBitLength;
    }

    /* 3.WorkerId 机器码设定 */
    /* 计算最大可设定机器码 */
    uint32_t maxWorkerIdNumber = (1 << options.WorkerIdBitLength) - 1;
    if (maxWorkerIdNumber == 0) 
    {
        /* 默认最大机器码 */
        maxWorkerIdNumber = 63;
    }
    /* 机器码设定保护在允许范围内 */
    if (options.WorkerId < 0 || options.WorkerId > maxWorkerIdNumber) 
    {
        perror("WorkerId error. (range:[0, {2^options.WorkerIdBitLength-1]}");
        exit(1);
    } 
    else 
    {
        _idGenerator->Worker->WorkerId = options.WorkerId;
    }

    /* 4.SeqBitLength 设定序列数 */
    /* 序列数位长，默认值6，取值范围 [3, 21] */
    if (options.SeqBitLength < 2 || options.SeqBitLength > 21) 
    {
        perror("SeqBitLength error. (range:[3, 21])");
        exit(1);
    } 
    else 
    {
        _idGenerator->Worker->SeqBitLength = options.SeqBitLength <= 0 ? 6 : options.SeqBitLength;
    }

    /* 5.MaxSeqNumber 最大序列号 */
    /* 计算最大序列数 */
    uint32_t maxSeqNumber = (1 << options.SeqBitLength) - 1;
    if (maxSeqNumber == 0) 
    {
        /* 默认最大序列号 */
        maxSeqNumber = 63;
    }
    /* 最大序列号要在合理范围内 */
    if (options.MaxSeqNumber > maxSeqNumber) 
    {
        perror("MaxSeqNumber error. (range:[1, {2^options.SeqBitLength-1}]");
        exit(1);
    } 
    else 
    {
        _idGenerator->Worker->MaxSeqNumber = options.MaxSeqNumber <= 0 ? maxSeqNumber : options.MaxSeqNumber;
    }

    /* 6.MinSeqNumber 最小序列号 */
    /* 最小序列号要在合理范围内 */
    if (options.MinSeqNumber < 5 || options.MinSeqNumber > maxSeqNumber) 
    {
        perror("MinSeqNumber error. (range:[5, {options.MinSeqNumber}]");
        exit(1);
    } 
    else 
    {
        _idGenerator->Worker->MinSeqNumber = options.MinSeqNumber <= 0 ? 5 : options.MinSeqNumber;
    }

    /* 7.Others 最大漂移次数 */
    /* 默认2000，推荐范围 500-20000 */
    _idGenerator->Worker->TopOverCostCount = options.TopOverCostCount <= 0 ? 2000 : options.TopOverCostCount;
    _idGenerator->Worker->_TimestampShift =
            _idGenerator->Worker->WorkerIdBitLength + _idGenerator->Worker->SeqBitLength;
    _idGenerator->Worker->_CurrentSeqNumber = _idGenerator->Worker->MinSeqNumber;

    /* 雪花计算方式 */
    _idGenerator->Worker->Method = options.Method;
    /* 选择计算方法 */
    if (options.Method == 2) 
    {
        _idGenerator->NextId = WorkerM2Id;
    } 
    else 
    {
        _idGenerator->NextId = WorkerM1Id;
    }
}

