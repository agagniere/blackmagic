import os
from conan import ConanFile
from conan.tools.files import copy, save, load
from conan.tools.scm import Git

class BlackMagicConan(ConanFile):
    name = 'blackmagic'
    description = 'Collection of C macros for generating code'
    license = 'MIT'
    author = 'Antoine Gagniere'
    topics = 'header-only', 'preprocessor', 'macros'
    homepage = 'https://agagniere.github.io/blackmagic'
    url = 'https://github.com/agagniere/blackmagic'

    no_copy_source = True
    exports_sources = 'include/*.h', 'README.md', 'LICENSE'

    def _retrieve_version(self):
        git = Git(self, folder=self.recipe_folder)
        return git.run('tag --sort "-version:refname" --merged').split('\n', 1)[0]

    def export(self):
        save(self, os.path.join(self.export_folder, 'version.txt'), self._retrieve_version())

    def set_version(self):
        try:
            self.version = load(self, 'version.txt')
        except:
            self.version = self._retrieve_version()

    def package(self):
        # This will also copy the 'include' folder
        copy(self, '*.h', self.source_folder, self.package_folder)
        copy(self, 'README.md', self.source_folder, self.package_folder)
        copy(self, 'LICENSE', self.source_folder, self.package_folder)

    def package_info(self):
        # For header-only packages, libdirs and bindirs are not used
        # so it's necessary to set those as empty.
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
