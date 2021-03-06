# API 说明

## 雪花算法初始化

```c
void snowflake_init(uint32_t workerid, uint8_t method, uint8_t worker_id_bit_length, uint8_t Seq_bit_length);
```


| 参数               | 描述                             |
|:------------------ |:---------------------------------|
| workerid           | 机器码，必须由外部设定 			|
| method			 | 雪花计算方法，取值范围 [1, 2] （1 - 漂移算法, 2 - 传统算法，参数为 0 时默认值 1 ）  |
| worker_id_bit_length | 机器码位长，取值范围 [1, 15]（要求：序列数位长+机器码位长不超过22，参数为 0 时默认值 1 ） |
| Seq_bit_length       | 序列数位长，取值范围 [3, 21]（要求：序列数位长+机器码位长不超过22，参数为 0 时默认值 6 ） |
| **返回**             | **描述**				 |
| 空      			   |              			 |

## 获取 ID 

```c
uint64_t snowflake_get_id(void);
```

| 参数              | 描述                              |
|:------------------|:-----------------------------------|
| 空                |                
| **返回**          | **描述**                        |
| ID                | uint64_t 型数据                |

