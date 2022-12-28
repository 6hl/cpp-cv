.PHONY: build weights test
build:
	cfg/build.sh
weights:
	cfg/weights.sh
run:
	cfg/run.sh
test:
	cfg/test.sh