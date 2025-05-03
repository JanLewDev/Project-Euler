#!/bin/bash

SCRIPT_DIR="$(dirname "$(realpath "$0")")"
cd $SCRIPT_DIR
for file in *.cpp; do
    make "${file%%.*}" 2>log 1>/dev/null
    if [ -s log ]; then
        echo -e "\e[91mProblem w $file\e[39m"
        cat log
        exit 1
    fi
    echo -e "\e[92mSkompilowano $file\e[39m"
done

echo -e "\e[92mSkompilowano wszystkie pliki\e[39m"

plikcsv="wyniki.csv"

printf "Algorytm,Rozmiar Danych,Czas,Pamiec,Przypisania,Porownania\n" >$plikcsv
for file in *.cpp; do
    if [ "$file" == "gen.cpp" ]; then
        continue
    fi
    if [ "$file" == "spr.cpp" ]; then
        continue
    fi
    setA=(10 100 1000 10000 100000 1000000 10000000)
    insertion=false
    # jesli to insertion to nie testujemy dla miliona i wiecej
    if [[ "$file" == "insertion_sort.cpp" || "$file" == "double_insertion_sort.cpp" ]]; then
        setA=(10 100 1000 10000 100000)
        insertion=true
    fi
    for size in "${setA[@]}"; do
        echo -e "\e[92mTest $file, n = $size\e[39m"
        n=50
        if [ "$insertion" == true ] && [[ $size -eq 100000 ]]; then
            n=5
        fi
        if [[ $size -eq 1000000 ]]; then
            n=10
        fi
        if [[ $size -eq 10000000 ]]; then
            n=5
        fi
        for ((i = 1; i <= $n; i++)); do
            ./gen $i $size >in
            command time -f "%M %e %x" ./"${file%%.*}" <in >out 2>log
            read MEM TIME STATUS <log
            MILLISECONDS=$(echo "$TIME * 1000" | bc)
            MILLISECONDS="$(printf '%d' $MILLISECONDS 2>/dev/null)"

            przypisania=$(tail -2 out | head -1)
            porownania=$(tail -1 out)

            printf "%s,%s,%s,%s,%s,%s\n" "${file%%.*}" $size $MILLISECONDS $MEM $przypisania $porownania >>$plikcsv
        done
    done
done

# dodanie pustych statystyk, aby rozmiary tabel się zgadzaly w analiza.py
echo "insertion_sort,1000000,0,0,0,0
insertion_sort,10000000,0,0,0,0
double_insertion_sort,1000000,0,0,0,0
double_insertion_sort,10000000,0,0,0,0" >>$plikcsv
