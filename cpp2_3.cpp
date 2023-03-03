#include <iostream>
#include <string>
#include <exception>

class ExceptionVectorInt : std::exception {
private:
    std::string whatStr;
public:
    ExceptionVectorInt (std::string &&whatStr) noexcept : whatStr(std::move(whatStr)) {}
    ExceptionVectorInt (const std::string &whatStr) noexcept : whatStr(std::move(whatStr)) {}
    ~ExceptionVectorInt () noexcept = default;
    
    const char *what() const noexcept override{
        return whatStr.c_str();
    }
};

class VectorInt{
private:
    int *arr;
    int size;
    int capacity;
    void add_capacity(){
        this->capacity *= 2;
        int *var = arr;
        arr = new int [this->capacity];
        if(!arr)
            throw ExceptionVectorInt("Memory was not allocated in the <add_capacity>");
        for(size_t idx_i = 0; idx_i < this->size; ++idx_i){
            arr[idx_i] = std::move(var[idx_i]);
        }
        delete[] var;
    }
    void remove_capacity(){
        this->capacity = this->size;
        int *var = arr;
        arr = new int [this->capacity];
        if(!arr)
            throw ExceptionVectorInt("Memory was not allocated in the <remove_capacity>");
        for(size_t idx_i = 0; idx_i < this->size; ++idx_i){
            arr[idx_i] = std::move(var[idx_i]);
        }
        delete[] var;
    }
public:
    VectorInt(){
        capacity = 1;
        size = 0;
        this->arr = new int [capacity];
        if(!arr)
            throw ExceptionVectorInt("Memory was not allocated in the <constructor>");
    }
    VectorInt(const int& capacity){
        this->size = 0;
        this->capacity = capacity;
        this->arr = new int [capacity];
        if(!arr)
          throw ExceptionVectorInt("Memory was not allocated in the <constructor>");  
    }
    ~VectorInt(){delete[] arr;}
    void pushBack(const int &var){
        if(this->size == this->capacity)
            add_capacity();
            arr[this->size] = var;
            ++this->size;
    }
    void pushFront(const int &var){
        if(this->size == this->capacity)
            add_capacity();
        int *var_arr = this->arr;
        arr = new int [this->capacity];
        if(!arr)
            throw ExceptionVectorInt("Memory was not allocated in the <push_front>");
        for(size_t idx_i = 0; idx_i < this->size; ++idx_i){
            arr[idx_i + 1] = std::move(var_arr[idx_i]);
        }
        delete[] var_arr;
        arr[0] = var;
        ++this->size;
    }
    void insert(const int &var, const int& index){
        if(at(index)){
            if(this->size == this->capacity)
                add_capacity();
            
            int *var_arr = this->arr;
            arr = new int [capacity];
            if(!arr)
                throw ExceptionVectorInt("Memory was not allocated in the <insert>");
            size_t idx_k = 0;
            for(size_t idx_i = 0; idx_i <= size; ++idx_i){
                if(idx_i == index)
                    ++idx_i;
                arr[idx_i] = std::move(var_arr[idx_k]);
                ++idx_k;
            }
            delete[] var_arr;
            arr[index] = var;
            ++this->size;
        }else
            throw ExceptionVectorInt("Wrong index, array size is smaller <insert>");
    }
    bool at(const int &index){
        if(index <= size)
            return true;
        return false;
    }
    const bool at(const int &index)const{
        if(index <= size)
            return true;
        return false;
    }
    int &operator[] (const int &index){
        if(!at(index)){
            throw ExceptionVectorInt("Wrong index, array size is smaller <[]>");
        }
        return arr[index];
    }
    const int &operator[]  (const int &index)const {
        if(!at(index)){
            throw ExceptionVectorInt("Wrong index, array size is smaller <[]>");
        }
        return arr[index];
    }
    int get_size() const{return this->size;}
    int get_capacity() const{return this->capacity;}
    friend std::ostream &operator<< (std::ostream &out,const VectorInt & var){
        for(size_t idx_i = 0; idx_i < var.get_size(); ++idx_i ){
            out << var[idx_i] << '\t';
        }
        return out;
    }
};

int main(){
try
{
    VectorInt arr(10);
    std::cout << arr.get_size() << '\t' << arr.get_capacity() << std::endl;
    arr.pushBack(2);
    arr.pushFront(1);
    arr.insert(99,1);
    std::cout << arr.get_size() << '\t' << arr.get_capacity() << std::endl;
    std::cout << arr << std::endl;
    // arr.insert(10,11);
    std::cout << arr[0] << std::endl;
    // std::cout << arr[10] << std::endl;
}
catch(const ExceptionVectorInt &e)
{
    std::cerr << e.what() << '\n';
}

 
}