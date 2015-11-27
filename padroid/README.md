[简体中文](#简体中文)

[English](#english)

## 简体中文

Paduino 是一个运行在 iOS 设备上的程序，通过它你可以将你的手机变成一台连接 Arduino 的控制手柄。Paduino 将通过蓝牙串口发送指令到 Arduino。

**硬件需求**
 * iOS 设备
 * 带 BLE 扩展的 Arduino 设备

**构建方式**
 * 使用 Unity3D 构建 iOS 平台项目
 * 使用 XCode 编译并部署 iOS 项目到设备
 * 将 Arduino_Sample/pilot 文件夹中的 Arduino 项目编译烧写到 Arduino 开发板

**指令列表**
 * "ld;" 左侧 D-Pad 按下
 * "lu;" 左侧 D-Pad 抬起
 * "<X,Y;" 左侧 D-Pad 偏移, X/Y 范围为 [-255, 255]
 * "rd;" 右侧 D-Pad 按下
 * "ru;" 右侧 D-Pad 抬起
 * ">X,Y;" 右侧 D-Pad 偏移, X/Y 范围为 [-255, 255]
 * "sd;" select 键 按下
 * "su;" select 键 抬起
 * "td;" start 键 按下
 * "tu;" start 键 抬起

**安全防护**
Paduino 和 Pilot 使用一定的安全机制保障在诸如信号延迟和断开连接的情况下被控端的安全
 * Paduino 在没有输入的情况下每 1 秒会发送一次 {0, 0} 的 D-Pad 数据指令
 * Arduino 在没有接收到指令的情况下每 1.2 秒会回调一次 {0, 0} 的 D-Pad 数据回调

## English

Paduino is an App running on an iOS device, which can make your mobile phone into a joystick to pair with an Arduino board with bluetooth support. Paduino will send AT commands to your Arduino via bluetooth.

**Hardware requirements**
 * iOS device
 * Arduino board with BLE support

**Setup**
 * Build the iOS platform target project with Unity3D
 * Build and distribute iOS App with XCode to your iOS device
 * Compile and burn the scratch in the Arduino_Sample/pilot folder to your Arduino board

**AT command list**
 * "ld;" left D-Pad down
 * "lu;" left D-Pad up
 * "<X,Y;" left D-Pad offset, X/Y in range [-255, 255]
 * "rd;" right D-Pad down
 * "ru;" right D-Pad up
 * ">X,Y;" right D-Pad offset, X/Y in range [-255, 255]
 * "sd;" select key down
 * "su;" select key up
 * "td;" start key down
 * "tu;" start key up

**Security insurance**
Paduino and Pilot use some sort of strategy to guarantee the safety of the back end devices in situations such as signal delay, lost of paired, etc.
 * Paduino will send a {0, 0} D-Pad data command every 1 second while no input
 * Arduino will call a {0, 0} D-Pad data callback every 1.2 seconds while no command received
 
