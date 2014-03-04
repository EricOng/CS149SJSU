cd "${0%/*}";
gcc -o ./bin/tickets.out ./src/main.c
./bin/tickets.out $1
