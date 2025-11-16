#include "patella_analyzer.h"
#include <vtkCell.h>
#include <vtkTriangle.h>
#include <algorithm>

PatellaAnalyzer::PatellaAnalyzer(vtkSmartPointer<vtkPolyData> polyData) 
    : m_polyData(polyData),
      m_cellCount(polyData->GetNumberOfCells()),
      m_pointCount(polyData->GetNumberOfPoints()),
      m_cellPoints(getCellPoints(polyData)) {}

void PatellaAnalyzer::analyze() {
    computeSurfaceArea();
    computeCentroid();
    fitAnteriorPlane();
    computePatellaLength();
}

void PatellaAnalyzer::computeSurfaceArea() {
    m_surfaceArea = 0.0;
    for (auto& cell : m_cellPoints) {
        if (cell.size() != 3) continue; // 只处理三角形面
        double area = vtkTriangle::ComputeArea(cell[0].x, cell[0].y, cell[0].z,
                                              cell[1].x, cell[1].y, cell[1].z,
                                              cell[2].x, cell[2].y, cell[2].z);
        m_surfaceArea += area;
    }
}

void PatellaAnalyzer::computeCentroid() {
    // 面积加权面心计算，参考论文公式(1)
    Vector3D centroidSum(0, 0, 0);
    double totalArea = 0.0;
    for (auto& cell : m_cellPoints) {
        if (cell.size() != 3) continue;
        double area = vtkTriangle::ComputeArea(cell[0].x, cell[0].y, cell[0].z,
                                              cell[1].x, cell[1].y, cell[1].z,
                                              cell[2].x, cell[2].y, cell[2].z);
        Vector3D cellCentroid = (cell[0] + cell[1] + cell[2]) * (1.0/3.0);
        centroidSum = centroidSum + cellCentroid * area;
        totalArea += area;
    }
    m_centroid = totalArea == 0 ? Vector3D() : centroidSum * (1.0/totalArea);
}

void PatellaAnalyzer::fitAnteriorPlane() {
    // 拟合髌骨前面法向量，方法参考论文Section 3.2
    // 1. 筛选符合条件的面（基于距离和角度阈值）
    std::vector<Vector3D> planePoints;
    double radiusThreshold = 10.0; // 论文实验设置
    double angleThreshold = 15.0;  // 论文实验设置
    for (auto& cell : m_cellPoints) {
        Vector3D cellCentroid = (cell[0] + cell[1] + cell[2]) * (1.0/3.0);
        double distToCentroid = distanceBetweenPoints(cellCentroid, m_centroid);
        double angleToForward = angleBetweenVectors(cellCentroid - m_centroid, Vector3D(0, 0, 1));
        if (distToCentroid <= radiusThreshold && angleToForward <= angleThreshold) {
            planePoints.push_back(cellCentroid);
        }
    }
    // 2. 平面拟合（最小二乘法，参考论文公式(3)）
    // 此处省略具体拟合代码，调用geometry模块的函数或第三方库
    m_anteriorNormal = Vector3D(0, 0, 1); // 示例值，实际需替换为拟合结果
}

void PatellaAnalyzer::computePatellaLength() {
    // 计算髌骨最长轴，参考论文Section 4.1
    double maxLength = 0.0;
    for (int i = 0; i < m_pointCount; ++i) {
        double p[3];
        m_polyData->GetPoint(i, p);
        Vector3D point(p[0], p[1], p[2]);
        double dist = distanceBetweenPoints(point, m_centroid);
        if (dist > maxLength) {
            maxLength = dist;
        }
    }
    m_patellaLength = maxLength * 2; // 直径作为长度
}
