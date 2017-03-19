#ifndef RESULT_COLLECTION_HPP
#define RESULT_COLLECTION_HPP

#include <vector>
#include "BaseResult.h"

namespace Instagram{
    
template<typename T>
class ResultCollection : public BaseResult
{
public:
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    ResultCollection() : BaseResult{}, m_elements(0){}
    ResultCollection(const ResultCollection<T>& resultCollection) : BaseResult{resultCollection}, m_elements{resultCollection.m_elements}{}
    ResultCollection(ResultCollection<T>&& resultCollection) : BaseResult{resultCollection}, m_elements{std::move(resultCollection.m_elements)}{}
    ResultCollection(const char* errMsg) : BaseResult{errMsg}, m_elements(0){}
    ResultCollection(const std::string& errMsg) : BaseResult{errMsg}, m_elements(0){}
    
    ResultCollection<T>& operator=(const ResultCollection<T>& resultCollection){
        if(this == &resultCollection){
            return *this;
        }
        
        BaseResult::operator=(resultCollection);
        m_elements = resultCollection.m_elements;
        
        return *this;
    }
    
    ResultCollection<T>& operator=(ResultCollection<T>&& resultCollection){
        if(this == &resultCollection){
            return *this;
        }
        
        BaseResult::operator=(resultCollection);
        m_elements = resultCollection.m_elements;
        
        return *this;
    }
    
    iterator begin() noexcept{
        return m_elements.begin();
    }
    
    iterator end() noexcept{
        return m_elements.end();
    }
    
    const_iterator begin() const noexcept{
        return m_elements.begin();
    }
    
    const_iterator end() const noexcept{
        return m_elements.end();
    }
    
    const std::vector<T>& elements() const noexcept{
        return m_elements;
    }
    
    const T& get(size_t n) const {
        return m_elements[n];
    }
    
    T& get(size_t n){
        return m_elements[n];
    }
    
    const T& operator[](size_t n) const {
        return m_elements[n];
    }
    
    T& operator[](size_t n){
        return m_elements[n];
    }
    
    ResultCollection<T>& operator<<(T&& element){
        m_elements.push_back(std::forward<T>(element));
        return *this;
    }
    
    void addElement(T&& element){
        m_elements.push_back(std::forward<T>(element));
    }

    size_t size() const noexcept{
        return m_elements.size();
    }
    
    void clear(){
        m_elements.clear();
    }
    
private:
    std::vector<T> m_elements;
};

}
#endif
