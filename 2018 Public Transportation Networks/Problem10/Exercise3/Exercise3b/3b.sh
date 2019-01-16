#!/bin/bash
g++ ./3b.cpp -o ./3b
./3b > 3b.lp
echo "read ./3b.lp optimize write solution ./3b.sol" | scip -q
