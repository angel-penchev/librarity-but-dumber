# Create cmake configuration
cmake -S. -Bcmake-build-debug -DCMAKE_BUILD_TYPE=Debug~

# Build project
cmake --build cmake-build-debug --config Debug