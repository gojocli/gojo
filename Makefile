.PHONY: build
.PHONY: test

config:
	cmake -S . -B build/Debug -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_STANDARD=23 -DCMAKE_CXX_STANDARD_REQUIRED=ON -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-Wall -Wextra -Wconversion -Wshadow -fno-exceptions" -DCMAKE_TOOLCHAIN_FILE=deps/build/Debug/generators/conan_toolchain.cmake

config-rel:
	cmake -S . -B build/Release -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_STANDARD=23 -DCMAKE_CXX_STANDARD_REQUIRED=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -Wextra -Wconversion -Wshadow -fno-exceptions" -DCMAKE_TOOLCHAIN_FILE=deps/build/Release/generators/conan_toolchain.cmake

build:
	cmake --build build/Debug --parallel

build-rel:
	cmake --build build/Release --parallel

test:
	cd build/Debug/test && ctest --output-on-failure
	cd ../../../

fmt:
	find src/ -iname '*.cpp' -o -iname '*.hpp' | xargs clang-format -n

check:
	run-clang-tidy -p build/Debug

clean:
	rm -rf build
	mkdir -p build
