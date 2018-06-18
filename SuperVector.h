//
// Created by Base on 2018-06-15.
//

#ifndef UNTITLED_SUPERVECTOR_H
#define UNTITLED_SUPERVECTOR_H

template <typename T>
    class vector {
    public:
        typedef T &          reference;
        typedef T *          iterator;
        typedef const T *    const_iterator;
        typedef unsigned int size_type;

        //Relocate:
        void reallocate();
        //Constructors:
        vector();
        explicit vector(size_t n);
        vector(size_t n, T val);
        explicit vector(std::initializer_list<T>);

        //Destructor:
        ~vector();

        //Iterators:
        iterator begin();
        iterator end();
        iterator insert(const_iterator, const T&);
        iterator insert(const_iterator, std::initializer_list<T>);
        iterator erase(const_iterator pos);

        //MODIFY ELEMENTS
        void push_back(T &&);
        void push_back(const T &);
        void pop_back();
        void clear();

        void resize(size_type);
        void shrink_to_fit();


        //CHECK IF EMPTY
        bool empty();
        //GET SIZE, CAPACITY
        size_type size();
        size_type capacity();

        //Print element
        reference operator [](size_type);

        //Operators
        bool operator == (vector<T> &);
        bool operator != (vector<T> &);
        bool operator >  (vector<T> &);
        bool operator <  (vector<T> &);
        bool operator >= (vector<T> &);
        bool operator <= (vector<T> &);

    private:
        size_t reserved_size = 4;
        size_t vector_size = 0;
        T *arr;
    };
    //REALLOCATE
    template <typename T>
    inline void vector<T>::reallocate() {
        T *temp_arr = new T[reserved_size];
        memmove(temp_arr, arr, vector_size * sizeof(T));
        delete[] arr;
        arr = temp_arr;
    }

    //CREATE VECTOR, INITIALIZE, CONSTRUCT:
    template <typename T> //default: vector<T> v;
    vector<T>::vector(){
        arr = new T[reserved_size];
    }

    template <typename T> //default: vector<T> v(int);
    vector<T>::vector(typename vector<T>::size_type n) {
        reserved_size = n*2;
        arr = new T[n];
        for(size_t i = 0; i < n; i++) {
            arr[i] = 0;
        }
        vector_size = n;
    }

    template <typename T> //default: vector<T> v(int, T);
    vector<T>::vector(typename vector<T>::size_type n, const T val){
        reserved_size = n*2;
        arr = new T[n];

        for(size_t i = 0; i < n; i++)
            arr[i] = val;
        vector_size = n;
    }

    template <typename T>
    vector<T>::vector(std::initializer_list<T> list) {//default: vector<T> v{T, T, T};
        reserved_size = list.size()*2;
        arr = new T[reserved_size];
        for(auto item: list) {
            arr[vector_size++] = item;
        }
    }

    //PUSHBACK
    template <typename T>
    void vector<T>::push_back(const T &val) {
        if (vector_size == reserved_size) {
            reserved_size = reserved_size*2;
            reallocate();
        }
        arr[vector_size] = val;
        ++vector_size;
    }

    template <typename T>
    void vector<T>::push_back(T && val) {
        if(vector_size == reserved_size){
            reserved_size = reserved_size*2;
            reallocate();
        }
        arr[vector_size] = std::move(val);
        ++vector_size;
    }
    //DELETE VECTOR
    template <typename T>
    vector<T>::~vector(){
        delete [] arr;
    }

    //POPBACK
    template <typename T>
    void vector<T>::pop_back() {
        vector_size--;
        arr[vector_size].~T();
    }
    //CLEAR
    template <typename T>
    void vector<T>::clear() {
        for (auto i = 0; i < vector_size; i++) {
            arr[i].~T();
        }
        vector_size = 0;
    }
    //CHECK IF EMPTY
    template <typename T>
    bool vector<T>::empty() {
        if(vector_size == 0) return true;
        else return false;
    }

    //RESIZE
    template <typename T>
    void vector<T>::resize(typename vector<T>::size_type sz) {

        if (sz > vector_size) {
            if (sz > reserved_size) {
                reserved_size = sz;
                reallocate();
            }
        }
        else for (size_type i = sz; i < vector_size; i++) arr[i].~T();
        vector_size = sz;
    }
    //SHRINK TO FIT
    template <typename T>
    void vector<T>::shrink_to_fit() {
        reserved_size = vector_size;
        reallocate();
    }
    //OPERATOR []
    template <typename T>
    typename vector<T>::reference vector<T>::operator [](typename vector<T>::size_type nr){
        return arr[nr];
    }

    //SIZE()
    template <typename T>
    typename vector<T>::size_type vector<T>::size() {
        return vector_size;
    }

    template <typename T>
    typename vector<T>::size_type vector<T>::capacity(){
        return reserved_size;
    }
    //ITERATORS:

    template <typename T> //BEGIN
    typename vector<T>::iterator vector<T>::begin() {
        return arr;
    }
    template <typename T> //END
    typename vector<T>::iterator vector<T>::end() {
        return arr+vector_size;
    }
    template <typename T> //INSERT
    typename vector<T>::iterator vector<T>::insert(const_iterator iter, const T& value) {
        T *temp_arr = new T[reserved_size];
        int x = 0;
        for(auto i = iter - begin(); i < size(); i++) {
            temp_arr[x] = arr[i];
            x++;
        }
        x = 0;
        vector_size++;

        arr[iter-begin()] = value;
        for(auto i = iter - begin()+1; i < size(); i++) {
            arr[i] = temp_arr[x];
            x++;
        }
    }

    template <typename T>  //INSERT LIST
    typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator iter, std::initializer_list<T> list) {
        T *temp_arr = new T[reserved_size];
        int x = 0;
        for(auto i = iter - begin(); i < size(); i++) {
            temp_arr[x] = arr[i];
            x++;
        }
        x = 0;
        for(auto item : list) {
            arr[iter-begin()] = item;
            iter++;
            vector_size++;
        }
        for(auto i = iter - begin(); i < size(); i++) {
            arr[i] = temp_arr[x];
            x++;
        }
    }
    //EMPLACE
    template <typename T>

    //ERASE?
    template <typename T>
    typename vector<T>::iterator vector<T>::erase(typename vector<T>::const_iterator pos) {
        T *temp_arr = new T[reserved_size];
        int x = 0;
        for(auto i = pos - begin(); i < size(); i++) {
            temp_arr[x] = arr[i];
            x++;
        }
        x = 0;
        vector_size--;

        arr[pos-begin()].~T();
        for(auto i = pos - begin()+1; i < size(); i++) {
            arr[i] = temp_arr[x];
            x++;
        }
    }


    //LOGICAL OPERATORS
    template <typename T>
    bool vector<T>::operator == (vector<T> &r) {
        if(r.vector_size != vector_size) return false;
        for(size_t i = 0; i < vector_size; i++) {
            if(r.arr[i] != arr[i]) return false;
        }
        return true;
    }

    template <typename T>
    bool vector<T>::operator != (vector<T> &r) {
        if(r.vector_size != vector_size) return true;
        for(size_t i = 0; i < vector_size; i++) {
            if(r.arr[i] != arr[i]) return true;
        }
        return false;
    }

    template <typename T>
    bool vector<T>::operator < (vector<T> &r) {
        size_t i{}, lowerSz{};
        if(vector_size < r.vector_size) lowerSz =  vector_size;
        else if (vector_size > r.vector_size) lowerSz =  r.vector_size;
        for (i = 0; i < lowerSz; i++)
            if (arr[i] != r.arr[i])
                return arr[i] < r.arr[i];
        return vector_size < r.vector_size;
    }

    template <typename T>
    bool vector<T>::operator <= (vector<T> &r) {
        size_type i, lowerSz{};
        if(vector_size < r.vector_size) lowerSz =  vector_size;
        else if (vector_size > r.vector_size) lowerSz =  r.vector_size;
        for (i = 0; i < lowerSz; ++i)
            if (arr[i] != r.arr[i]) {
                bool b = arr[i] < r.arr[i];
                return b;
            }
        if(vector_size <= r.vector_size) return true;
        else return false;
    }

    template <typename T>
    bool vector<T>::operator >= (vector<T> &r) {
        size_type i, lowerSz{};
        if(vector_size < r.vector_size) lowerSz =  vector_size;
        else if (vector_size > r.vector_size) lowerSz =  r.vector_size;
        for (i = 0; i < lowerSz; ++i)
            if (arr[i] != r.arr[i]) {
                bool b = arr[i] > r.arr[i];
                return b;
            }
        return vector_size >= r.vector_size;
    }

    template <typename T>
    bool vector<T>::operator > (vector<T> &r) {
        size_type i, lowerSz{};
        if(vector_size < r.vector_size) lowerSz =  vector_size;
        else if (vector_size > r.vector_size) lowerSz =  r.vector_size;
        for (i = 0; i < lowerSz; ++i) {
            if (arr[i] != r.arr[i]) {
                bool b = arr[i] > r.arr[i];
                return b;
            }
        }

        return vector_size > r.vector_size;
    }





#endif //UNTITLED_SUPERVECTOR_H
