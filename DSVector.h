//
// Created by MARK FONTENOT on 6/7/22.
//

#ifndef PA01_SENTIMENT_DSVECTOR_H
#define PA01_SENTIMENT_DSVECTOR_H

template<typename T>
class DSVector {
private:
    int cap;
    int size;
    T* data;
public:

    DSVector(int init_capacity = 10);
    DSVector(const DSVector& arg);
    ~DSVector();
    void pushBack(const T& arg);
    T& operator[](int location);
    DSVector& operator=(const DSVector& arg);
    int getSize();

};

template <typename T>
DSVector<T>::DSVector(int init_capacity) {
    size = 0;
    cap = init_capacity;
    data = new T[cap];
}

template <typename T>
DSVector<T>::DSVector(const DSVector& arg) {
    //delete[] data;
    cap = arg.cap;
    size = arg.size;
    data = new T[cap];
    for(int i = 0; i < size; i++)
        data[i] = arg.data[i];
}

template <typename T>
DSVector<T>::~DSVector() {
    delete [] data;
}

template <typename T>
DSVector<T>& DSVector<T>::operator=(const DSVector& arg) {

    if(this != &arg){
        delete[] data;
        size = arg.size;
        cap = arg.cap;
        data = new T[cap];
        for (int i = 0; i < size; i++) {
            data[i] = arg.data[i];
        }

    }
    return *this;
}


template<typename T>
void DSVector<T>::pushBack(const T& arg) {
    if(size == cap)
        ;
    data[size] = arg;
    size++;
}

template<typename T>
T& DSVector<T>::operator[](int location) {
    return data[location];
}

template<typename T>
int DSVector<T>::getSize() {
    return size;
}

#endif //PA01_SENTIMENT_DSVECTOR_H
