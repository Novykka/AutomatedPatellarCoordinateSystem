#include "vtk_utils.h"
#include <vtkSTLReader.h>
#include <vtkCell.h>
#include <vtkPoints.h>

vtkSmartPointer<vtkPolyData> readSTL(const std::string& filePath) {
    auto reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(filePath.c_str());
    reader->Update();
    return reader->GetOutput();
}

std::vector<std::vector<Vector3D>> getCellPoints(vtkSmartPointer<vtkPolyData> polyData) {
    std::vector<std::vector<Vector3D>> cellPoints;
    int cellCount = polyData->GetNumberOfCells();
    for (int i = 0; i < cellCount; ++i) {
        auto cell = polyData->GetCell(i);
        std::vector<Vector3D> points;
        for (int j = 0; j < cell->GetNumberOfPoints(); ++j) {
            double coords[3];
            cell->GetPoint(j, coords);
            points.emplace_back(coords[0], coords[1], coords[2]);
        }
        cellPoints.push_back(points);
    }
    return cellPoints;
}
