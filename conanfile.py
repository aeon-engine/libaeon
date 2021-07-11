from conans.errors import ConanInvalidConfiguration
from conans import ConanFile, CMake, tools
import os


class LibAeonConan(ConanFile):
    name = 'libaeon'
    description = 'A general purpose C++20 support library.'
    license = 'BSD-2-Clause'
    homepage = 'https://git.aeons.dev/aeon-engine/libaeon'
    url = 'https://git.aeons.dev/aeon-engine/libaeon'
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "cmake_multi"
    options = {
        'shared': [True, False],
        'fPIC': [True, False],
        'enable_unittests': [True, False],
        'enable_benchmarks': [True, False],
        'with_ast': [True, False],
        'with_chrono': [True, False],
        'with_clang': [True, False],
        'with_common': [True, False],
        'with_compression': [True, False],
        'with_crypto': [True, False],
        'with_file_container': [True, False],
        'with_fonts': [True, False],
        'with_gl': [True, False],
        'with_gl_utils': [True, False],
        'with_imaging': [True, False],
        'with_logger': [True, False],
        'with_math': [True, False],
        'with_midi': [True, False],
        'with_mono': [True, False],
        'with_platform': [True, False],
        'with_plugins': [True, False],
        'with_ptree': [True, False],
        'with_rdp': [True, False],
        'with_reflection': [True, False],
        'with_serial': [True, False],
        'with_sockets': [True, False],
        'with_streams': [True, False],
        'with_testing': [True, False],
        'with_tracelog': [True, False],
        'with_unicode': [True, False],
        'with_variant': [True, False],
        'with_vulkan': [True, False],
        'with_web': [True, False]
    }
    default_options = {
        'shared': False,
        'fPIC': True,
        'enable_unittests': True,
        'enable_benchmarks': True,
        'with_ast': True,
        'with_chrono': True,
        'with_clang': True,
        'with_common': True,
        'with_compression': True,
        'with_crypto': True,
        'with_file_container': True,
        'with_fonts': True,
        'with_gl': True,
        'with_gl_utils': True,
        'with_imaging': True,
        'with_logger': True,
        'with_math': True,
        'with_midi': True,
        'with_mono': False,
        'with_platform': True,
        'with_plugins': True,
        'with_ptree': True,
        'with_rdp': True,
        'with_reflection': True,
        'with_serial': True,
        'with_sockets': True,
        'with_streams': True,
        'with_testing': True,
        'with_tracelog': True,
        'with_unicode': True,
        'with_variant': True,
        'with_vulkan': True,
        'with_web': True
    }

    def _supports_compiler(self):
        compiler = self.settings.compiler.value
        version = tools.Version(self.settings.compiler.version)
        major_rev, minor_rev = int(version.major), int(version.minor)

        unsupported_combinations = [
            [compiler == 'gcc', major_rev < 11],
            [compiler == 'clang', major_rev < 12],
            [compiler == 'Visual Studio', major_rev < 16],
            # [compiler == 'apple-clang', major_rev < 9],
        ]
        if any(all(combination) for combination in unsupported_combinations):
            message = 'unsupported compiler: "{}", version "{}"'
            raise ConanInvalidConfiguration(message.format(compiler, version))

    def config_options(self):
        if self.settings.os == 'Windows':
            del self.options.fPIC

        if self.settings.os != 'Windows':
            del self.options.with_platform
            del self.options.with_gl
            del self.options.with_gl_utils

    def requirements(self):
        if self.options.get_safe('enable_unittests', True):
            self.requires('gtest/1.11.0@aeon/stable')

        if self.options.get_safe('enable_benchmarks', True):
            self.requires('benchmark/1.5.5@aeon/stable')

        if self.options.get_safe('with_chrono', True) or self.options.get_safe('with_unicode', True):
            self.requires('icu/69.1@aeon/stable')

        if self.options.get_safe('with_clang', True):
            self.requires('libclang/11.1.0@aeon/stable')

        if self.options.get_safe('with_compression', True):
            self.requires('zlib/1.2.11@aeon/stable')

        if self.options.get_safe('with_fonts', True):
            self.requires('freetype/2.10.4@aeon/stable')

        if self.options.get_safe('with_gl', True):
            self.requires('opengl-registry/1.0@aeon/stable')

        if self.options.get_safe('with_imaging', True):
            self.requires('libpng/1.6.37@aeon/stable')
            self.requires('libjpeg-turbo/2.1.0@aeon/stable')

        if self.options.get_safe('with_midi', True):
            self.requires('rtmidi/4.0.0@aeon/stable')

        if self.options.get_safe('with_sockets', True):
            self.requires('asio/1.18.2@aeon/stable')

        if self.options.get_safe('with_vulkan', True):
            self.requires('vulkan-memory-allocator/2.3.0.201@aeon/stable')

    def imports(self):
        if self.settings.compiler.value == 'Visual Studio':
            self.copy("*.dll", src="bin", dst=os.path.join("bin", str(self.settings.build_type)))

    def configure(self):
        if self.options.shared:
            del self.options.fPIC

        self._supports_compiler()

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions['BUILD_SHARED_LIBS'] = self.options.shared
        cmake.definitions['CMAKE_POSITION_INDEPENDENT_CODE'] = \
            self.options.get_safe('fPIC', default=False) or self.options.shared

        cmake.definitions['AEON_ENABLE_TESTING'] = self.options.enable_unittests
        cmake.definitions['AEON_ENABLE_BENCHMARK'] = self.options.enable_benchmarks
        
        cmake.definitions['AEON_COMPONENT_AST'] = self.options.get_safe('with_ast', default=False)
        cmake.definitions['AEON_COMPONENT_CHRONO'] = self.options.get_safe('with_chrono', default=False)
        cmake.definitions['AEON_COMPONENT_CLANG'] = self.options.get_safe('with_clang', default=False)
        cmake.definitions['AEON_COMPONENT_COMMON'] = self.options.get_safe('with_common', default=False)
        cmake.definitions['AEON_COMPONENT_COMPRESSION'] = self.options.get_safe('with_compression', default=False)
        cmake.definitions['AEON_COMPONENT_CRYPTO'] = self.options.get_safe('with_crypto', default=False)
        cmake.definitions['AEON_COMPONENT_FILE_CONTAINER'] = self.options.get_safe('with_file_container', default=False)
        cmake.definitions['AEON_COMPONENT_FONTS'] = self.options.get_safe('with_fonts', default=False)
        cmake.definitions['AEON_COMPONENT_GL'] = self.options.get_safe('with_gl', default=False)
        cmake.definitions['AEON_COMPONENT_GL_UTILS'] = self.options.get_safe('with_gl_utils', default=False)
        cmake.definitions['AEON_COMPONENT_IMAGING'] = self.options.get_safe('with_imaging', default=False)
        cmake.definitions['AEON_COMPONENT_LOGGER'] = self.options.get_safe('with_logger', default=False)
        cmake.definitions['AEON_COMPONENT_MATH'] = self.options.get_safe('with_math', default=False)
        cmake.definitions['AEON_COMPONENT_MIDI'] = self.options.get_safe('with_midi', default=False)
        cmake.definitions['AEON_COMPONENT_MONO'] = self.options.get_safe('with_mono', default=False)
        cmake.definitions['AEON_COMPONENT_PLATFORM'] = self.options.get_safe('with_platform', default=False)
        cmake.definitions['AEON_COMPONENT_PLUGINS'] = self.options.get_safe('with_plugins', default=False)
        cmake.definitions['AEON_COMPONENT_PTREE'] = self.options.get_safe('with_ptree', default=False)
        cmake.definitions['AEON_COMPONENT_RDP'] = self.options.get_safe('with_rdp', default=False)
        cmake.definitions['AEON_COMPONENT_REFLECTION'] = self.options.get_safe('with_reflection', default=False)
        cmake.definitions['AEON_COMPONENT_SERIAL'] = self.options.get_safe('with_serial', default=False)
        cmake.definitions['AEON_COMPONENT_SOCKETS'] = self.options.get_safe('with_sockets', default=False)
        cmake.definitions['AEON_COMPONENT_STREAMS'] = self.options.get_safe('with_streams', default=False)
        cmake.definitions['AEON_COMPONENT_TESTING'] = self.options.get_safe('with_testing', default=False)
        cmake.definitions['AEON_COMPONENT_TRACELOG'] = self.options.get_safe('with_tracelog', default=False)
        cmake.definitions['AEON_COMPONENT_UNICODE'] = self.options.get_safe('with_unicode', default=False)
        cmake.definitions['AEON_COMPONENT_VARIANT'] = self.options.get_safe('with_variant', default=False)
        cmake.definitions['AEON_COMPONENT_VULKAN'] = self.options.get_safe('with_vulkan', default=False)
        cmake.definitions['AEON_COMPONENT_WEB'] = self.options.get_safe('with_web', default=False)

        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.remove_files_by_mask(self.package_folder, "*.pdb")
        tools.remove_files_by_mask(self.package_folder, "*.exe")
