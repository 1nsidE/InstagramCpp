//
// Created by inside on 3/12/16.
//

#include "FormData.h"
#include "Http.h"

namespace Http {

FormData::FormData(){}

FormData::FormData(const std::string &boundary) : m_boundary{boundary} {}

FormData::FormData(const FormData& formData) : m_data{formData.m_data}, m_boundary{formData.m_boundary} {}

FormData::FormData(FormData&& formData) : FormData{}{
    swap(*this, formData);
} 

void FormData::addPair(const std::string &name, const std::string &value) {
    m_data[name] = value;
}

const std::string& FormData::operator[](const std::string& key) const {
    const static std::string emptyName = "";
    return m_data.count(key) ? m_data.at(key) : emptyName;
}

std::string& FormData::operator[](const std::string& key) {
    return m_data[key];
}

const std::string FormData::getString() const {
    if (m_data.size() == 0) {
        return "";
    }
    std::string result{};

    for (const auto &p : m_data) {
        result.append("--").append(m_boundary).append(CRLF);
        result.append(CONTENT_DISP).append("\"").append(p.first).append("\"").append(CRLF).append(CRLF);
        result.append(p.second).append(CRLF);
    }
    result.append("--").append(m_boundary).append("--");
    return result;
}

std::string FormData::contentType() const {
    std::string content_type {CONTENT_TYPE};
    content_type.append(m_boundary);
    return content_type;
}

void swap(FormData& first, FormData& second){
    using std::swap;
    swap(first.m_data, second.m_data);
    swap(first.m_boundary, second.m_boundary);
}

}
