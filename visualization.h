#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include "geometry.h"

class Visualizer {
public:
    Visualizer();
    
    // 添加PolyData模型（如髌骨）
    void addModel(vtkSmartPointer<vtkPolyData> polyData, const Vector3D& color = Vector3D(0.8, 0.8, 0.8));
    // 添加球形标记（如面心）
    void addSphereMarker(const Vector3D& center, double radius, const Vector3D& color);
    // 添加线段标记（如最长轴）
    void addLineMarker(const Vector3D& p1, const Vector3D& p2, const Vector3D& color, double lineWidth = 2.0);
    // 显示可视化窗口
    void show();
    
private:
    vtkSmartPointer<vtkRenderer> m_renderer;               // 渲染器
    vtkSmartPointer<vtkRenderWindow> m_renderWindow;       // 渲染窗口
    vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;// 交互器
};

#endif // VISUALIZATION_H
