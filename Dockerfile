FROM alpine:latest
RUN apk add bash make figlet git gcc musl-dev clang linux-headers \
    && git clone https://github.com/jaseg/lolcat.git \
    && cd lolcat && make && make install
COPY . ./app
