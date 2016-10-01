#include "RelationshipInfo.h"

namespace Instagram {

RelationshipInfo::RelationshipInfo() : BaseResult{}, incoming_status{ "" }, outgoing_status{ "" } {}

RelationshipInfo::RelationshipInfo(const std::string& incoming, const std::string& outgoing) : BaseResult{}, incoming_status{ incoming }, outgoing_status{ outgoing } {}

RelationshipInfo::RelationshipInfo(const RelationshipInfo& rel_info) : BaseResult{ rel_info }, incoming_status{ rel_info.incoming_status }, outgoing_status{ rel_info.outgoing_status } {}

RelationshipInfo::RelationshipInfo(RelationshipInfo&& rel_info) : BaseResult{ std::forward<BaseResult>(rel_info) }, incoming_status{ std::move(rel_info.incoming_status) }, outgoing_status{ std::move(rel_info.outgoing_status) } {}

RelationshipInfo::RelationshipInfo(const char* err_msg) : BaseResult{ err_msg }, incoming_status{ "" }, outgoing_status{ "" } {}

RelationshipInfo::RelationshipInfo(const std::string& err_msg) : BaseResult{ err_msg }, incoming_status{ "" }, outgoing_status{ "" } {}

RelationshipInfo::~RelationshipInfo() {}

const std::string& RelationshipInfo::get_incoming_status() const noexcept {
    return incoming_status;
}

const std::string& RelationshipInfo::get_outgoing_status() const noexcept {
    return outgoing_status;
}

void RelationshipInfo::set_incoming_status(const std::string& status) {
    incoming_status = status;
}

void RelationshipInfo::set_outgoing_status(const std::string& status) {
    outgoing_status = status;
}

}
