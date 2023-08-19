from conans import ConanFile

class OrderConan(ConanFile):
    name = "order-pp"
    version = "master"
    license = "BSL-1.0"
    author = "Vesa Karvonen"
    url = "https://github.com/rofl0r/order-pp"
    description = "order-pp preprocessor library (standalone part of chaos-pp)"
    topics = ("header-only", "preprocessor", "macros")
    no_copy_source = True
    requires = "chaos-pp/master"

    def source(self):
        self.run(f"git clone {self.url} .")

    def package(self):
        self.copy("*", src = "inc", dst = "include")
        self.copy("README.md")
        self.copy("LICENSE")

    def package_id(self):
        self.info.header_only()
