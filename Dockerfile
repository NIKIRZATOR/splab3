FROM debian
RUN apt-get update
RUN apt install gcc g++ -y
COPY lab3_1.cpp .
RUN g++ lab3_1.cpp -static
CMD ./a.out
  
