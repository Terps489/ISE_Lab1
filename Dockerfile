FROM ubuntu:latest

RUN apt-get update && apt-get install -y git cmake make g++ vim

COPY Kostil.sh /Kostil.sh
RUN chmod +x /Kostil.sh

WORKDIR /app
CMD ["/Kostil.sh"]