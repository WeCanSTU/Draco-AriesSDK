[中文](https://github.com/WeCanSTU/Draco-AriesSDK/blob/master/README_CN.md) / [English](https://github.com/WeCanSTU/Draco-AriesSDK/blob/master/README.md)

# Draco-AriesSDK Porting Project

This repository is a **[AriesSDK](https://gitee.com/WeCanSTU/AriesSDK) software porting** project based on the **[Draco CA51F005 1T 8051 Core Board](https://gitee.com/WeCanSTU/Draco)**. It provides a complete software framework, Application examples, and supports multiple toolchains, helping developers quickly implement embedded project development, debugging, and deployment.


## Document Structure

1. **Features**
   - Overview of core functionality and supported features of this project.

2. **Quick Start**
   - Installation and usage instructions for multiple development modes.
   - Covers two development approaches: Keil C51 and VSCode + EIDE plugin.

3. **Project Structure**
   - Detailed explanation of project code directories and their purposes, helping developers quickly understand the project organization.

4. **Build and Flash**
   - Detailed introduction to automated compilation and firmware download using **VSCode + EIDE**.

5. **Development and Debugging**
   - Brief description of firmware location and debugging tool usage.

6. **Resources and Support**
   - Provides download links for tools required by the project, as well as technical support contact information.

7. **Contributing Guide**
   - Provides ways to contribute code, welcoming community developers to participate.


## 1. Features

This project has the following core features:

### 1.1 AriesSDK Support

- Provides **I2C interface porting** for AriesSDK, enabling quick adaptation to Phoenix core boards.
- Supports multiple peripheral communication protocols, facilitating developers to extend their own peripheral functionality.

### 1.2 Application Examples

- Provides rich peripheral examples such as GPIO, I2C, USB-CDC, etc., covering common embedded development needs.
- Example code has a clear structure, making it easy for developers to get started quickly.

### 1.3 Multi-Toolchain Support

- **Keil C51**: Supports 8051 compiler, suitable for traditional embedded development workflows.
- **VSCode + EIDE Plugin**: Lightweight development mode, easy to integrate task management and automated builds.

## 2. Quick Start

### 2.1 Download Code and Initialize

Clone this repository and initialize submodules using the following commands:

```bash
git clone https://gitee.com/WeCanSTU/Draco-AriesSDK.git
cd Draco-AriesSDK
git submodule update --init --recursive
```

### 2.2 Development Mode Instructions

#### Method 1: Keil C51 Development Mode

1. Install **Keil C51**
   - [Download Keil C51](https://www.keil.com/download/product/)

2. Open Keil Project File
   - In the project directory `CA51F005/App`, find the `CA51F005-App.uvprojx` file and double-click to open it.

3. Compile and Flash
   - Press **F7** to compile the code, ensuring no errors.
   - Navigate to the `CA51F005/App` directory in the command line
   ```
   tsc-cli flash output\CA51F005-App.bin
   ```


#### Method 2: VSCode + EIDE Plugin Development Mode

1. Install Prerequisites
   - **Keil C51**: Same as above, ensure installation is complete.
   - **TechSync Tool**: Install [TechSync Tool](https://gitee.com/WeCanSTU/install) for firmware flashing and log debugging.
   - **VSCode**: Download [VSCode](https://code.visualstudio.com/), and install the **EIDE (Embedded IDE For VSCode)** plugin.

2. Open EIDE Project
   - Open the `CA51F005-App/App` directory under this repository path in VSCode, and double-click the `App.code-workspace` file to load the project as a workspace.

3. Compile and Download Firmware
   - In the EIDE toolbar, select **Build** command to compile.
   - Select **Download** to flash the firmware to the device via **TechSync Tool**.


## 3. Project Structure

The following is a description of the core directories of the project:

```plaintext
.
├── CA51F005                # Draco core board related projects
│   ├── App                 # Application project directory
│   │   ├── .eide           # EIDE project configuration
│   │   └── User            # User code
│   └── Port                # Porting code directory
├── resource                # Other related resources
└── Sdk                     # SDK and driver support
    ├── AriesSDK            # AriesSDK code
    └── CA51F005            # CA51F005 platform support package
```

## 4. Build and Flash

This section will detail how to use the **VSCode + EIDE** environment to complete project compilation and firmware download through **EIDE**.

### Usage Steps

#### 1. Open VSCode

Open the `App.code-workspace` file located in the `CA51F005-App/App` directory using VSCode's EIDE plugin.

#### 2. Compile Project

Click `Build` or `Rebuild` (`Ctrl + F7`) in the EIDE controls to execute project compilation.

#### 3. Download

Click `Program Flash` (`F8`) in the EIDE controls to execute firmware download and update.


## 5. Development and Debugging

- Compiled firmware is located in the `output` folder.

- Use **TechSync and tsc-cli tools** for remote multi-user real-time monitoring of device logs

  ```bash
  tsc-cli serial monitor -f -d -p {serial port}
  ```

  - Device logs captured in real-time on Windows

   ![win-log](https://github.com/WeCanSTU/Draco-AriesSDK/blob/master/resources/win-log.png)

## 6. Resources and Support

- **Forum**: [AriesSDK Forum](https://forum.umetav.cn)
- **QQ Group**: 786239575
- **Technical Support Email**: [tech@umetav.cn](https://gitee.com/link?target=mailto%3Atech%40umetav.cn)

## 7. Contributing Guide

Developers are welcome to submit Issues or Pull Requests, contribute code, or suggest improvements!

