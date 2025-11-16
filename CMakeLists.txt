cmake_minimum_required(VERSION 3.10)
project(PatellaAnalysis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找VTK库
find_package(VTK REQUIRED COMPONENTS 
  CommonCore
  CommonDataModel
  IOGeometry
  RenderingCore
  RenderingOpenGL2
  InteractionStyle
)

# 头文件目录
include_directories(include)

# 源文件
set(SOURCES
  src/csv_writer.cpp
  src/geometry.cpp
  src/patella_analyzer.cpp
  src/vtk_utils.cpp
  src/visualization.cpp
  src/main.cpp
)

# 生成可执行文件
add_executable(patella_analysis ${SOURCES})

# 链接VTK库
target_link_libraries(patella_analysis PRIVATE ${VTK_LIBRARIES})

# VTK模块初始化
vtk_module_autoinit(
  TARGETS patella_analysis
  MODULES ${VTK_LIBRARIES}
)
