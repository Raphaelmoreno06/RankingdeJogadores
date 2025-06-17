Sistema de Ranking de Jogadores
--------------------------------------------------
O projeto "Sistema de Ranking de Jogadores" tem como objetivo implementar uma aplicação em linguagem C para gerenciar um ranking de jogadores. O sistema permite operações como cadastro de jogadores, atualização de pontuações, exibição do ranking, ordenação e exclusão de dados. Além disso, o sistema utiliza estruturas de dados como Lista Encadeada, Pilha e Fila para organizar os elementos.
--------------------------------------------------

Estruturas de Dados Utilizadas
- Lista Encadeada: Estrutura principal para armazenar os jogadores.
- Pilha (Stack - LIFO): Utilizada para manter um histórico das inserções realizadas.
- Fila (Queue - FIFO): Utilizada para manter a ordem de entrada dos jogadores.
--------------------------------------------------

Funcionalidades Implementadas
- Inserção de novo jogador no ranking.
- Atualização da pontuação de jogadores existentes.
- Exibição do ranking de jogadores.
- Ordenação da lista por pontuação utilizando o algoritmo Merge Sort.
- Exclusão completa da tabela de jogadores.
- Salvamento e carregamento dos dados em arquivo binário (jogadores.dat).

--------------------------------------------------

Fluxo Principal do Programa
1. Exibição do menu principal para o usuário.
2. Recebimento da escolha do usuário.
3. Execução da operação selecionada.
4. Atualização das estruturas de dados.
5. Salvamento dos dados para garantir persistência.

--------------------------------------------------

Estrutura de Arquivos do Projeto
- main.c: Código-fonte principal.
- jogadores.dat: Arquivo binário para armazenar os dados dos jogadores.

--------------------------------------------------
Instruções de Compilação

Para compilar o programa utilizando o compilador GCC, utilize o seguinte comando no terminal:
gcc main.c -o ranking

Após a compilação, o executável gerado poderá ser executado normalmente.
--------------------------------------------------
