# Mobile-Pilot
## Project's BG
上次PPT科普了一下四轴飞行器（Quadrotor），以及目前主流的四轴飞行器及其应用和发展方向。本次输出目标为，在掌握四轴飞行器（Quadrotor）飞行基本原理和开发方法后，摆脱传统控制方式，通过`手机蓝牙`的方式，控制飞行器。<br />

### Basic knowledges about Quadrotor
1.`Pixhawk`
![主板 icon](https://pixhawk.org/_media/modules/pixhawk_connectors.png?cache=)

Pixhawk是一款高性能的自动飞行硬件模块，适用于固定翼，多轴飞行器，直升机，车船等可以运动的自动控制平台，它结合了PX4FMU和PX4IO这两大模块的功能。它对于四轴飞行器（Quadrotor）而言是最重要的基础硬件设备。所有的软件功能都运行在Pixhawk的基础上。Pixhawk支持许多`飞行协议栈`，它允许现有的`APM`和`PX4`能够无缝地过渡到该系统。APM运行在PX4中间层，基于APM协议栈的飞行控制软件ArduPilot。

![Mainboard2 icon](http://www.pixhawk.cc/wp-content/uploads/2015/09/pic3.jpg)

2.`APM`


3.`发射机`

飞行器是通过接收`发射机（如下图,类似于PS手柄）`发出的10路通道(channel)模拟信号，进行控制飞行器的四个主要参数：旋转roll，偏航yaw，油门throttle，斜坡pitch等。
![发射机 icon](http://copter.ardupilot.com/wp-content/uploads/sites/2/2012/01/radio_setup1.png)