#Mobile-Pilot
##Project's BG
本项目输出目标为，在掌握四轴飞行器（Quadrotor）飞行基本原理和开发方法后，摆脱传统控制方式，通过`手机蓝牙`的方式，控制飞行器。<br />

###Basic Backgrouds about Quadrotor
**1.Pixhawk**
![主板 icon](https://pixhawk.org/_media/modules/pixhawk_connectors.png?cache=)

Pixhawk是一款高性能的自动飞行硬件模块，适用于固定翼，多轴飞行器，直升机，车船等可以运动的自动控制平台，它结合了PX4FMU和PX4IO这两大模块的功能。它对于四轴飞行器（Quadrotor）而言是最重要的基础硬件设备。所有的软件功能都运行在Pixhawk的基础上。Pixhawk支持许多`飞行协议栈`，它允许现有的`APM`和`PX4`能够无缝地过渡到该系统。

**2.APM**

`APM`和`Pixhawk`是分别为两个不同的飞控系统，它们从`"硬件－固件－软件"`，均有自己完整的一套体系。
>Pixhawk是源于ETH Zurich的计算机视觉与几何实验室、自主系统实验室和自动控制实验室的PIXHAWK项目。它具有来自ST公司先进的处理器和传感器技术，以及NuttX实时操作系统，能够实现惊人的性能，灵活性和可靠性控制任何自主飞行器。

ArduPilot/APM是由一个大型爱好者社区开发。由于ArduPilot开源特性，使得开发者们成功的能够将其移植到PX4等其他平台上，从而让APM从市场上的闭源产品中脱颖而出。最初APM自动导航板是基于Arduino开发环境的，现在不仅支持Arduino，而且支持Arduino兼容的硬件（如PX4）。“APM” 即为前缀（APM:Copter，APM:Plane，APM:Rover等）。`Copter`，`Plane`，`Rover`是APM中的几大模块，其中`Plane`为固定翼无人机；`Rover`为无人地面车辆；`Copter`则为多旋翼无人机，四轴飞行器就是Copter的一种。

**3.发射机**

飞行器是通过接收`发射机（如下图,类似于PS手柄）`发出的10路通道(channel)模拟信号，进行控制飞行器的四个主要参数：旋转度roll，偏转度yaw，油门throttle，斜度pitch等。<br />

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

###Copter Code Overview
ArduPilot中的Copter模块是为多旋翼飞行器而开发的飞行控制软件层。四轴飞行器则为多旋翼飞行器的一种。这也意味着，Copter模块是四轴飞行器的核心控制模块。ArduPilot为四轴飞行器定义了许多种飞行模式，从上层抽象来看，这些模式输出到发动机大体分为两种形式：Manual手动飞行模式，AutoPilot自动导航模式。每个模式的具体实现都包括在一个名为`control_mode.cpp`文件中，例如control_stabilize.cpp，以及control_rtl.cpp。

**1.Manual飞行模式**
手动飞行模式包含了最常用的`Stabilize`（自稳模式）。在手动飞行模式下，每个具体模式都拥有自己的初始化函数`mode_init()`和运行函数`mode_run()`。<br />
***mode_init()***<br />
每次飞行器启动时，会选择一个具体的飞行模式。这时就会调用在flight_mode.cpp文件中的`set_mode()`函数。这个函数会根据传入的相应模式，调用该模式的`mode_init()`函数，进行初始化操作。例如在`stabilize_init()`函数中，会调用pos_control类中的成员函数`set_alt_target()`，将目标高度初始化为0。这样做的目的在于激活`pos controller`(位置控制器)，使其能够将高度错误反馈出来。<br />
***mode_run()***<br />
同样的，在飞行器运行时，飞控会调用`update_flight_mode()`，再根据具体的模式，调用该模式的`mode_run()`函数。例如`stabilize_run()`函数将发射器输入转换为目标参数（roll旋转，pitch斜度，yaw angles偏转角度）。
![Manual Mode](http://dev.ardupilot.com/wp-content/uploads/sites/6/2013/06/AC_CodeOverview_ManualFlightMode.png)

***Stabilize（自稳模式）***<br />
自稳模式是最APM:Copter中最常用的手动飞行模式。在此模式下：<br />
＊ 飞行员的旋转，俯仰操作控制飞行器的倾斜角度，当飞行员松开对应摇杆时，自稳模式自动保持飞行器水平。<br />
＊ 如果飞行员必须经常地操作旋转，俯仰指令，此模式让飞行器如同在原地，不然会被风吹走。<br />
＊ 当飞行员进行转向操作控制飞行器方向时，飞行员松开转向摇杆，在自稳模式下飞行器会保持当时的方向。<br />
＊ 飞行员的油门操作控制飞行器马达的平均转速，也就是说持续不断的调节油门以维持高度。如果飞行员把油门摇杆向下打到底，马达会降到最低转速（MOT_SPIN_ARMED），如果当时飞行器仍在飞行过程中，则会失去高度而坠落。<br />
＊ 给马达的油门大小会根据当时飞行器的倾角（例如，倾角变大时增加），以减少飞行员对飞行器高度改变所必需做的补偿。<br />
＊ 在AC3.0.1版本及之前版本中，飞行器只能在自稳模式或特技模式下ARMED（解锁）。<br />
`解锁`：是飞行器起飞前必须做的一项操作。解锁后，马达才能够运转。


**3.AutoPilot飞行模式**<br />
在AutoPilot飞行模式中，包含定高模式（AltHold），返航模式（RTL），自动模式（Auto）等等。<br />
![AutoPilot Mode](http://dev.ardupilot.com/wp-content/uploads/sites/6/2013/06/AC_CodeOverview_AutoFlightModes.png)

***RTL Mode***<br />
在返航（RTL）模式中飞行器会从它当是的位置飞到home（解锁的位置）的上方悬停。返航模式的行为可以由好多个参数的调整而加以控制。当选择返航模式后，飞行器会先上升到RTL_ALT高度，或维持当时高度，如果当时高度高于RTL_ALT高度，然后返航。预设RTL_ALT是15公尺。<br />
![AutoPilot OverView](http://copter.ardupilot.tw/wp-content/uploads/2014/10/RTL.png)  
RTL是依赖GPS的动作，所以GPS锁定是使用这个模式的前提。在解锁（arm）之前，需要确认APM的蓝色LED灯恒亮，而不是闪烁。如果GPS不带罗盘，GPS锁定后，LED会持续亮蓝灯。如果是GPS和罗盘的模组，GPS锁定后，LED会闪蓝灯。<br />
RTL会命令飞行器回到home，也就是解锁的位置。`因此，home的位置永远应该是飞行器实际上GPS起飞的地点，没有障碍并且远离人群`。在APM:Copter中，如果GPS锁定，然后ARM飞行器，home就是飞行器当时解锁时的位置。也就是说，你在APM:Copter中，执行RTL，飞行器会回到她当时解锁时的位置。<br />

在RTL模式中，可调整的参数有：  
1.RTL_ALT:飞行器返航前会先飞到这个高度。`设为零会以当时的高度返航；返航高度可设为1-8000公分；预设返航高度为15公尺（1500）`  
2.RTL_ALT_FINAL:在RTL的最后阶段，或者完成任务后，飞行器会飞到这个高度。`设为0会自动降落；最后返航高度可以设为0-1000公分`  
3.RTL_LOIT_TIME:最后降落前，在‘Home’之上悬停的时间，以千分之一秒为为单位。`悬停时间可以设为0-60,000微秒`   
4.WP_YAW_BEHAVIOR:设定飞控系统如何控制任务或者返航中的航向。`0表示不改变航向；1表示面向下一个中途点，包括返航中面向home；2表示面向下一个中途点，RTL除外（即飞行器返航中保持最后的航向）`
5.LAND_SPEED:下降最后阶段的速度，以公分每秒为单位。`下降速度可设为每秒20-200公分`

***Auto Mode***<br />
自动模式中，飞行器会遵循事先设定好的任务程序，由导航指令（例如：中途点waypoints）和“执行”指令（例如：按相机快门或其他不影响飞行器位置的指令）组成，存储在AutoPilot中。
![AutoPilot OverView](http://copter.ardupilot.tw/wp-content/uploads/2014/09/auto.png)
自动模式整合定高模式的高度控制，和悬停模式的位置控制





