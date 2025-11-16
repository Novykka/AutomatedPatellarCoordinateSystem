#ifndef PATELLA_ANALYZER_H
#define PATELLA_ANALYZER_H

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vector>
#include "geometry.h"
#include "vtk_utils.h"

class PatellaAnalyzer {
public:
    // 构造函数：传入髌骨PolyData
    explicit PatellaAnalyzer(vtkSmartPointer<vtkPolyData> polyData);
    
    // 执行完整分析流程
    void analyze();
    
    // 获取分析结果（只读）
    Vector3D getCentroid() const { return m_centroid; }          // 面积加权面心
    double getSurfaceArea() const { return m_surfaceArea; }      // 总表面积
    Vector3D getAnteriorNormal() const { return m_anteriorNormal; } // 前面法向量
    double getPatellaLength() const { return m_patellaLength; }  // 髌骨长度

private:
    // 内部处理步骤（封装细节）
    void computeSurfaceArea();      // 计算总表面积
    void computeCentroid();         // 计算面积加权面心
    void fitAnteriorPlane();        // 拟合前面法向量（核心算法，参考论文）
    void computePatellaLength();    // 计算髌骨长度
    
    // 数据成员（隐藏内部状态）
    vtkSmartPointer<vtkPolyData> m_polyData;       // 原始模型
    std::vector<std::vector<Vector3D>> m_cellPoints;// 所有面的点（Vector3D格式）
    int m_cellCount;                                // 面数
    int m_pointCount;                               // 点数
    
    // 分析结果
    Vector3D m_centroid;         // 面积加权面心
    double m_surfaceArea;        // 总表面积
    Vector3D m_anteriorNormal;   // 前面法向量
    double m_patellaLength;      // 髌骨长度
};

#endif // PATELLA_ANALYZER_H
