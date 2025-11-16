#ifndef VTK_UTILS_H
#define VTK_UTILS_H

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <string>

// 读取STL文件，返回PolyData
vtkSmartPointer<vtkPolyData> readSTL(const std::string& filePath);

// 将PolyData的点和面转换为Vector3D格式（方便几何计算）
std::vector<std::vector<Vector3D>> getCellPoints(vtkSmartPointer<vtkPolyData> polyData);

#endif // VTK_UTILS_H
