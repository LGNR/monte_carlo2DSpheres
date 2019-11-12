#!/bin/bash

for i in $(seq 324 350); 
do 
./monte_carlo $i 1 10 10 10 10 50 | cat >> presion_vs_eta  
done
