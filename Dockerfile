FROM ubuntu:24.04

RUN apt update && apt install -fy clang 

COPY fuzz.c . 

RUN clang -fsanitize=fuzzer,address -o fuzz fuzz.c

CMD /fuzz