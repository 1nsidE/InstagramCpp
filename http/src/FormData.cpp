//
// Created by inside on 3/12/16.
//

#include "FormData.h"
#include "Http.h"

namespace Http {

FormData::FormData(const std::string &_boundary) : boundary(_boundary) {}

FormData::FormData(const FormData& form_data) : data { form_data.data },
boundary { form_data.boundary } {}

FormData::FormData(FormData&& form_data) : data { std::move(form_data.data) },
boundary { std::move(form_data.boundary) } {}
void FormData::add_pair(const std::string &name, const std::string &value) {
    data[name] = value;
}

const std::string& FormData::operator[](const std::string& name) const {
    const static std::string empty_name = "";
    return data.count(name) ? data.at(name) : empty_name;
}

std::string& FormData::operator[](const std::string& key) {
    return data[key];
}

const std::string FormData::get_string() const {
    if (data.size() == 0) {
        return "";
    }
    std::string result("");

    for (const auto &p : data) {
        result.append("--").append(boundary).append(CRLF);
        result.append(CONTENT_DISP).append("\"").append(p.first).append("\"").append(CRLF).append(CRLF);
        result.append(p.second).append(CRLF);
    }
    result.append("--").append(boundary).append("--");
    return result;
}

std::string FormData::get_content_type() const {
    std::string content_type { CONTENT_TYPE };
    content_type.append(boundary);
    return content_type;
}

}
