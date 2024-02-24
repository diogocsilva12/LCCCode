#!/bin/bash

inicio=$(date +%s)

for ((i = 1; i <= $1; i++))
do
    IDADE=$(((RANDOM % 100)+1))
    echo "./pessoas -i Pessoa${i} $IDADE"

    ./pessoas -i Pessoa${i} $IDADE

done

fim=$(date +%s)
tempo_gasto=$((fim - inicio))

echo "O script levou $tempo_gasto segundos para executar"


