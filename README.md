# cpp-llvm-coverage
How to use LLVM coverage for for C++

## Example
 
See https://longhanks.github.io/cpp-llvm-coverage
 
## Libraries/Tools used

The coverage data is generated using LLVM's [Source-based Code Coverage](https://clang.llvm.org/docs/SourceBasedCodeCoverage.html).

The generated HTML output is produced by Chromium's `coverage.py` (see [Code Coverage in Chromium](https://chromium.googlesource.com/chromium/src/+/master/docs/testing/code_coverage.md)).

`llvm-profdata` and `llvm-cov` are downloaded from Chromium ([Linux x64](https://commondatastorage.googleapis.com/chromium-browser-clang/Linux_x64/llvm-code-coverage-361419-76a8a0cb-1.tgz), [Mac](https://commondatastorage.googleapis.com/chromium-browser-clang/Mac/llvm-code-coverage-361419-76a8a0cb-1.tgz)).

The tests are written using [Catch2](https://github.com/catchorg/Catch2).
