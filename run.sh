cd  Codigo/

for counter in $(seq 1 100);
do
    python3 parser.py

    g++ -c example.cpp
    g++ -o example example.o -lz3
    ./example >> processo_de_analise.txt

done

g++ tempo_exec.cpp -o tempo
./tempo