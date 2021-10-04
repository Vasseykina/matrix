//
// Created by User on 04.10.2021.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <cstddef>

template<class T>
class Matrix {
private:
    T **data;
    size_t rows;
    size_t cols;

public:
    Matrix(const size_t &rows, const size_t &cols);

    Matrix(const Matrix<T> &m);

    Matrix<T> &operator+=(const Matrix<T> &m);

    Matrix<T> &operator-=(const Matrix<T> &m);

    Matrix<T> &operator*=(const Matrix<T> &m);

    size_t getRows() { return rows; };

    size_t getCols() { return cols; };

    T *operator[](size_t i) { return data[i]; };

    Matrix<T> &operator=(const Matrix<T> &m);

    virtual ~Matrix();
};

template<class T>
inline Matrix<T>::Matrix(const size_t &rows, const size_t &cols):rows(rows), cols(cols) {
    data = new T *[rows];
    data[0] = new T[rows * cols];
    for (auto i = 0; i < rows; i++) {
        data[i] = data[0] + cols * i;
    }
}

template<class T>
inline Matrix<T>::~Matrix() {
    delete[] data[0];
    delete[] data;
    data = nullptr;
}

template<class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &m) {
    if (this != &m) {
        delete[] data[0];
        delete[]data;
        rows = m.rows;
        cols = m.cols;
        data = new T *[rows];
        data[0] = new T[rows * cols];
        for (auto i = 0; i < rows; ++i) {
            data[i] = data[0] + i * cols;
        }
        for (auto i = 0; i < rows * cols; ++i) {
            data[0][i] = m.data[0][i];
        }
    }
    return *this;
}


template<class T>
inline Matrix<T>::Matrix<T>(const Matrix<T> &m) {
    rows = m.rows;
    cols = m.cols;
    data = new T *[rows];
    data[0] = new T[rows * cols];
    for (auto i = 0; i < rows; ++i) {
        data[i] = data[0] + i * cols;
    }
    for (auto i = 0; i < rows * cols; ++i) {
        data[0][i] = m.data[0][i];
    }
}

template<class T>
inline Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &m) {
    for (auto i = 0; i < rows; ++i) {
        for (auto j = 0; j < cols; ++j) {
            data[i][j] += m.data[i][j];
        }
    }
    return *this;
}

template<class T>
inline Matrix<T> operator+(Matrix<T> n, const Matrix<T> &m) {
    return n += m;
}

template<class T>
inline Matrix<T>& Matrix<T>::operator-=(const Matrix<T> &m) {
    for (auto i = 0; i < rows; ++i) {
        for (auto j = 0; j < cols; ++j) {
            data[i][j] -= m.data[i][j];
        }
    }
    return *this;
}

template<class T>
inline Matrix<T> operator-(Matrix<T> n, const Matrix<T> &m) {
    return n -= m;
}

template<class T>
inline Matrix<T>& Matrix<T>::operator*=(const Matrix<T> &m) {
    if (m.rows != cols) {
        throw 42;
    }
    Matrix<T> result(m.cols, rows);
    for (auto i = 0; i < result.rows; ++i) {
        for (auto j = 0; j < result.cols; ++j) {
            result[i][j] = 0;
            for (auto g = 0; g < cols; ++g) {
                result[i][j] += data[i][g] * m.data[g][j];
            }

        }

    }
    cout << result;
    *this = result;
    return *this;
}

template<class T>
inline Matrix<T> operator*(Matrix<T> m, Matrix<T> &n) {
    return n *= m;
}


template<class T>
inline std::ostream &operator<<(std::ostream &out, Matrix<T> &m) {
    for (auto i = 0; i < m.getRows(); ++i) {
        for (auto j = 0; j < m.getCols(); ++j) {
            out << m[i][j] << ' ';
        }
        out << endl;
    }
    return out;
}

template<class T>
inline std::istream &operator>>(std::istream &in, Matrix<T> &m) {
    for (auto i = 0; i < m.getRows(); ++i) {
        for (auto j = 0; j < m.getCols(); ++j) {
            in >> m[i][j];
        }
    }
    return in;
}


#endif //MATRIX_MATRIX_H
