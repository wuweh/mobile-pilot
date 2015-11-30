# Mobile-Pilot
## Project's BG
上次PPT科普了一下四轴飞行器（Quadrotor），以及目前主流的四轴飞行器及其应用和发展方向。本次输出目标为，在掌握四轴飞行器（Quadrotor）飞行基本原理和开发方法后，摆脱传统控制方式，通过`手机蓝牙`的方式，控制飞行器。<br />

### Basic knowledges about Quadrotor
1.`Pixhawk`
![主板 icon](https://pixhawk.org/_media/modules/pixhawk_connectors.png?cache=)

Pixhawk是一款高性能的自动飞行硬件模块，适用于固定翼，多轴飞行器，直升机，车船等可以运动的自动控制平台，它结合了PX4FMU和PX4IO这两大模块的功能。它对于四轴飞行器（Quadrotor）而言是最重要的基础硬件设备。所有的软件功能都运行在Pixhawk的基础上。Pixhawk支持许多`飞行协议栈`，它允许现有的`APM`和`PX4`能够无缝地过渡到该系统。

2.`APM`

`APM`和`Pixhawk`是分别为两个不同的飞控系统，它们从`"硬件－固件－软件"`，均有自己完整的一套体系。
>Pixhawk是源于ETH Zurich的计算机视觉与几何实验室、自主系统实验室和自动控制实验室的PIXHAWK项目。它具有来自ST公司先进的处理器和传感器技术，以及NuttX实时操作系统，能够实现惊人的性能，灵活性和可靠性控制任何自主飞行器。

ArduPilot/APM是由一个大型爱好者社区开发。由于ArduPilot开源特性，使得开发者们成功的能够将其移植到PX4等其他平台上，从而让APM从市场上的闭源产品中脱颖而出。最初APM自动导航板是基于Arduino开发环境的，现在不仅支持Arduino，而且支持Arduino兼容的硬件（如PX4）。“APM” 即为前缀（APM:Copter，APM:Plane，APM:Rover等）。`Copter`，`Plane`，`Rover`是APM中的几大模块，其中`Plane`为固定翼无人机；`Rover`为无人地面车辆；`Copter`则为多旋翼无人机，四轴飞行器就是Copter的一种。

3.`发射机`

飞行器是通过接收`发射机（如下图,类似于PS手柄）`发出的10路通道(channel)模拟信号，进行控制飞行器的四个主要参数：旋转roll，偏航yaw，油门throttle，斜坡pitch等。<br />

![发射机 icon](http://copter.ardupilot.com/wp-content/uploads/sites/2/2012/01/radio_setup1.png)