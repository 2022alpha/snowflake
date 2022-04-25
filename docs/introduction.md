# 软件包介绍

SnowFlake 软件包是 RT-Thread 基于开源 SnowFlake 算法而制作的一款实用软件包。

## 技术支持

开源地址：https://github.com/2022alpha/snowflake

## 软件包目录结构

SnowFlake 软件包目录结构如下所示：

```shell
snowflake
├───docs 
│   ├───figures                     // 文档使用图片
│   │   api.md                      // API 使用说明
│   │   introduction.md             // 介绍文档
│   │   principle.md                // 实现原理
│   │   README.md                   // 文档结构说明
│   │   samples.md                  // 软件包示例
│   │   user-guide.md               // 使用说明
│   └───version.md                  // 版本
├───inc                             // 头文件
├───samples                         // 示例代码
│   └───snowflake_sample        	// 获取 ID 示例代码
├───src                             // 源文件
│   LICENSE                         // 软件包许可证
│   README.md                       // 软件包使用说明
│   SConscript                      // RT-Thread 默认的构建脚本
│   snowflake.h                     // snowflake 头文件 
│   snowflake_port.c                // snowflake_port 源文件
└───snowflake_port.h                // snowflake_port 头文件
```

## 软件包功能特点

- 整形数字，随时间单调递增（不一定连续）;

- 集合了两种雪花计方式，传统雪花算法和优化的雪花算法（雪花漂移）；

- 优化的雪花算法（雪花漂移），它生成的ID更短、速度更快；

- 雪花漂移支持时间回拨处理，比如服务器时间回拨1秒，本算法能自动适应生成临界时间的唯一ID。

## ID 组成说明

 * 本算法生成的ID由3部分组成（沿用雪花算法定义）：相对基础时间的时间差 + WorkerId + 序列数 
 
 * 第1部分，时间差，是生成ID时的系统时间减去 BaseTime 的总时间差（毫秒单位）。
 
 * 第2部分，WorkerId，是区分不同机器或不同应用的唯一ID，最大值由 WorkerIdBitLength（默认6）限定。
 
 * 第3部分，序列数，是每毫秒下的序列数，由参数中的 SeqBitLength（默认6）限定。
 
## ID 示例

本算法生成的 ID ，是整数（占用空间最多8字节），以下是基于默认配置生成的 ID： 

```
 269137030549573
 269137030549574
 269137030549575
```

## 配置变更

配置变更指是系统运行一段时间后，再调整运行参数（IdGeneratorOptions 选项值），请注意：

- 1.最重要的一条原则是：BaseTime **只能往前**（比老值更小、距离现在更远）赋值，原因是往后赋值极大可能产生相同的时间戳。[**不推荐**在系统运行之后调整 BaseTime]

- 2.任何时候增加 WorkerIdBitLength 或 SeqBitLength，都是可以的，但是慎用 “减小”的操作，因为这可能导致在未来某天生成的 ID 与过去老配置时相同。[允许在系统运行之后**增加**任何一个 BitLength 值]

- 3.如果必须减小 WorkerIdBitLength 或 SeqBitLength 其中的一项，一定要满足一个条件：新的两个 BitLength 之和要大于 老的值之和。[**不推荐**在运行之后缩小任何一个 BitLength 值]

- 4.上述3条规则，并未在本算法内做逻辑控制，集成方应根据上述规则做好影响评估，确认无误后，再实施配置变更。



