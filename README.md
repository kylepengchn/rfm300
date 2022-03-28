# RFM300

## 1、介绍

这是一个 RT-Thread 的软件包，该软件包提供了 RFM300模块的驱动。

RFM300是由 HOPERF|华普微电子生产无线收发模块。

RFM300模块系列基于CMOSTEK NextGenRFTM CMT2300芯片设计而成，可工作在433/868/915MHz，超低接收灵敏度（120dBm）， +20dBm (RFM300H)/+13dBm(RFM300)发射功率，频率广链接性能高。

> 更多关于 RFM300的信息请参阅 [RFM300无线收发模块](https://www.hoperf.cn/modules/rf_transceiver/RFM300.html) 或 _数据手册_

### 1.1 目录结构

| 名称 | 说明 |
| ---- | ---- |
| docs | 文档 |
| demo | 有关使用该驱动的样例代码 |
| src  | 源代码目录 |

### 1.2 许可证

RFM300package 遵循 Apache license v2.0 许可，详见 `LICENSE` 文件。

### 1.3 依赖

- RT-Thread PIN 设备
- RT-Thread SPI 设备
- RT-Thread IPC (SEM)

## 2、获取软件包

使用 RFM300package 需要在 RT-Thread 的包管理器中选择它，具体路径如下：

```
RT-Thread online packages
    peripheral libraries and drivers --->
        [*] RFM300: ISM Transceiver Module With +20dBm(100mW) Output Power.
			(spi0) The spi bus of rfm300 (NEW)                            
			(rfm300) The spi device name for rfm300 (NEW)                 
			(rfm300_fifo) The spi device name for rfm300 fifo (NEW)       
			(-1)  The CSB pin of rfm300 (NEW)                             
			(-1)  The FCSB pin of rfm300 (NEW)                            
			(-1)  The GPIO1 pin of rfm300 (NEW)                           
			(-1)  The GPIO2 pin of rfm300 (NEW)                           
			(-1)  The GPIO3 pin of rfm300 (NEW)                           
			[ ]   Use demo (NEW)
```

选中后让 RT-Thread 的包管理器自动更新，或者使用 `pkgs --update` 命令更新包到 BSP 中。

## 3、使用 RFM300

_**用户手册--> [datasheet.pdf](./docs/RFM300_Datasheet_REV1.2.pdf)**_

_**具体用例, 参见 demo --> [rfm300_demo.c](./demo/rfm300_demo.c)**_

## 4、注意事项

无

## 5、联系方式

- 维护：kylepengchn@163.com
- 主页：https://github.com/kylepengchn/rfm300

