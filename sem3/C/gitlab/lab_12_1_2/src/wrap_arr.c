#include <Python.h>
#include <stdlib.h>

#include "arr.h"
#include "errs.h"

static PyObject* copy_to_py_list(const int *arr, size_t n)
{
    PyObject *plist, *pitem;

    // новая ссылка
    plist = PyList_New(n);
    if (!plist)
        return NULL;

    for (size_t i = 0; i < n; i++)
    {
        // новая ссылка
        pitem = PyLong_FromLong(arr[i]);
        // pitem = PyFloat_FromDouble(arr[i]);
        if (!pitem)
        {
            Py_DECREF(plist);
            return NULL;
        }

        PyList_SET_ITEM(plist, i, pitem);
    }

    return plist;
}

int *full_int_arr(PyObject *seq, size_t *len_arr_out)
{
    PyObject *item, *item_int;
    size_t len_arr;
    int *arr;

    len_arr = PySequence_Fast_GET_SIZE(seq);
    arr = malloc(len_arr * sizeof(int));
    if (!arr)
    {
        Py_DECREF(seq);
        return NULL;
    }

    for (size_t i = 0; i < len_arr; i++)
    {
        item = PySequence_Fast_GET_ITEM(seq, i);
        if (!item)
        {
            Py_DECREF(seq);
            free(arr);
            return NULL;
        }

        item_int = PyNumber_Long(item);
        if (!item_int)
        {
            Py_DECREF(seq);
            free(arr);
            return NULL;
        }

        arr[i] = (int) PyLong_AsLong(item_int);
        Py_DecRef(item_int);
    }

    *len_arr_out = len_arr;
    return arr;
}

// int k_shift_arr(int arr[], size_t len_arr, int k)
static PyObject *py_k_shift_arr(PyObject *self, PyObject *args)
{
    PyObject *seq, *listarr;
    int *arr;
    size_t len_arr;
    int k, rc;

    if (!PyArg_ParseTuple(args, "Oi", &seq, &k))
        return NULL;
    
    seq = PySequence_Fast(seq, "Argument must be iterable\n\n");
    if (!seq)
        return NULL;
    
    arr = full_int_arr(seq, &len_arr);
    Py_DecRef(seq);
    if (!arr)
        return NULL;

    rc = k_shift_arr(arr, len_arr, k);
    if (rc != 0)
    {
        free(arr);
        return NULL;
    }
    listarr = copy_to_py_list(arr, len_arr);
    free(arr);

    return listarr;
}

// int make_sqrt_arr(int src[], size_t len_src, int dst[], size_t *len_dst)
static PyObject *py_make_sqrt_arr_eco(PyObject *self, PyObject *args)
{
    PyObject *seq, *list_dst;
    int *src, *dst;
    size_t len_src, len_dst = 0;
    int rc = OK;

    if (!PyArg_ParseTuple(args, "O", &seq))
        return NULL;
    
    seq = PySequence_Fast(seq, "Argument must be iterable");
    if (!seq)
        return NULL;

    src = full_int_arr(seq, &len_src);
    Py_DecRef(seq);
    if (!src)
        return NULL;

    rc = make_sqrt_arr(src, len_src, NULL, &len_dst);
    if (rc == ERR_PARAM)
        return NULL;
    dst = malloc(len_dst * sizeof(int));
    if (!dst)
        return NULL;
    
    make_sqrt_arr(src, len_src, dst, &len_dst);
    list_dst = copy_to_py_list(dst, len_dst);
    free(src);
    free(dst);

    return list_dst;

}

// int make_sqrt_arr(int src[], size_t len_src, int dst[], size_t *len_dst)
static PyObject *py_make_sqrt_arr_reserv(PyObject *self, PyObject *args)
{
    PyObject *seq, *list_dst;
    int *src, *dst;
    size_t len_src, len_dst = 0;

    if (!PyArg_ParseTuple(args, "O", &seq))
        return NULL;
    
    seq = PySequence_Fast(seq, "Argument must be iterable");
    if (!seq)
        return NULL;

    src = full_int_arr(seq, &len_src);
    Py_DecRef(seq);
    if (!src)
        return NULL;

    len_dst = len_src;
    dst = malloc(len_dst * sizeof(int));
    if (!dst)
        return NULL;
    make_sqrt_arr(src, len_src, dst, &len_dst);
    list_dst = copy_to_py_list(dst, len_dst);
    free(src);
    free(dst);

    return list_dst;

}


static PyMethodDef pylib_arr_methods[] =
{
    {"k_shift_arr", py_k_shift_arr, METH_VARARGS, "Shifting_arr_to_k_positions"},
    {"make_sqrt_arr_eco", py_make_sqrt_arr_eco, METH_VARARGS, "Filter arr to sqrt economy dynamic memory"},
    {"make_sqrt_arr_reserv", py_make_sqrt_arr_reserv, METH_VARARGS, "Filter arr to sqrt non economy dynamic memory"},
    { NULL, NULL, 0, NULL}
};

static struct PyModuleDef pylib_arr_module = 
{
    PyModuleDef_HEAD_INIT,
    "pylib_arr",
    "An pylib_arr module",
    -1,
    pylib_arr_methods
};

PyMODINIT_FUNC PyInit_pylib_arr(void)
{
    return PyModule_Create(&pylib_arr_module);
}
