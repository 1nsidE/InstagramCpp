#include "CommentsInfo.h"

namespace Instagram {

CommentsInfo::CommentsInfo() : BaseResult{}, comments(0) {}

CommentsInfo::CommentsInfo(const CommentsInfo& comments_info) : BaseResult{ comments_info }, comments{ comments_info.comments } {}

CommentsInfo::CommentsInfo(CommentsInfo&& comments_info) : BaseResult{ std::forward<BaseResult>(comments_info) }, comments{ std::move(comments_info.comments) } {}

CommentsInfo::CommentsInfo(const char* err_msg) : BaseResult{ err_msg }, comments(0) {}

CommentsInfo::CommentsInfo(const std::string& err_msg) : BaseResult{ err_msg }, comments(0) {}

CommentsInfo::~CommentsInfo() {}

CommentsInfo& CommentsInfo::operator=(const CommentsInfo& comments_info) {
    if (this == &comments_info) {
        return *this;
    }

    BaseResult::operator=(comments_info);

    comments = comments_info.comments;
    return *this;
}

CommentsInfo& CommentsInfo::operator=(CommentsInfo&& comments_info) {
    if (this == &comments_info) {
        return *this;
    }

    BaseResult::operator=(std::forward<BaseResult>(comments_info));
    comments = std::move(comments_info.comments);

    return *this;
}

const std::vector<CommentInfo>& CommentsInfo::get_comments() const noexcept {
    return comments;
}

CommentInfo& CommentsInfo::operator[](size_t n) {
    return comments[n];
}

const CommentInfo& CommentsInfo::operator[](size_t n) const {
    return comments[n];
}

CommentsInfo::iterator CommentsInfo::begin() {
    return comments.begin();
}

CommentsInfo::iterator CommentsInfo::end() {
    return comments.end();
}

CommentsInfo::const_iterator CommentsInfo::begin() const {
    return comments.begin();
}

CommentsInfo::const_iterator CommentsInfo::end() const {
    return comments.end();
}

void CommentsInfo::add_comment(const CommentInfo& comment_info) {
    comments.push_back(comment_info);
}

void CommentsInfo::add_comment(CommentInfo&& comment_info) {
    comments.push_back(std::forward<CommentInfo>(comment_info));
}

CommentsInfo& CommentsInfo::operator<<(const CommentInfo& comment_info) {
    add_comment(comment_info);
    return *this;
}

CommentsInfo& CommentsInfo::operator<<(CommentInfo&& comment_info) {
    add_comment(std::forward<CommentInfo>(comment_info));
    return *this;
}

}
