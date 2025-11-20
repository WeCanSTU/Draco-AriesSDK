[中文](https://github.com/WeCanSTU/Draco-AriesSDK/blob/master/README_CN.md) / [English](https://github.com/WeCanSTU/Draco-AriesSDK/blob/master/README.md)

# Draco-AriesSDK 移植工程

本仓库是基于 **[Draco 天龙座 CA51F005 1T 8051 核心板](https://gitee.com/WeCanSTU/Draco)** 的 **[AriesSDK](https://gitee.com/WeCanSTU/AriesSDK) 软件移植**工程，提供了完整的软件框架、Application 示例，支持多工具链开发，帮助开发者快速实现嵌入式项目开发、调试及部署。


## 文档结构

1. **功能特性**
   - 概述本工程的核心功能与支持特性。

2. **快速入门**
   - 提供多种开发模式的安装与使用说明。
   - 覆盖 Keil C51、VSCode + EIDE 插件两种开发方式。

3. **工程结构**
   - 详细说明项目代码目录及其作用，帮助开发者快速理解工程组织结构。

4. **构建与烧录**
   - 详细介绍基于 **VSCode + EIDE** 的自动化编译与固件下载方式。

5. **开发与调试**
   - 简要说明固件位置和调试工具的使用。

6. **资源与支持**
   - 提供项目所需的工具下载链接，以及技术支持联系方式。

7. **贡献指南**
   - 提供贡献代码的方式，欢迎社区开发者参与。


## 1. 功能特性

本工程具备以下核心功能：

### 1.1 AriesSDK 支持

- 提供 AriesSDK 的 **I2C 接口移植**，快速适配 Phoenix 核心板。
- 支持多种外设通信协议，便于开发者扩展自己的外设功能。

### 1.2 Application 示例

- 提供丰富的外设示例，如 GPIO、I2C、USB-CDC 等，覆盖常见的嵌入式开发需求。
- 示例代码结构清晰，便于开发者快速上手。

### 1.3 多工具链支持

- **Keil C51**：支持 8051 编译器，适合传统嵌入式开发流程。
- **VSCode + EIDE 插件**：轻量化开发模式，易于集成任务管理和自动化构建。

## 2. 快速入门

### 2.1 下载代码与初始化

通过以下命令克隆本仓库，并初始化子模块：

```bash
git clone https://gitee.com/WeCanSTU/Draco-AriesSDK.git
cd Draco-AriesSDK
git submodule update --init --recursive
```

### 2.2 开发模式说明

#### 方式一：Keil C51 开发模式

1. 安装 **Keil C51**
   - [点击下载 Keil C51](https://www.keil.com/download/product/)

2. 打开 Keil 工程文件
   - 在工程目录 `CA51F005/App` 下，找到 `CA51F005-App.uvprojx` 文件并双击打开。

3. 编译与烧录
   - 按 **F7** 进行代码编译，确保无错误。
   - 命令行进入`CA51F005/App`目录下
   ```
   tsc-cli flash output\CA51F005-App.bin
   ```


#### 方式二：VSCode + EIDE 插件开发模式

1. 安装前置工具
   - **Keil C51**：同上，确保安装完成。
   - **TechSync 工具**：安装 [TechSync 工具](https://gitee.com/WeCanSTU/install)，用于固件烧录和日志调试。
   - **VSCode**：下载 [VSCode](https://code.visualstudio.com/)，并安装插件 **EIDE（Embedded IDE For VSCode）**。

2. 打开 EIDE 工程
   - 在 VSCode 中打开本仓库路径下的 `CA51F005-App/App` 目录，双击 `App.code-workspace` 文件以工作区方式加载工程。

3. 编译与下载固件
   - 在 EIDE 工具栏中，选择 **Build** 指令进行编译。
   - 选择 **Download**，通过 **TechSync 工具** 将固件烧录到设备中。


## 3. 工程结构

以下是项目的核心目录说明：

```plaintext
.
├── CA51F005                # Draco 天龙座 核心板相关工程
│   ├── App                 # 应用工程目录
│   │   ├── .eide           # EIDE 工程配置
│   │   └── User            # 用户代码
│   └── Port                # 移植代码目录
├── resource                # 其他相关资源
└── Sdk                     # SDK 及驱动支持
    ├── AriesSDK            # AriesSDK 代码
    └── CA51F005            # CA51F005 平台支持包
```

## 4. 构建与烧录

本节将详细说明如何使用 **VSCode + EIDE** 环境，通过 **EIDE**完成工程的编译与固件下载。

### 使用步骤

#### 1. 打开 VSCode

使用VSCode的 EIDE插件打开位于 `CA51F005-App/App` 目录下的`App.code-workspace`文件。

#### 2. 编译工程

点击EIDE控件的`Build`或者`Rebuild`(`Ctrl + F7`)执行项目编译。

#### 3. 下载

点击EIDE控件的`Program Flash`(`F8`)执行固件下载更新。


## 5. 开发与调试

- 编译后的固件位于 `output` 文件夹中。

- 使用 **TechSync 及 tsc-cli 工具** 进行远程多人实时监控设备的日志

  ```bash
  tsc-cli serial monitor -f -d -p {串口号}
  ```

  - Windows上实时捕获的设备日志

   ![win-log](https://gitee.com/WeCanSTU/Draco-AriesSDK/raw/master/resources/win-log.png)

## 6. 资源与支持

- **论坛**: [AriesSDK Forum](https://forum.umetav.cn)
- **QQ群**: 786239575
- **技术支持邮箱**: [tech@umetav.cn](https://gitee.com/link?target=mailto%3Atech@umetav.cn)

## 7. 贡献指南

欢迎开发者提交 Issue 或 Pull Request，贡献代码或提出改进建议！

