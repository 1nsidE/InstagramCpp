#ifndef RELATIONSHIP_INFO_H
#define RELATIONSHIP_INFO_H

#include "BaseResult.h"

namespace Instagram{

class EXPORT_INSTAGRAM RelationshipInfo : public BaseResult{
public:
    RelationshipInfo();
    RelationshipInfo(const std::string& incoming, const std::string& outgoing);
    RelationshipInfo(const RelationshipInfo& rel_info);
    RelationshipInfo(RelationshipInfo&& rel_info);

    RelationshipInfo(const char* err_msg);
    RelationshipInfo(const std::string& err_msg);

    ~RelationshipInfo();

    const std::string& get_incoming_status() const noexcept;
    const std::string& get_outgoing_status() const noexcept;

    void set_incoming_status(const std::string& status);
    void set_outgoing_status(const std::string& status);
private:
    std::string incoming_status;
    std::string outgoing_status;
};

}

#endif

