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

    ResultCollection() : BaseResult{}, elements(0){}
    ResultCollection(const ResultCollection<T>& resultCollection) : BaseResult{resultCollection}, elements{resultCollection.elements}{}
    ResultCollection(ResultCollection<T>&& resultCollection) : BaseResult{resultCollection}, elements{std::move(resultCollection.elements)}{}
    ResultCollection(const char* errMsg) : BaseResult{errMsg}, elements(0){}
    ResultCollection(const std::string& errMsg) : BaseResult{errMsg}, elements(0){}
    
    ResultCollection<T>& operator=(const ResultCollection<T>& resultCollection){
        if(this == &resultCollection){
            return *this;
        }
        
        BaseResult::operator=(resultCollection);
        elements = resultCollection.elements;
        
        return *this;
    }
    
    ResultCollection<T>& operator=(ResultCollection<T>&& resultCollection){
        if(this == &resultCollection){
            return *this;
        }
        
        BaseResult::operator=(resultCollection);
        elements = resultCollection.elements;
        
        return *this;
    }
    
    iterator begin() noexcept{
        return elements.begin();
    }
    
    iterator end() noexcept{
        return elements.end();
    }
    
    const_iterator begin() const noexcept{
        return elements.begin();
    }
    
    const_iterator end() const noexcept{
        return elements.end();
    }
    
    const std::vector<T>& get_elements() const noexcept{
        return elements;
    }
    
    const T& get(size_t n) const {
        return elements[n];
    }
    
    T& get(size_t n){
        return elements[n];
    }
    
    const T& operator[](size_t n) const {
        return elements[n];
    }
    
    T& operator[](size_t n){
        return elements[n];
    }
    
    ResultCollection<T>& operator<<(T&& element){
        elements.push_back(std::forward<T>(element));
        return *this;
    }

    ResultCollection<T>& operator<<(T& element){
        elements.push_back(element);
        return *this;
    }
    
    void add_element(T&& element){
        elements.push_back(std::forward<T>(element));
    }
    
    void clear(){
        elements.clear();
    }
    
private:
    std::vector<T> elements;
};

}
#endif
