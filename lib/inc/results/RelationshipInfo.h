#ifndef RELATIONSHIP_INFO_H
#define RELATIONSHIP_INFO_H

#include "BaseResult.h"

namespace Instagram{

class EXPORT_INSTAGRAM RelationshipInfo : public BaseResult{
public:
    RelationshipInfo();
    RelationshipInfo(const std::string& incoming, const std::string& outgoing);
    RelationshipInfo(const RelationshipInfo& relInfo);
    RelationshipInfo(RelationshipInfo&& relInfo);

    RelationshipInfo(const char* errMsg);
    RelationshipInfo(const std::string& errMsg);

    ~RelationshipInfo();

    const std::string& incomingStatus() const noexcept;
    const std::string& outgoingStatus() const noexcept;

    void setIncomingStatus(const std::string& status);
    void setOutgoingStatus(const std::string& status);
private:
    std::string m_incomingStatus{};
    std::string m_outgoingStatus{};

    friend void swap(RelationshipInfo& first, RelationshipInfo& second);
};

}

#endif

