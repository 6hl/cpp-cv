.PHONY: build weights test
build:
	cfg/build.sh
weights:
	cfg/weights.sh
run:
	cfg/run.sh
eval:
	cfg/eval.sh
test:
	cfg/test.sh