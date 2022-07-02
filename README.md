# Bitcoin Wallet Checker

Install:
```shell
cmake .
cmake --build .
```

Run:
```shell
./collector
```

Output:
```shell
dev@localhost:~/collector$ ./collector 
Enter wallet: 1P5ZEDWTKTFGxQjZphgWPQUpe554WKDfHQ << Microstrategy main wallet
Wallet      : 1P5ZEDWTKTFGxQjZphgWPQUpe554WKDfHQ
Balance     : 132003.543918
Transactions: 760
Tot Received: 231665.428404
```

Redis:
https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-redis-on-ubuntu-20-04
```shell
sudo apt install redis-server
```