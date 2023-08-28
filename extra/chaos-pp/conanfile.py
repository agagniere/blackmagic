import os
from conan import ConanFile
from conan.tools.files import copy
from conan.tools.scm import Git

class ChaosConan(ConanFile):
    name = 'chaos-pp'
    version = 'master'
    description = 'chaos preprocessor library. this is what boost preprocessor derived from.'
    license = 'BSL-1.0'
    author = 'Paul Mensonides'
    topics = ('header-only', 'preprocessor', 'macros')
    url = 'https://github.com/rofl0r/chaos-pp'
    no_copy_source = True

    def source(self):
        Git(self).clone(self.url, '.')

    def package(self):
        copy(self, '*.h',
             os.path.join(self.source_folder, 'chaos'),
             os.path.join(self.package_folder, 'include', 'chaos'))
        copy(self, 'README', self.source_folder, self.package_folder)
        copy(self, 'LICENSE', self.source_folder, self.package_folder)

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
