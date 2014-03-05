cd "${0%/*}";
gcc -w -lpthread -o ./bin/tickets.out ./src/main.c
./bin/tickets.out $1
