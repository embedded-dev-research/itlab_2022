#ifndef _MTRX_
#define _MTRX_

#include "Color.hpp"

template <typename ValType>
class Mtrx {
protected:
    ValType* data = nullptr;
public:
    int height;
    int width;

    Mtrx(int height_m = 0, int width_m = 0, ValType element = 0);
    Mtrx(const Mtrx& mtrx_m);                                                       // copy constructor
    Mtrx(Mtrx&& mtrx_m);

    ~Mtrx() { delete[] data; }                                                      // destructor

    ValType det();

    Mtrx<ValType>& operator=(const Mtrx<ValType>& mtrx_m);                          // assignment operator
    Mtrx<ValType>& operator=(Mtrx<ValType>&& mtrx_m);                               // assignment operator
    ValType& operator[](int position_m);                                            // access
    const ValType& operator[](int position_m) const;                                // const access

    // scalar operation
    Mtrx<ValType> operator*(const ValType& val);                                    // multiply by a scalar
    Mtrx<ValType> operator/(const ValType& val);                                    // division by a scalar

    // matrix operation
    template <typename T>
    friend Mtrx<T> operator*(const Mtrx<T>& mtrx_left, const Mtrx<T>& mtrx_right);  // multiplication

    template <typename T>
    friend Mtrx<T> Adamar(const Mtrx<T>& mtrx_left, const Mtrx<T>& mtrx_right);     // comp. multiplication

    // input-output
    template <typename T>
    friend std::ostream& operator<<(std::ostream& out, const Mtrx<T>& mtrx_m);
};

template <mode Mode>
class Image : public Mtrx<Color<Mode>>
{
public:
    Image(int height_m = 0, int width_m = 0, Color<Mode> color_m = 0)                // constructor
        : Mtrx<Color<Mode>>(height_m, width_m, color_m) {}

    unsigned char* splitR();                                                         // split component 
    unsigned char* splitG();
    unsigned char* splitB();
    unsigned char* getMemory(int a, int b);
};

/// 
/// 
/// Mtrx
/// 
/// 

template <typename ValType> //contructor
Mtrx<ValType>::Mtrx(int height_m, int width_m, ValType element)
    : height(height_m)
    , width(width_m)
{
    data = new ValType[height * width];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            data[i * width + j] = element;
        }
    }
} /*-------------------------------------------------------------------------*/

template <typename ValType> //copy constructor
Mtrx<ValType>::Mtrx(const Mtrx<ValType>& mtrx_m)
    : height(mtrx_m.height)
    , width(mtrx_m.width)
{
    data = new ValType[height * width];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            data[i * width + j] = mtrx_m[i * width + j];
        }
    }
} /*-------------------------------------------------------------------------*/

template <typename ValType>
Mtrx<ValType>::Mtrx(Mtrx&& mtrx_m)
    : height(mtrx_m.height)
    , width(mtrx_m.width)
    , data(mtrx_m.data)
{
    mtrx_m.data = nullptr;
} /*-------------------------------------------------------------------------*/

template <typename ValType>
Mtrx<ValType>& Mtrx<ValType>::operator=(const Mtrx<ValType>& mtrx_m) {
    if (this != &mtrx_m) {
        delete[] data;

        height = mtrx_m.height;
        width = mtrx_m.width;
        data = new ValType[height * width];

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                data[i * height + j] = mtrx_m[i * height + j];
            }
        }
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <typename ValType>
Mtrx<ValType>& Mtrx<ValType>::operator=(Mtrx<ValType>&& mtrx_m) {
    height = mtrx_m.height;
    width = mtrx_m.width;
    std::swap(data, mtrx_m.data);

    return *this;
} /*-------------------------------------------------------------------------*/

template <typename ValType>
const ValType& Mtrx<ValType>::operator[](int position_m) const {
    return data[position_m];

} /*-------------------------------------------------------------------------*/

template <typename ValType>
ValType& Mtrx<ValType>::operator[](int position_m) {
    return data[position_m];
} /*-------------------------------------------------------------------------*/

template <typename ValType>
Mtrx<ValType> Mtrx<ValType>::operator*(const ValType& val) {
    Mtrx<ValType> res(*this);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            res[i * width + j] *= val;
    return res;
} /*-------------------------------------------------------------------------*/

template <typename ValType>
Mtrx<ValType> Mtrx<ValType>::operator/(const ValType& val) {
    Mtrx<ValType> res(*this);
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; j++) {
            res[i * width + j] /= val;
        }
    return res;
} /*-------------------------------------------------------------------------*/

template <typename T>
Mtrx<T> operator*(const Mtrx<T>& mtrx_left, const Mtrx<T>& mtrx_right) {
    Mtrx<T> mtrx_result(mtrx_left.height, mtrx_right.width);

    for (int i = 0; i < mtrx_left.height; i++) {
        for (int j = 0; j < mtrx_right.width; j++) {
            for (int k = 0; k < mtrx_left.width; k++) {
                mtrx_result.data[i * mtrx_result.width + j] += mtrx_left.data[i * mtrx_left.width + k] * mtrx_right.data[k * mtrx_right.width + j];
            }
        }
    }

    return mtrx_result;
} /*-------------------------------------------------------------------------*/

template <typename T>
Mtrx<T> Adamar(const Mtrx<T>& mtrx_left, const Mtrx<T>& mtrx_right) {
    Mtrx<T> mtrx_result(mtrx_left.height, mtrx_left.width);

    for (int i = 0; i < mtrx_result.height; ++i) {
        for (int j = 0; j < mtrx_result.width; ++j) {
            mtrx_result[i * mtrx_result.width + j] = mtrx_left[i * mtrx_left.width + j] * mtrx_right[i * mtrx_right.width + j];
        }
    }

    return mtrx_result;
} /*-------------------------------------------------------------------------*/

template <typename T>
std::ostream& operator<<(std::ostream& out, const Mtrx<T>& mtrx_m) {
    for (int i = 0; i < mtrx_m.height; ++i) {
        for (int j = 0; j < mtrx_m.width; ++j) {
            out << mtrx_m.data[i * mtrx_m.width + j] << ' ';
        }
        out << '\n';
    }
    return out;
} /*-------------------------------------------------------------------------*/

/// 
/// 
/// Image
/// 
/// 

template <mode Mode>
unsigned char* Image<Mode>::splitR() {
    unsigned char* R = new unsigned char[this->height * this->width];
    for (int i = 0; i < this->height * this->width; i++) {
        R[i] = this->data[i].R();
    }
    return R;
} /*-------------------------------------------------------------------------*/

template <mode Mode>
unsigned char* Image<Mode>::splitG() {
    unsigned char* G = new unsigned char[this->height * this->width];
    for (int i = 0; i < this->height * this->width; i++) {
        G[i] = this->data[i].G();
    }
    return G;
} /*-------------------------------------------------------------------------*/

template <mode Mode>
unsigned char* Image<Mode>::splitB() {
    unsigned char* B = new unsigned char[this->height * this->width];
    for (int i = 0; i < this->height * this->width; i++) {
        B[i] = this->data[i].B();
    }
    return B;
} /*-------------------------------------------------------------------------*/

template <mode Mode>
unsigned char* Image<Mode>::getMemory(int a, int b){
    unsigned char* ret = new unsigned char[4*(b-a)];
    for(int i = 0; i < b-a; i++){
        unsigned char* tmp = this->data[i+a].getComp();
        for(int j = 0; j < 4; j++){
            ret[i*4 + j] = tmp[j];
        }
    }
    return ret;
}

#endif