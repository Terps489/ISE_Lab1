FROM ubuntu:latest

RUN apt-get update && apt-get install -y git cmake make g++ vim

COPY Kostil.sh /Kostil.sh

WORKDIR /app
CMD ["/Kostil.sh"]