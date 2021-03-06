/*
 * 版权属于：yitter(yitter@126.com)
 * 代码翻译：amuluowin
 * 代码修订：yitter
 * 开源地址：https://github.com/yitter/idgenerator
 */

#include "snowflake_m1.h"

static void EndOverCostAction(uint64_t useTimeTick, SnowFlakeWorker *worker);
static uint64_t NextOverCostId(SnowFlakeWorker *worker);
static uint64_t NextNormalId(SnowFlakeWorker *worker);
static uint64_t CalcId(SnowFlakeWorker *worker);
static uint64_t CalcTurnBackId(SnowFlakeWorker *worker);

static inline void EndOverCostAction(uint64_t useTimeTick, SnowFlakeWorker *worker) 
{
    if (worker->_TermIndex > 10000) 
    {
        worker->_TermIndex = 0;
    }
}

static inline uint64_t NextOverCostId(SnowFlakeWorker *worker) 
{
    uint64_t currentTimeTick = uGetCurrentTimeTick(worker);

    /* 进入新一个时间戳 */
    if (currentTimeTick > worker->_LastTimeTick) 
    {
        EndOverCostAction(currentTimeTick, worker);
        worker->_LastTimeTick = currentTimeTick;
        worker->_CurrentSeqNumber = worker->MinSeqNumber;
        worker->_IsOverCost = false;
        worker->_OverCostCountInOneTerm = 0;
        worker->_GenCountInOneTerm = 0;
        return CalcId(worker);
    }
    if (worker->_OverCostCountInOneTerm > worker->TopOverCostCount) 
    {
        EndOverCostAction(currentTimeTick, worker);
        worker->_LastTimeTick = uGetNextTimeTick(worker);
        worker->_CurrentSeqNumber = worker->MinSeqNumber;
        worker->_IsOverCost = false;
        worker->_OverCostCountInOneTerm = 0;
        worker->_GenCountInOneTerm = 0;
        return CalcId(worker);
    }
    /* 当前序列数超过了最大序列数 */
    if (worker->_CurrentSeqNumber > worker->MaxSeqNumber) 
    {
        worker->_LastTimeTick++;
        worker->_CurrentSeqNumber = worker->MinSeqNumber;
        worker->_IsOverCost = true;
        worker->_OverCostCountInOneTerm++;
        worker->_GenCountInOneTerm++;
        return CalcId(worker);
    }

    worker->_GenCountInOneTerm++;
    return CalcId(worker);
}

static inline uint64_t NextNormalId(SnowFlakeWorker *worker) 
{
    uint64_t currentTimeTick = uGetCurrentTimeTick(worker);

    /* 时间戳出现了异常 */
    if (currentTimeTick < worker->_LastTimeTick) 
    {
        if (worker->_TurnBackTimeTick < 1) 
        {
            worker->_TurnBackTimeTick = worker->_LastTimeTick - 1;
            worker->_TurnBackIndex++;
            if (worker->_TurnBackIndex > 4) 
            {
                worker->_TurnBackIndex = 1;
            }
        }
        return CalcTurnBackId(worker);
    }

    if (worker->_TurnBackTimeTick > 0) 
    {
        worker->_TurnBackTimeTick = 0;
    }

    if (currentTimeTick > worker->_LastTimeTick) 
    {
        worker->_LastTimeTick = currentTimeTick;
        worker->_CurrentSeqNumber = worker->MinSeqNumber;
        return CalcId(worker);
    }

    if (worker->_CurrentSeqNumber > worker->MaxSeqNumber) 
    {
        worker->_TermIndex++;
        worker->_LastTimeTick++;
        worker->_CurrentSeqNumber = worker->MinSeqNumber;
        worker->_IsOverCost = true;
        worker->_OverCostCountInOneTerm = 1;
        worker->_GenCountInOneTerm = 1;
        return CalcId(worker);
    }

    return CalcId(worker);
}

/**
 * @brief   时钟正常时使用此函数计算 ID
 * @param   worker 参数
 * @return  计算结果
 */
static inline uint64_t CalcId(SnowFlakeWorker *worker) 
{
    uint64_t result = (worker->_LastTimeTick << worker->_TimestampShift) | (worker->WorkerId << worker->SeqBitLength) |
                      (worker->_CurrentSeqNumber);
    worker->_CurrentSeqNumber++;
    return result;
}

/**
 * @brief   时钟回拨时使用此函数计算 ID
 * @param   worker 参数
 * @return  计算结果
 */
static inline uint64_t CalcTurnBackId(SnowFlakeWorker *worker)
{
    uint64_t result = (worker->_LastTimeTick << worker->_TimestampShift) | (worker->WorkerId << worker->SeqBitLength) |
                      (worker->_TurnBackTimeTick);
    worker->_TurnBackTimeTick--;
    return result;
}

extern SnowFlakeWorker *NewSnowFlakeWorker() 
{
    SnowFlakeWorker *worker = (SnowFlakeWorker *) snowflake_malloc(sizeof(SnowFlakeWorker));
    worker->_IsOverCost = false;
    worker->_LastTimeTick = 0;
    worker->_TurnBackTimeTick = 0;
    worker->_TurnBackIndex = 0;
    worker->_OverCostCountInOneTerm = 0;
    worker->_GenCountInOneTerm = 0;
    worker->_TermIndex = 0;

    return worker;
}

/**
 * @brief   计算方式 1 雪花漂移算法
 * @param   worker 参数
 * @return  ID
 */
extern uint64_t WorkerM1NextId(SnowFlakeWorker *worker)
{
    snowflake_lock();
    uint64_t id = worker->_IsOverCost ? NextOverCostId(worker) : NextNormalId(worker);
    snowflake_unlock();
    return id;
}
/**
 * @brief   获取当前时间，微妙级
 * @return  当前时间
 */
extern uint64_t uGetCurrentMicroTime(void) 
{
    return GetSystemCurrentMicroTime();
}
/**
 * @brief   获取当前时间戳
 * @return  当前时间戳
 */
extern uint64_t uGetCurrentTime(void) 
{
    return (uGetCurrentMicroTime() / 1000);
}

/**
 * @brief   计算时间戳
 * @param   worker 参数
 * @return  当前时间戳
 */
extern uint64_t uGetCurrentTimeTick(SnowFlakeWorker *worker) 
{
    return (uGetCurrentTime() - worker->BaseTime);
}
/**
 * @brief   获取时间戳，并与上次时间戳比较
 * @param   worker 参数
 * @return  下一个时间戳
 */
extern uint64_t uGetNextTimeTick(SnowFlakeWorker *worker) 
{
    uint64_t tempTimeTicker = uGetCurrentTimeTick(worker);
    while (tempTimeTicker <= worker->_LastTimeTick) 
    {
        tempTimeTicker = uGetCurrentTimeTick(worker);
    }
    return tempTimeTicker;
}
