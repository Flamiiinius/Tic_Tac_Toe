Jogo do Galo

Ricardo Dias Azevedo e Rodrigo Flaminio Ribeiro

Disciplina: Inteligência Artificial


Compilar: g++ IA2JogoGalo.cpp
Testado em: OS X e ubuntu
executar: ./a.out

input:
1)  1 ou 2 (se o 1º jogador joga c/ X ou O)
2)  1, 2, 3 ou 0 (Jogador vs Jogador; Jogador vs PC; PC vs PC; 0 para sair)
2.1) ->(SE 2) 1, 2 ou 0 (quem joga 1º PC ou jogador, 0 para voltar ao menu)
2.2) ->(SE 2 ou 3) 1 ou 2 (usar minimax OU alphabeta)
2.3) ->(Se 1 ou 2) A1,A2,a3,b1,b2,B3,c1,c2,C3 (letra(M ou m) seguida do numero para a posicao da matriz onde quer jogar -> repetir ate acabar o jogo)

3)volta ao menu 2

ex: ps: nao colocar o que esta dentro dos ()

ex:
2 (primeiro com O)
3 (PC vs PC)
1 (usar minimax)
0 (Sair do jogo)

ex2:
1 (1º X)
2 (PC vs Jogador)
1 (Ser EU(HUMANO) 1º a jogar)
2 ( usar alphaBeta)
A1 (escolher as jogadas)
A3
c2
b3
c1
0 (voltar para o menu)
0 (sair do jogo)



