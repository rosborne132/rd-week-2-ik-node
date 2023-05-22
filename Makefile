all: format clean build

clean:
	@echo "Cleaning up build 🧹"
	rm -rf build

format:
	@echo "Formatting code 🧹"
	find include src -iname *.cpp -o -iname *.h | xargs clang-format -i

generate:
	@echo "Generating files 🔨"
	cmake -H. -Bbuild -G Ninja

build:
	make generate
	@echo "Building project 🚀"
	cmake --build build
	