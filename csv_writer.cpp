#include "csv_writer.h"
#include <sstream>

CSVWriter::CSVWriter(const std::string& filePath) {
    m_file.open(filePath);
    if (!m_file.is_open()) {
        throw std::runtime_error("无法打开CSV文件: " + filePath);
    }
}

CSVWriter::~CSVWriter() {
    if (m_file.is_open()) {
        m_file.close();
    }
}

void CSVWriter::writeRow(const std::vector<std::string>& fields) {
    if (fields.empty()) return;

    std::ostringstream line;
    for (size_t i = 0; i < fields.size(); ++i) {
        if (i > 0) line << ",";
        line << escapeField(fields[i]);
    }
    line << "\n";

    m_file << line.str();
    if (!m_file.good()) {
        throw std::runtime_error("CSV行写入失败");
    }
}

void CSVWriter::writeHeader(const std::vector<std::string>& headers) {
    writeRow(headers);
}

std::string CSVWriter::escapeField(const std::string& field) {
    // 检查是否含逗号、引号或换行
    if (field.find(',') == std::string::npos && 
        field.find('"') == std::string::npos && 
        field.find('\n') == std::string::npos) {
        return field;
    }

    // 转义双引号（替换为两个双引号）
    std::string escaped = field;
    size_t pos = 0;
    while ((pos = escaped.find('"', pos)) != std::string::npos) {
        escaped.replace(pos, 1, "\"\"");
        pos += 2;
    }

    // 用双引号包裹字段
    return "\"" + escaped + "\"";
}
