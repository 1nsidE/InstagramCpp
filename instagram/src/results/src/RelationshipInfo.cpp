#include "RelationshipInfo.h"

namespace Instagram {

RelationshipInfo::RelationshipInfo() : BaseResult{} {}

RelationshipInfo::RelationshipInfo(const std::string& incoming, const std::string& outgoing) : 
                                                                    BaseResult{}, m_incomingStatus{incoming}, 
                                                                    m_outgoingStatus{outgoing} {}

RelationshipInfo::RelationshipInfo(const RelationshipInfo& relInfo) : BaseResult{relInfo}, 
                                                                    m_incomingStatus{relInfo.m_incomingStatus}, 
                                                                    m_outgoingStatus{relInfo.m_outgoingStatus} {}

RelationshipInfo::RelationshipInfo(RelationshipInfo&& relInfo) : RelationshipInfo{} {
    swap(*this, relInfo);
}

RelationshipInfo::RelationshipInfo(const char* errMsg) : BaseResult{errMsg}, m_incomingStatus{""}, m_outgoingStatus{""} {}

RelationshipInfo::RelationshipInfo(const std::string& errMsg) : BaseResult{errMsg}, m_incomingStatus{""}, m_outgoingStatus{""} {}

RelationshipInfo::~RelationshipInfo() {}

const std::string& RelationshipInfo::incomingStatus() const noexcept {
    return m_incomingStatus;
}

const std::string& RelationshipInfo::outgoingStatus() const noexcept {
    return m_outgoingStatus;
}

void RelationshipInfo::setIncomingStatus(const std::string& status) {
    m_incomingStatus = status;
}

void RelationshipInfo::setOutgoingStatus(const std::string& status) {
    m_outgoingStatus = status;
}

void swap(RelationshipInfo& first, RelationshipInfo& second){
    using std::swap;
    swap(static_cast<BaseResult&>(first), static_cast<BaseResult&>(second));

    swap(first.m_incomingStatus, second.m_incomingStatus);
    swap(first.m_outgoingStatus, second.m_outgoingStatus);
}

}
