from conans import ConanFile

class ChaosConan(ConanFile):
    name = "chaos-pp"
    version = "master"
    license = "BSL-1.0"
    author = "Paul Mensonides"
    url = "https://github.com/rofl0r/chaos-pp"
    description = "chaos preprocessor library. this is what boost preprocessor derived from."
    topics = ("header-only", "preprocessor", "macros")
    no_copy_source = True

    def source(self):
        self.run(f"git clone {self.url} .")

    def package(self):
        self.copy("*", src = "chaos", dst = "include/chaos")
        self.copy('README')
        self.copy('LICENSE')

    def package_id(self):
        self.info.header_only()
