from os.path import abspath, dirname, join
import platform


host = platform.system()
if host == 'Linux':
    LLVM_PLATFORM = 'linux_x64'
elif host == 'Darwin':
    LLVM_PLATFORM = 'macos_x64'
else:
    raise Exception('Cannot build coverage on ' + host)

LLVM_BUILD_DIR = join(dirname(abspath(__file__)), 'llvm_coverage_' + LLVM_PLATFORM)
STAMP_FILE = ''
