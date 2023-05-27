all: exec

main.o: main.c
    gcc -o main.o -c main.c

product.o: product.c
    gcc -o product.o -c product.c

customer.o: customer.c
    gcc -o customer.o -c customer.c



exec: main.o car.o user.o 
    gcc main.o product.o customer.o  -o exec
