cd "${0%/*}";
gcc -lpthread -o ./bin/tickets.out ./src/main.c
./bin/tickets.out $1
