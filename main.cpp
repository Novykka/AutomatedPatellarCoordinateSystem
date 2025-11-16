#include <iostream>
#include <stdexcept>
#include "vtk_utils.h"          // VTK模型读取
#include "patella_analyzer.h"  // 髌骨分析核心
#include "csv_writer.h"        // CSV写入
#include "visualization.h"     // 可视化
#include "geometry.h"          // 几何数据结构（Vector3D）

int main() {
    try {
        // ------------------------------
        // 1. 输入配置（可扩展为命令行参数）
        // ------------------------------
        const std::string stl_path = "patella.stl";   // 输入STL路径
        const std::string csv_path = "patella_results.csv"; // 输出CSV路径

        // ------------------------------
        // 2. 读取STL模型（依赖vtk_utils）
        // ------------------------------
        std::cout << "[INFO] 读取STL文件: " << stl_path << std::endl;
        auto poly_data = readSTL(stl_path);
        if (!poly_data) {
            throw std::runtime_error("STL文件读取失败: " + stl_path);
        }
        std::cout << "[INFO] STL读取成功（点数: " << poly_data->GetNumberOfPoints() 
                  << ", 面数: " << poly_data->GetNumberOfCells() << "）" << std::endl;

        // ------------------------------
        // 3. 髌骨分析（依赖patella_analyzer）
        // ------------------------------
        std::cout << "[INFO] 开始分析髌骨形态..." << std::endl;
        PatellaAnalyzer analyzer(poly_data);
        analyzer.analyze();
        std::cout << "[INFO] 分析完成！" << std::endl;

        // ------------------------------
        // 4. 获取分析结果
        // ------------------------------
        const Vector3D centroid = analyzer.getCentroid();          // 面积加权面心
        const double surface_area = analyzer.getSurfaceArea();    // 总表面积
        const Vector3D anterior_normal = analyzer.getAnteriorNormal(); // 前面法向量
        const double patella_length = analyzer.getPatellaLength();// 髌骨长度

        // ------------------------------
        // 5. 写入CSV（依赖csv_writer）
        // ------------------------------
        std::cout << "[INFO] 写入结果到CSV: " << csv_path << std::endl;
        CSVWriter csv_writer(csv_path);
        csv_writer.writeHeader({"Metric", "Value"}); // 表头
        csv_writer.writeRow({"Area-Weighted Centroid (X)", std::to_string(centroid.x)});
        csv_writer.writeRow({"Area-Weighted Centroid (Y)", std::to_string(centroid.y)});
        csv_writer.writeRow({"Area-Weighted Centroid (Z)", std::to_string(centroid.z)});
        csv_writer.writeRow({"Total Surface Area (mm²)", std::to_string(surface_area)});
        csv_writer.writeRow({"Anterior Plane Normal (X)", std::to_string(anterior_normal.x)});
        csv_writer.writeRow({"Anterior Plane Normal (Y)", std::to_string(anterior_normal.y)});
        csv_writer.writeRow({"Anterior Plane Normal (Z)", std::to_string(anterior_normal.z)});
        csv_writer.writeRow({"Patella Length (mm)", std::to_string(patella_length)});
        std::cout << "[INFO] CSV写入完成！" << std::endl;

        // ------------------------------
        // 6. 可视化（依赖visualization）
        // ------------------------------
        std::cout << "[INFO] 初始化可视化窗口..." << std::endl;
        Visualizer visualizer;
        visualizer.addPolyData(poly_data, Vector3D(0.8, 0.8, 0.8)); // 灰色显示模型
        visualizer.addSphereMarker(centroid, 0.5, Vector3D(1, 0, 0)); // 红色标记面心
        visualizer.addLineMarker(
            centroid - Vector3D(0, 0, patella_length/2),  // 长度起点
            centroid + Vector3D(0, 0, patella_length/2),  // 长度终点
            Vector3D(0, 1, 0), 2.0                      // 绿色线，宽度2
        );
        std::cout << "[INFO] 显示可视化窗口..." << std::endl;
        visualizer.show();

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "[ERROR] 未知错误！" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
