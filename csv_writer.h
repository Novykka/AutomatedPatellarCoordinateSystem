#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

/**
 * @brief 封装CSV文件写入逻辑，支持表头和多行数据。
 */
class CSVWriter {
public:
    /**
     * @brief 构造函数，打开CSV文件。
     * @param filePath CSV文件路径（若文件存在会覆盖）。
     * @throw std::runtime_error 若文件无法打开。
     */
    explicit CSVWriter(const std::string& filePath);

    /**
     * @brief 析构函数，关闭文件。
     */
    ~CSVWriter();

    /**
     * @brief 写入一行数据（自动添加换行）。
     * @param fields 行数据的字段列表（自动处理逗号和引号）。
     */
    void writeRow(const std::vector<std::string>& fields);

    /**
     * @brief 写入表头（本质是调用writeRow）。
     * @param headers 表头字段列表。
     */
    void writeHeader(const std::vector<std::string>& headers);

private:
    /**
     * @brief 处理单个字段（转义逗号和引号）。
     * @param field 原始字段。
     * @return 处理后的字段（用双引号包裹含特殊字符的内容）。
     */
    std::string escapeField(const std::string& field);

    std::ofstream m_file; ///< 文件输出流
};

#endif // CSV_WRITER_H
