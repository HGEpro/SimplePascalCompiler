# If the first argument is "run"...
ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif


src_directory = ./src/
output_directory = ./compiled

binary = compiler.o

files = $(src_directory)lexer.cpp $(src_directory)lexer.hpp $(src_directory)main.cpp


compile:
	mkdir -p $(output_directory)
	g++ $(files) -o $(output_directory)/$(binary)

run:
	$(output_directory)/$(binary) $(RUN_ARGS) 

