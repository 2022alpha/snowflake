/*
 * 版权属于：yitter(yitter@126.com)
 * 开源地址：https://github.com/yitter/idgenerator
 */

#include "yitidhelper.h"

/**
* @brief   保存设定参数
* @param   options 参数
*/
extern void SetIdGenerator(IdGeneratorOptions options) 
{
    SetOptions(options);
}

/**
 * @brief   配置雪花算法机器码
 * @param   workerId 机器码
 */
extern void SetWorkerId(uint32_t workerId) 
{
    IdGeneratorOptions options = BuildIdGenOptions(workerId);
    SetIdGenerator(options);
}

/**
 * @brief   获取ID
 * @return  ID
 */
extern uint64_t NextId(void) 
{
    return GetIdGenInstance()->NextId();
}
