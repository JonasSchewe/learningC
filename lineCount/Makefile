.phony: clean all example implementation test
.SILENT: all example implementation test clean

all: example implementation test

example:
	cd  example/ && $(MAKE) && cd ..

implementation:
	cd  implementation/ && $(MAKE) && cd ..

test:
	cd  test/ && $(MAKE) && cd ..


clean:
	cd  example/ && $(MAKE) clean && cd ..
	cd  implementation/ && $(MAKE) clean && cd ..
	cd  test/ && $(MAKE) clean && cd ..