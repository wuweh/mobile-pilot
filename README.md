#Mobile-Pilot
##Project's BG
上次PPT科普了一下四轴飞行器（Quadrotor），以及目前主流的四轴飞行器及其应用和发展方向。本次输出目标为，在掌握四轴飞行器（Quadrotor）飞行基本原理和开发方法后，摆脱传统控制方式，通过`手机蓝牙`的方式，控制飞行器。<br />

###Basic Backgrouds about Quadrotor
**1.Pixhawk**
![主板 icon](https://pixhawk.org/_media/modules/pixhawk_connectors.png?cache=)

Pixhawk是一款高性能的自动飞行硬件模块，适用于固定翼，多轴飞行器，直升机，车船等可以运动的自动控制平台，它结合了PX4FMU和PX4IO这两大模块的功能。它对于四轴飞行器（Quadrotor）而言是最重要的基础硬件设备。所有的软件功能都运行在Pixhawk的基础上。Pixhawk支持许多`飞行协议栈`，它允许现有的`APM`和`PX4`能够无缝地过渡到该系统。

**2.APM**

`APM`和`Pixhawk`是分别为两个不同的飞控系统，它们从`"硬件－固件－软件"`，均有自己完整的一套体系。
>Pixhawk是源于ETH Zurich的计算机视觉与几何实验室、自主系统实验室和自动控制实验室的PIXHAWK项目。它具有来自ST公司先进的处理器和传感器技术，以及NuttX实时操作系统，能够实现惊人的性能，灵活性和可靠性控制任何自主飞行器。

ArduPilot/APM是由一个大型爱好者社区开发。由于ArduPilot开源特性，使得开发者们成功的能够将其移植到PX4等其他平台上，从而让APM从市场上的闭源产品中脱颖而出。最初APM自动导航板是基于Arduino开发环境的，现在不仅支持Arduino，而且支持Arduino兼容的硬件（如PX4）。“APM” 即为前缀（APM:Copter，APM:Plane，APM:Rover等）。`Copter`，`Plane`，`Rover`是APM中的几大模块，其中`Plane`为固定翼无人机；`Rover`为无人地面车辆；`Copter`则为多旋翼无人机，四轴飞行器就是Copter的一种。

**3.发射机**

飞行器是通过接收`发射机（如下图,类似于PS手柄）`发出的10路通道(channel)模拟信号，进行控制飞行器的四个主要参数：旋转roll，偏航yaw，油门throttle，斜坡pitch等。<br />

![发射机 icon](http://copter.ardupilot.com/wp-content/uploads/sites/2/2012/01/radio_setup1.png)<br />


###ArduPilot CodeBase
ArduPilot大体可分为5个主要的部分：<br />

**1.Vehicle Directories 发动机模型**<br />
这部分为定义在固件层上的一层抽象，它向不同类型的发动机模型提供固件层的接口。目前ArduPilot中支持4种模型，分别为Plane, Copter, APMrover2和AntennaTracker。<br />

**2.AP_HAL**<br />
AP_HAL是Hardware Abstraction Layer的缩写。这部分的主要功能在于，将ArduPilot适配到众多不同的平台上去。在AP_HAL目录以及其Lib目录中，有许多子目录。由于不同平台板子有其特有的属性，ArduPilot为了能够支持跨平台，就为不同平台建立了不同的接口目录。例如AP_HAL_AVR是向基于AVR板的接口目录，AP_HAL_PX4则是为PX4提供的，而AP_HAL_Lniux是向基于Linux的电路板提供的。<br />

**3.Libraries**<br />
ArduPilot所依赖的库均在这部分。<br />

**4.Tool Directories**<br />
工具目录向ArduPilot提供了各种各样的支持工具。例如tools/autotest目录向开发者提供自动测试基础结构；tools/Replay提供日志重放的实用功能。<br />

**5.External Support Code**<br />
对于其他平台，需要外部支持的代码。在相同的平台下，开发者有时仍然需要这些外部支持代码向其提供额外的特性和主板支持。例如：<br />
*PX4NuttX-板载实时系统，它是用在PX4主板上NuttX RTOS实时系统的核心模块；PX4Firmware-PX4的中间件以及PX4的驱动层；mavlink－mavlink通讯协议以其核心生成器；uavcan-ArduPilot中uavcan CANBUS总线接口协议的具体实现；*



