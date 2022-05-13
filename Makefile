BUILD_DIR=cmake-build-debug
RELEASE_DIR=cmake-build-release

build:
	# Create cmake configuration
	cmake -S. -B$(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug~

	# Build project
	cmake --build $(BUILD_DIR) --config Debug

release:
	# Create cmake configuration
	cmake -S. -B$(RELEASE_DIR) -DCMAKE_BUILD_TYPE=Release~

	# Build project
	cmake --build $(RELEASE_DIR) --config Release

run:
	./$(BUILD_DIR)/librarity_but_dumber_run

tests:
	cd $(BUILD_DIR) ; ctest --test-dir -C Debug --output-on-failure --verbose

clean:
	rm -rf $(BUILD_DIR) $(RELEASE_DIR)
