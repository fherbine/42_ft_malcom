FROM alpine:latest
RUN apk add bash make figlet git gcc musl-dev clang linux-headers valgrind tcpdump screen \
	&& git clone https://github.com/jaseg/lolcat.git \
	&& cd lolcat && make && make install

# Test web server
RUN apk add --no-cache python3 py3-pip python3-dev curl \
	&& python3 -m pip install uwsgi

COPY . ./app
