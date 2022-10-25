# VeighNa框架的XTP底层接口

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/vnpy-logo.png"/>
</p>

<p align="center">
    <img src ="https://img.shields.io/badge/version-2.2.32.2.1-blueviolet.svg"/>
    <img src ="https://img.shields.io/badge/platform-windows|linux-yellow.svg"/>
    <img src ="https://img.shields.io/badge/python-3.7|3.8|3.9|3.10-blue.svg" />
    <img src ="https://img.shields.io/github/license/vnpy/vnpy.svg?color=orange"/>
</p>

## 说明

基于中泰证券XTP柜台的2.2.32.2接口封装开发。

## 安装

安装环境推荐基于3.3.0版本以上的【[**VeighNa Studio**](https://www.vnpy.com)】。

直接使用pip命令：

```
pip install vnpy_xtp
```


或者下载源代码后，解压后在cmd中运行：

```
pip install .
```

使用源代码安装时需要进行C++编译，因此在执行上述命令之前请确保已经安装了【Visual Studio（Windows）】或者【GCC（Linux）】编译器。

## 使用

以脚本方式启动（script/run.py）：

```
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp

from vnpy_xtp import XtpGateway


def main():
    """主入口函数"""
    qapp = create_qapp()

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    main_engine.add_gateway(XtpGateway)
    
    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()


if __name__ == "__main__":
    main()
```
