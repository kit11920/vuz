#pragma once 

#include "BaseException.h"

class MemoryExcetion: public BaseMatrixException
{
public:
    MemoryExcetion(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Memory allocation error ") noexcept:
                  BaseMatrixException(time, filename, line, class_name, method_name, info){};
};

class RowIndexException: public BaseMatrixException
{
public:
    RowIndexException(const char *time, const char *filename,
                  const size_t &line, const char *class_name,
                  const char *method_name, const char *info = "Index of row matrix out of range") noexcept:
                  BaseMatrixException(time, filename, line, class_name, method_name, info){};
};

class ColIndexException: public BaseMatrixException
{
public:
    ColIndexException(const char *time, const char *filename,
                  const size_t &line, const char *class_name,
                  const char *method_name, const char *info = "Index of column matrix out of range") noexcept:
                  BaseMatrixException(time, filename, line, class_name, method_name, info){};
};

class MultiplicatingException: public BaseMatrixException
{
public:
    MultiplicatingException(const char *time, const char *filename,
                  const size_t &line, const char *class_name,
                  const char *method_name, const char *info = "Bad matrixs sizes for multiplication") noexcept:
                  BaseMatrixException(time, filename, line, class_name, method_name, info){};
};

class SizeMtrxsForOperationException: public BaseMatrixException
{
public:
    SizeMtrxsForOperationException(const char *time, const char *filename,
                  const size_t &line, const char *class_name,
                  const char *method_name, const char *info = "Matrixs have different sizes for operation") noexcept:
                  BaseMatrixException(time, filename, line, class_name, method_name, info){};
};

class NeedSquareMtrxException: public BaseMatrixException
{
public:
    NeedSquareMtrxException(const char *time, const char *filename,
                  const size_t &line, const char *class_name,
                  const char *method_name, const char *info = "Matrix must be square") noexcept:
                  BaseMatrixException(time, filename, line, class_name, method_name, info){};
};

class ExcludeCopyMtrxException: public BaseMatrixException
{
public:
    ExcludeCopyMtrxException(const char *time, const char *filename,
                  const size_t &line, const char *class_name,
                  const char *method_name, const char *info = "Dst mtrx must be allocated and rows--, cols--") noexcept:
                  BaseMatrixException(time, filename, line, class_name, method_name, info){};
};

class ZeroDetException: public BaseMatrixException
{
public:
    ZeroDetException(const char *time, const char *filename,
                  const size_t &line, const char *class_name,
                  const char *method_name, const char *info = "Zero matrix determetant") noexcept:
                  BaseMatrixException(time, filename, line, class_name, method_name, info){};
};

class ExpiredException: public BaseIteratorException
{
public:
    ExpiredException(const char *time, const char *filename,
                  const size_t &line, const char *class_name,
                  const char *method_name, const char *info = "Expired weak ptr error") noexcept:
                  BaseIteratorException(time, filename, line, class_name, method_name, info){};
};

class IterIndexException: public BaseIteratorException
{
public:
    IterIndexException(const char *time, const char *filename,
                  const size_t &line, const char *class_name,
                  const char *method_name, const char *info = "Index of iterator out of range") noexcept:
                  BaseIteratorException(time, filename, line, class_name, method_name, info){};
};
