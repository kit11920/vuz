import ctypes

# Чтобы скрипт искал в родительском каталоге
import sys, os
parant_dir = os.path.abspath('.')
sys.path.append(parant_dir)
# 
import pylib_arr

# Класс чтения функций из библиотеки при подключении ctypes
class Libarr_ctypes():
    def __init__(self, namelib):
        self.lib = ctypes.CDLL(namelib)

        # int k_shift_arr(int arr[], size_t len_arr, int k);
        self._k_shift_arr = self.lib.k_shift_arr
        self._k_shift_arr.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, ctypes.c_int)
        self._k_shift_arr.restype = ctypes.c_int

        # int make_sqrt_arr(int src[], size_t len_src, int dst[], size_t *len_dst);
        self._make_sqrt_arr = self.lib.make_sqrt_arr
        self._make_sqrt_arr.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, 
                                ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_size_t))
        self._make_sqrt_arr.restype = ctypes.c_int

    # Обертка функции k_shift_arr()
    def k_shift_arr(self, arr, k):
        len_arr = len(arr)
        arr = (ctypes.c_int * len_arr)(*arr)

        rc = self._k_shift_arr(arr, len_arr, k)

        return rc, list(arr)
    
    # Обертка функции make_sqrt_arr() с экономичным выделением памяти
    def make_sqrt_arr_eco(self, src):
        len_src = len(src)
        src = (ctypes.c_int * len_src)(*src)
        dst_len = ctypes.c_size_t(0)
        # ptr = ctypes.POINTER(ctypes.c_size_t)(dst_len)

        rc = self._make_sqrt_arr(src, len_src, None, dst_len)
        
        if rc != -1:
            dst = (ctypes.c_int * dst_len.value)()
            rc = self._make_sqrt_arr(src, len_src, dst, ctypes.c_size_t(rc))

            return rc, list(dst)
        else:
            return rc, list()

    # Обертка функции make_sqrt_arr() с выделением памяти с запасом
    def make_sqrt_arr_reserv(self, src):
        len_src = len(src)
        len_dst = ctypes.c_size_t(len_src)
        src = (ctypes.c_int * len_src)(*src)

        dst = (ctypes.c_int * len_src)()
        rc = self._make_sqrt_arr(src, len_src, dst, len_dst)

        return rc, list(dst)[:len_dst.value]

# Класс чтения функций из библиотеки при подключении модулем расширения
class Libarr_ExtModule():
    def __init__(self):
        pass

        # Обертка функции k_shift_arr()
    def k_shift_arr(self, arr, k):
        return 0, pylib_arr.k_shift_arr(arr, k)

    # Обертка функции make_sqrt_arr() с экономичным выделением памяти
    def make_sqrt_arr_eco(self, src):
        return 0, pylib_arr.make_sqrt_arr_eco(src)

    # Обертка функции make_sqrt_arr() с выделением памяти с запасом
    def make_sqrt_arr_reserv(self, src):
        return 0, pylib_arr.make_sqrt_arr_reserv(src)


# Пример работы функций из библитеки
if __name__ == '__main__':
    lib = Libarr_ctypes('./libarr.so')
    arr = [0, 10, 4, 9, -9, -1, 121]

    rc, arr = lib.k_shift_arr(arr, 2)
    if rc != 0:
        print('ERROR')
    else:
        print(arr)
    
    rc, filter_arr = lib.make_sqrt_arr_eco(arr)
    if rc < 0:
        print('ERROR')
    else:
        print(filter_arr)

    lib = Libarr_ExtModule();
    print(lib.k_shift_arr([1, 2, 3, 4], 2)[1])
    print(lib.make_sqrt_arr_eco([1, 4, 9, 3, 8, 100])[1])
    print(lib.make_sqrt_arr_reserv([1, 4, 9, 3, 8, 100])[1])








