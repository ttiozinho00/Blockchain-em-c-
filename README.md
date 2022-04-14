# Blockchain

## O que é isto?

 Esta é uma implementação de Blockchain muito simples em C++.
 
 ## Como funciona?
 
Por padrão, ele cria 1.000 usuários e 10.000 transações entre eles. Cada minerador faz 100 transações aleatórias verificadas e tenta minerar um bloco (a meta de dificuldade padrão é 4) em um certo número de tentativas (o valor padrão é 100). Se todos os mineradores falharem em minerar um bloco, o número de tentativas é multiplicado por 2.
 
Este Blockchain está usando meu algoritmo de hash personalizado e libbitcoin para geração de Merkle Tree.
 
 ## Example output
 
 ```
Block mined in attempt 114
Block 2: 00000e9bab5af4efba284c376024e62f1723e8fd08c83fd7c8a09f88b741ff51
Transactions left in pool: 9900
Miner 1 was first!
Block mined in attempt 11728
Block 3: 0000cce541972c457a01082e58cd49040eb6c2f973f544ff19605a353bf10b79
Transactions left in pool: 9800
Miner 5 was first!
Block mined in attempt 161
Block 4: 00002d65d1d91a4f8aa461b3aa88aaa67a571fdc8cda168bcd6fb5601a9f40b6
Transactions left in pool: 9700
Miner 4 was first!
Block mined in attempt 650
Block 5: 0000a1c7c5b9e39b64e8dcd320e8daaad9163bb8d636426d776eb0bf0d16af6b
Transactions left in pool: 9600
Miner 3 was first!
Block mined in attempt 1869
Block 6: 000071059de4536122bb29e7a17904eb84748e26d0b0f46c2d5f19d0e63bed0a
Transactions left in pool: 9500
Miner 4 was first!
Block mined in attempt 100
Block 7: 00005c43f559b150159a0652cc2e6e14c600166efa7ac5e9df5d53a5271088ce
Transactions left in pool: 9400
............
 ```
 
 ## How to run
 - `https://github.com/ttiozinho00/Blockchain-em-cpp`
 - `cd Blockchain-em-cpp`
 - `make`
 - `./bin/blockchain`
