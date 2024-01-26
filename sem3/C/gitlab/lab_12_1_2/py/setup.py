# from distutils.core import setup, Extension
from setuptools import Extension, setup

setup(name='pylib_arr',
    ext_modules=[
        Extension(
            name='pylib_arr',
            sources=['src/wrap_arr.c'],
            include_dirs = ['.', 'inc'],
            library_dirs = ['.'],
            libraries = ['arr'],
            )
        ],
    build_lib='./py/'
)

