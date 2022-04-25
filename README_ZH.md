# SnowFlake

中文页 | [英文页](README.md)

## 1、介绍

SnowFlake 软件包是 RT-Thread 基于开源雪花算法而制作的一款实用软件包。

雪花算法是Twitter公司发明的一种算法，主要目的是解决在分布式环境下，ID怎样生成的问题。

分布式ID生成规则硬性要求：

- 全局唯一；

- 不能出现重复的ID号，既然是唯一标识，这是最基本的要求。

SnowFlake 软件包功能特点如下：

- 整形数字，随时间单调递增（不一定连续）;

- 集合了两种雪花计方式，传统雪花算法和优化的雪花算法（雪花漂移）；

- 雪花漂移算法，它生成的ID更短、速度更快；

- 雪花漂移支持时间回拨处理，比如服务器时间回拨1秒，本算法能自动适应生成临界时间的唯一ID。

更多软件包介绍请查看 [详细介绍](docs/introduction.md)。

### 1.1 目录结构

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

### 1.2 许可证

SnowFlake 软件包遵循 MIT 许可，详见 LICENSE 文件。

### 1.3 依赖

- RT_Thread 3.0+

## 2、获取软件包

使用 SnowFlake 软件包需要在 RT-Thread 的包管理中选中它，具体路径如下：

```shell
RT-Thread online packages
	tools packages  --->
		[*] Snowflake algorithm is a distributed ID generation algorithm
		[ ]   Enable snowflake samples 
              Version (latest)  --->
```

注：使用 SnowFlake 需要依赖 RTC，需要先开启 RTC 功能，若直接选中 SnowFlake 则会默认开启 RTC。

配置完成后让 RT-Thread 的包管理器自动更新，或者使用 pkgs --update 命令更新包到 BSP 中。

## 3、使用 SnowFlake 软件包

- 软件包详细介绍，请参考 [软件包介绍](docs/introduction.md)

- 详细的示例介绍，请参考 [示例文档](docs/samples.md) 

- 如何从零开始使用，请参考 [用户指南](docs/user-guide.md)

- 完整的 API 文档，请参考 [API 手册](docs/api.md)

- 软件包工作原理，请参考 [工作原理](docs/principle.md) 

- 更多**详细介绍文档**位于 [`/docs`](/docs) 文件夹下，**使用软件包进行开发前请务必查看**。

## 4、注意事项

若需要进行配置变更，请务必遵循**详细介绍**中配置变更注意事项。

## 5、联系方式 & 感谢

- 维护：2022alpha

- 主页：