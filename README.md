# SnowFlake

[Chinese](README_ZH.md) | English

## 1. Introduction

SnowFlake is a useful software package based on the open source SnowFlake algorithm created by RT-Thread.

Snowflake algorithm is an algorithm invented by Twitter. The main purpose is to solve the problem of how to generate ID in distributed environment.

Mandatory requirements for the distributed ID generation rule:

- Globally unique;

- It is essential that no duplicate ID numbers appear, since they are unique.

The SnowFlake software package has the following features:

- Integer number, monotonically increasing over time (not necessarily continuous);

- There are two kinds of snowmeter methods, traditional snowflake algorithm and optimized snowflake algorithm (snowflake drift);

- Snowflake drift algorithm, which generates shorter and faster ids;

- Snowflake drift supports time callback processing, for example, the server time callback is 1 second. This algorithm can automatically adapt to the unique ID of the critical time.

For more software package introduction, please refer to [Detailed introduction](docs/introduction.md).

### 1.1 Directory structure

The directory structure of the SnowFlake software package is as follows:

```
SnowFlake
├───docs 
│   ├───figures                   // Documents use pictures
│   │   api.md                    // API instructions
│   │   introduction.md           // Introduction document
│   │   principle.md              // Implementation principle
│   │   README.md                 // Document structure description
│   │   samples.md                // package sample
│   │   user-guide.md             // Instructions
│   └───version.md                // version
├───inc                           // header file
├───samples                       // sample code
│   └───snowflake_sample          // gets the ID sample code
├───src                           // source file
│   LICENSE                       // package license
│   README.md                     // Software package instructions
│   SConscript                    // RT-Thread default build script
│   snowflake.h                   // snowflake header file
│   snowflake_port.c              // snowflake_port source file
└───snowflake_port.h              // snowflake_port header file
```

### 1.2 License

The SnowFlake software package complies with the MIT license, see the LICENSE file for details.

### 1.3 Dependency

- RT_Thread 3.0+

## 2. Get the software package

To use the SnowFlake software package, you need to select it in the RT-Thread package management. The specific path is as follows:

```shell
RT-Thread online packages
	tools packages  --->
		[*] Snowflake algorithm is a distributed ID generation algorithm
		[ ]   Enable snowflake samples 
              Version (latest)  --->
```

Note: To use SnowFlake, you need to enable the RTC function. If you select SnowFlake, the RTC function is enabled by default.

After the configuration is complete, let the RT-Thread package manager automatically update, or use the pkgs --update command to update the package to the BSP.

## 3. Use SnowFlake software package

- For detailed description of the software package, please refer to [Package Introduction](docs/introduction.md)

- For detailed sample introduction, please refer to [Sample Document](docs/samples.md) 

- How to use from scratch, please refer to [User Guide](docs/user-guide.md) 

- For complete API documentation, please refer to [API Manual](docs/api.md) 

- The working principle of the software package, please refer to [Working Principle](docs/principle.md)

- More **Detailed introduction documents** are located in the [`/docs`](/docs) folder, **Please check before using the package for development**.

## 4. Matters needing attention

Note If you need to change the configuration, follow the precautions in ** introduction **

## 5. Contact & Thanks

- Maintenance: 2022alpha

- Homepage: 