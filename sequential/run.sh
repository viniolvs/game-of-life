#!/bin/bash

# Nome do arquivo CSV de saída
output_csv="outputs/sequential.csv"

# Cabeçalho do arquivo CSV
echo "Size,Generations,Time" > $output_csv

for input_file in entry/*.in; do
    echo "Running $input_file..."
    result=$(./sequential/life < $input_file)
    
    # Extrair o número de gerações e o tempo de execução da saída do programa
    gen=$(echo "$result" | awk '{print $1}')
    time_exec=$(echo "$result" | awk '{print $2}')
    
    # Extrair o tamanho da matriz e o número de gerações do nome do arquivo
    size_gen=$(basename $input_file .txt)
    size=$(echo $size_gen | cut -d'_' -f2)
    gen=$(echo $size_gen | cut -d'_' -f3)
    
    # Adicionar a linha ao arquivo CSV
    echo "$size,$gen,$time_exec" >> $output_csv
done
