.PHONY: build weights test
build:
	cfg/build.sh
weights:
	cfg/weights.sh
test:
	cfg/test.sh