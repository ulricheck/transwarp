from conans import ConanFile, CMake
from conans.tools import download, unzip
import os


class TranswarpConan(ConanFile):
    name = "transwarp"
    version = "1.8.1-dev"
    description = "Conan package for bloomen/transwarp."
    url = "https://github.com/ulricheck/transwarp"
    license = "MIT"
    settings = "arch", "build_type", "compiler", "os"
    generators = "cmake"
    exports_sources = "src/*", "CMakeLists.txt", "examples/*"
    no_copy_source = True

    def source(self):
        zip_name = "%s.zip" % self.version
        download("%s/archive/%s" % (self.url, zip_name), zip_name, verify=False)
        unzip(zip_name)
        os.unlink(zip_name)

    def build(self): # this is not building a library, just tests and examples
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        include_folder = "%s-%s/src" % (self.name, self.version)
        self.copy("*.h", dst="include", src=include_folder)

    def package_id(self):
        self.info.header_only()

