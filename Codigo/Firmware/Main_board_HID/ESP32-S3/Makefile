all:
	docker run --rm -v $(shell pwd):/project -w /project espressif/idf idf.py build
clean:
	docker run --rm -v $(shell pwd):/project -w /project espressif/idf idf.py fullclean 
