from conan import ConanFile

from conan.tools.cmake import CMake
from conan.tools.cmake import CMakeDeps
from conan.tools.cmake import CMakeToolchain


class CaesarRecipe(ConanFile):
    name = "caesar"
    version = "0.0.0"

    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False]}
    default_options = {"shared": False}

    requires = ("nocheck/0.0.1",)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self, generator="Ninja Multi-Config")
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(
            variables={
                "CMAKE_EXPORT_COMPILE_COMMANDS": "ON",
            }
        )
        cmake.build()
