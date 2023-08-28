import os
from conan import ConanFile
from conan.tools.files import copy
from conan.tools.scm import Git

class OrderConan(ConanFile):
    name = 'order-pp'
    version = 'master'
    description = 'order-pp preprocessor library (standalone part of chaos-pp)'
    license = 'BSL-1.0'
    author = 'Vesa Karvonen'
    topics = ('header-only', 'preprocessor', 'macros')
    url = 'https://github.com/rofl0r/order-pp'
    no_copy_source = True
    requires = 'chaos-pp/master'

    def source(self):
        Git(self).clone(self.url, '.')

    def package(self):
        copy(self, '*.h',
             os.path.join(self.source_folder, 'inc'),
             os.path.join(self.package_folder, 'include'))
        copy(self, 'README', self.source_folder, self.package_folder)
        copy(self, 'LICENSE', self.source_folder, self.package_folder)

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
