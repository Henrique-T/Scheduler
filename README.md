# Scheduler 

## Requisitos do Projeto

1. **Arquivo de entrada no formato especificado pelo projeto:** O programa requer um arquivo de entrada chamado `entrada.txt`, 
que deve estar formatado de acordo com as especificações do projeto. Verifique se o arquivo `entrada.txt` contém os dados necessários 
no formato correto antes de executar o programa. Você pode editar manualmente este arquivo.

2. **Make instalado:** Certifique-se de que a ferramenta `make` está instalada no seu sistema. O `make` é usado para automatizar o processo de compilação e construção do projeto.

## Localização do arquivo de entrada

Verifique se o arquivo `entrada.txt` está no diretório correto. O programa espera que este arquivo esteja localizado no mesmo diretório em que o executável do programa será executado.

## Compilando e Executando o código

1. No arquivo src/main.cpp, altere o parâmetro da cpu para o algoritmo desejado. 
Os possíveis algoritmos são: "FCFS", "shortestJobFirst", "priorityWithoutPreemption", "priorityWithPreemption", "roundRobin".
    E.g.: INE5412 cpu("FCFS")

2. No diretório root do projeto,rode:
    `make all`
3. No diretório root do projeto, rode:
    `./Scheduler`
