# AutomatedPatellarCoordinateSystem
# 髌骨形态分析代码（论文配套实现）

本代码是论文《3D patellar shape is associated with patellar dislocation: An automated coordinate algorithm and statistical shape modeling analysis》的工程实现，用于验证论文中的髌骨三维形态分析方法（曲率计算、平面拟合、坐标系建立等）。核心算法与创意细节请参考论文，代码仅提供可复现的工程框架。


## 1. 依赖环境
- VTK库（≥8.2）：用于三维模型读取、处理与可视化；
- C++编译器（支持C++11）：如GCC、Clang或MSVC；
- CMake（可选）：用于跨平台编译。


## 2. 编译与使用
1. 安装VTK库并配置环境变量（`VTK_DIR`指向VTK安装路径）；
2. 编译项目（如使用CMake生成Makefile，或直接导入IDE）；
3. 运行可执行文件，输入STL模型路径与参数（参数含义参考论文实验设置）。


## 3. 核心创意参考
代码中的关键算法（如面积加权面心计算、髌骨前面平面拟合、坐标系对齐）均来自论文中的方法，详细推导与验证请见：
> [作者]. [论文标题]. *[期刊/会议名称]*, [年份], [卷号]([期号]): [页码].


## 4. 注意事项
- 代码中的参数（如角度阈值`angleThre`、面积比阈值`AreaRatio1`）均为论文实验中的最优设置，修改可能影响结果；
- 可视化模块使用VTK默认配置，可调整`vtkRenderer`参数修改视角或颜色。


## 5. 版权声明
代码遵循MIT许可证，版权归[YAN Yichen/BUAA]所有。使用或修改代码时，请保留本声明。

---

# AutomatedPatellarCoordinateSystem (Paper Implementation)

This code is the engineering implementation of the paper "3D patellar shape is associated with patellar dislocation: An automated coordinate algorithm and statistical shape modeling analysis," used to validate the 3D patellar shape analysis methods (curvature calculation, plane fitting, coordinate system establishment, etc.) proposed in the paper. For core algorithms and creative details, please refer to the paper; the code provides only a reproducible engineering framework.

## 1. Dependencies
- VTK library (≥8.2): For 3D model reading, processing, and visualization;
- C++ compiler (supporting C++11): Such as GCC, Clang, or MSVC;
- CMake (optional): For cross-platform compilation.

## 2. Compilation and Usage
1. Install the VTK library and configure environment variables (`VTK_DIR` pointing to the VTK installation path);
2. Compile the project (e.g., using CMake to generate Makefile or directly importing into an IDE);
3. Run the executable file, input the STL model path and parameters (parameter meanings refer to the paper's experimental settings).

## 3. Core Creative Reference
Key algorithms in the code (such as area-weighted face center calculation, anterior patellar plane fitting, coordinate system alignment) are derived from the methods in the paper. For detailed derivation and validation, please refer to:
> [Author]. [Paper Title]. *[Journal/Conference Name]*, [Year], [Volume]([Issue]): [Page Number].

## 4. Notes
- Parameters in the code (such as angle threshold `angleThre`, area ratio threshold `AreaRatio1`) are the optimal settings from the paper's experiments; modifications may affect results;
- The visualization module uses VTK's default configuration; adjust `vtkRenderer` parameters to modify the view or colors.

## 5. Copyright Statement
The code is licensed under the MIT License, and the copyright belongs to [YAN Yichen/BUAA]. When using or modifying the code, please retain this statement.
