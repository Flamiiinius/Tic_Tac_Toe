//Feito por:
//Rodrigo Flaminio Ribeiro e Ricardo Azevedo
//No ambito da cadeira de IA 2o trabalho Abril


#include <iostream>
#include <climits>
#include <algorithm>
#include <cctype>

using namespace std;

bool retornar = false;
char jogadorUm;
char jogadorDois;

void print(char m[9]){ //imprime a matriz;
    cout << "    A - B - C" << endl ;
    cout << " 1  "<< m[0] << " | " << m[3] << " | " << m[6]  << endl;
    cout << "   ---+---+---" << endl;
    cout << " 2  "<< m[1] << " | " << m[4] << " | " << m[7]  << endl;
    cout << "   ---+---+---" << endl;
    cout << " 3  "<< m[2] << " | " << m[5] << " | " << m[8]  << endl << endl;
    
    return;
}

bool complete(char m[9]){  // ve se a matriz esta completa
    for(int i=0;i<9;i++)
        if(m[i]==' ') return false;
    
    return true;
}

int winner(char board[9]){ //se o jogador 1 tiver ganho retorna 1 -> se o jogador 2 tiver ganho retorna -1; se ninguem tiver ganho retorna 0
    
    if ((board[0] == jogadorUm && board[1] == jogadorUm && board[2] == jogadorUm) ||
        (board[3] == jogadorUm && board[4] == jogadorUm && board[5] == jogadorUm) ||
        (board[6] == jogadorUm && board[7] == jogadorUm && board[8] == jogadorUm) ||
        (board[0] == jogadorUm && board[3] == jogadorUm && board[6] == jogadorUm) ||
        (board[1] == jogadorUm && board[4] == jogadorUm && board[7] == jogadorUm) ||
        (board[2] == jogadorUm && board[5] == jogadorUm && board[8] == jogadorUm) ||
        (board[0] == jogadorUm && board[4] == jogadorUm && board[8] == jogadorUm) ||
        (board[2] == jogadorUm && board[4] == jogadorUm && board[6] == jogadorUm))
        return 1; //se o J1 ganho
    
    else if((board[0] == jogadorDois && board[1] == jogadorDois && board[2] == jogadorDois) ||
            (board[3] == jogadorDois && board[4] == jogadorDois && board[5] == jogadorDois) ||
            (board[6] == jogadorDois && board[7] == jogadorDois && board[8] == jogadorDois) ||
            (board[0] == jogadorDois && board[3] == jogadorDois && board[6] == jogadorDois) ||
            (board[1] == jogadorDois && board[4] == jogadorDois && board[7] == jogadorDois) ||
            (board[2] == jogadorDois && board[5] == jogadorDois && board[8] == jogadorDois) ||
            (board[0] == jogadorDois && board[4] == jogadorDois && board[8] == jogadorDois) ||
            (board[2] == jogadorDois && board[4] == jogadorDois && board[6] == jogadorDois))
        return -1; // se o J2 ganhou
    
    else
        return 0; //ninguem venceu (empate ou nao acabou)
}

void Player(char m[9],bool t){ //jogador
    
    char L,B,C;
    int c;
    bool f=true;
    
    if(t)B=jogadorUm;
    else B=jogadorDois;
    
    do{
        f=true;
        
        cout << "Onde Quer jogar? ex:(A1)" << endl;
        cin >> L >> C;
        
        if(islower(L)) L=toupper(L); //transformar minusculas em maiusculas
        
        if(C>'3'||C<'1')f=false; // se nao for 1,2,3 ->vai repetir
        c=C-'1'; //dar valor a variavel
        
        if(L=='A'){
            if(m[c]==' ')m[c]=B; //se e espaco da mete a letra
            else f=false;} // se ja tiver ocupado vai repetir
        else if(L=='B'){
            if(m[3+c]==' ')m[3+c]=B;
            else f=false;}
        else if(L=='C'){
            if(m[6+c]==' ')m[6+c]=B;
            else f=false;}
        else{f=false;}
        
    }while(!f);
}

int minimax(char m[9],bool t, int n,int *c){
    
    (*c)++;
    char B;
    int mini =INT_MAX, maxi =INT_MIN,res=0,pmin,pmax;
    
    if(t)B=jogadorUm;
    else B=jogadorDois;
    
    if(winner(m)!=0) return winner(m); //ve se algum ganhou
    if(complete(m)) return 0; // se ninguem tiver ganho, ver se e empate
    
    //a partir daqui sabemos que ha jogadas possiveis
    
    if(n==0){
        for(int i=0;i<9;i++){
            if(m[i]==' '){
                m[i]=B;
                if(winner(m)) return winner(m);
                m[i]=' ';
            }
        }
    }
    
    for (int i = 0; i <9; i++){ // em sitios onde ainda podemos jogar
        if(m[i] == ' '){
            
            if(!t){ //se for o jogador 2 a jogar
                m[i] = B; //ocupar a posicao c/ jogadorUm ou 'O'
                res = minimax(m,!t, n + 1,c); //gerar os filhos
                m[i]= ' '; // voltar a por a matriz ao estado inicial
                if(res < mini){ //valor para retornar
                    mini = res;
                    if (n == 0) pmin=i; //posicao do array onde vamos jogar
                }
            }
            
            else if(t){ //se for jogador 1 a jogar ->mesmo que em cima
                m[i] = B;
                res = minimax(m,!t, n + 1,c);
                m[i]= ' ';
                if(res > maxi){
                    maxi = res;
                    if(n==0) pmax=i;
                }
            }
            
        }
    }
    if(n==0){ //ja acabou, colocar jogadorUm ou 'O' no sitio onde queremos jogar
        if(t)m[pmax]=B;
        else m[pmin]=B;
    }
    
    if (t) return maxi;
    else return mini;
}

int alphaBeta(char m[9],int deep, int a, int b,bool t,int *c){ //algoritmo do alpha Beta
    
    (*c)++; //incrementar contador de nos
    int pmin,pmax; //posicao onde queremos jogar
    char B; //X ou O
    if(winner(m)!=0) return winner(m); //mesma historia de cima
    if(complete(m)) return 0;
    if(t)B=jogadorUm;
    else B=jogadorDois;
    
    if(t){  //se 1o
        int v=INT_MIN; //value comeca em MIN
        for(int i=0;i<9;i++){
            if(m[i]==' '){ //encontrar espaco vazio
                m[i]=B; //colar 'X' no sitio
                v=max(v,alphaBeta(m,deep+1,a,b,!t,c)); //gerar os filhos
                if(v > a){ //ve o valor dele for maior que o maximo
                    a=v; //maximo tem agora o valor
                    if(deep==0)pmax=i; //atualizar pos onde queremos jogar (se for a 1a iteracao)
                }
                m[i]=' '; //voltar a por a pos a 0
                if(b <= a){ // se o minimo maior ou igual ao maximo parar
                    break;
                }
            }
        }
        if(deep==0)m[pmax]=B; // colocar o 'X' na posicao onde queremos jogar
        return v;
    }
    else{ // se 2o
        int v=INT_MAX;
        for(int i=0;i<9;i++){
            if(m[i]==' '){
                m[i]=B;
                v=min(v,alphaBeta(m,deep+1,a,b,!t,c));
                if(b>v){
                    b=v;
                    if(deep==0)pmin=i;
                }
                b=max(b,v);
                m[i]=' ';
                if(b <= a) break;
            }
        }
        if(deep==0)m[pmin]=B;
        return v;
    }
}

void M1(){ //Jogador vs Jogador
    char m[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '}; //matriz
    bool t; //turno
    print(m);
    for(int i=0;i<9;i++){ //enquanto nao a vencedor
        if(complete(m)) break; //se estiver cheio para
        if(winner(m)!=0) break; //se ouver vencedor para
        if(i%2==0)t=true; //ver de quem e o turno
        else t=false;
        Player(m,t);// jogador jogar
        print(m); //imprimir a matriz
    }
    //	aqui ja ha vencedor ou empate
    
    if(winner(m)==0) cout << "Foi empate!!!" << endl<< endl;
    else if(winner(m)==1) cout << "Ganhou o Jogador 1!!!" << endl<< endl;
    else cout << "Ganhou o Jogador 2!!!" << endl<< endl;
    
    return;
}

void M2(){ // Jogador vs PC
    char m[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '}; //matriz
    int c,h=0;
    while(h!=1&&h!=2){ //escolher o algoritmo para o pc
        cout << "Quer Usar Minimax (1) ou AlphaBeta (2)" << endl;
        cin >> h;
    }
    print(m);
    
    while(true){ //enquanto nao acabar
        c=0; //contador a 0 para cada iteracao
        if(complete(m)) break; //se se ja acabou
        if(winner(m)!=0) break; //ver se ha vencedor
        Player(m,true); //jogaor
        print(m); //imprimir
        if(complete(m)) break; //ver se ja acabou
        if(winner(m)!=0) break;
        if(h==1)minimax(m,false,0,&c); //turno do pc
        else if(h==2)alphaBeta(m,0,INT_MIN,INT_MAX,false,&c);
        print(m);
        cout << c << " nos gerados!" << endl;
    }
    
    //	delete m; //Devo???
    
    if(winner(m)==0) cout << "Foi empate!!!" << endl<< endl;
    else if(winner(m)==1) cout << "Parabens, o voce ganhou!!!" << endl<< endl;
    else cout << "Ganhou o PC" << endl<< endl;
    
    return;
}

void M3(){ //PC vs Jogador
    char m[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '}; //matriz
    int c;
    int h;
    while(h!=1&&h!=2){
        cout << "Quer Usar Minimax (1) ou AlphaBeta (2)" << endl;
        cin >> h;
    }
    print(m);
    while(true){
        c=0;
        if(complete(m)) break;
        if(winner(m)!=0) break;
        if(h==1)minimax(m,true,0,&c);
        else if(h==2)alphaBeta(m,0,INT_MIN,INT_MAX,true,&c);
        print(m);
        cout << c << " nos gerados!" << endl;
        if(complete(m)) break;
        if(winner(m)!=0) break;
        Player(m,false);
        print(m);
    }
    
    //	delete m; //Devo???
    
    if(winner(m)==0) cout << "Foi empate!!!" << endl<< endl;
    else if(winner(m)==(-1)) cout << "Parabens, voce ganhou!!!" << endl<< endl;
    else cout << "Ganhou o PC" << endl<< endl;
    
    return;
}

void M4(){ //PC vs PC
    char m[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '}; //matriz
    int c=0,h;
    bool t; //turno
    while(h!=1&&h!=2){ //escolher algoritmo
        cout << "Quer Usar Minimax (1) ou AlphaBeta (2)" << endl;
        cin >> h;
    }
    print(m);
    for(int i=0;i<9;i++){ //max de 9 jogadas ->mesma ideia do 1o
        c=0; //contador a 0 para cada iteracoa
        if(complete(m)) break;
        if(winner(m)!=0) break;
        if(i%2==0)t=true; //ver de quem e o turno
        else t=false;
        if(h==1)minimax(m,t,0,&c);
        else if(h==2)alphaBeta(m,0,INT_MIN,INT_MAX,t,&c);
        cout << c << " nos gerados acima!" << endl << endl;
        print(m);
    }
    
    if(winner(m)==0) cout << "Foi empate!!!" << endl<< endl;
    else if(winner(m)==1) cout << "Ganhou o PC 1!!!" << endl<< endl; //Nunca acontece
    else cout << "Ganhou o PC 2!!!" << endl<< endl;  //Nunca Acontece
    
    return;
}

void quemJoga(){
    int n=5;
    
    while(n!=0){ //escolher o modo
        cout << "Quem joga primeiro?" << endl;
        cout << "  1 -> Jogador" << endl;
        cout << "  2 -> Computador" << endl;
        cout << "  0 -> Voltar" << endl;
        cin >> n;
        switch(n){
            case 0: retornar = true;break;
            case 1: M2();break;
            case 2: M3();break;
        }
        
    }
    return;
}

void menu(){
    int n=5;
    
    while(n!=0){ //escolher o modo
        cout << "Jogo do galo!" << endl;
        cout << "  1 -> Jogar contra outro jogador" << endl;
        cout << "  2 -> Jogar contra o computador" << endl;
        cout << "  3 -> Computador contra computador" << endl;
        cout << "  0 -> Sair" << endl;
        
        cin >> n;
        switch(n){
            case 0: exit(0);break;
            case 1: M1();break;
            case 2: quemJoga();break;
            case 3: M4();break;
        }
        if(retornar)
            n = 4;
    }
}
void x_ou_o(){
    int test;
    cout << "O 1o a jogar, joga com X ou O?" << endl;
    cout << "  1 -> X" << endl;
    cout << "  2 -> O" << endl;
    cin >> test;
    if (test == 1) {
        jogadorUm = 'X';
        jogadorDois = 'O';
    }
    else if (test == 2){
        jogadorUm = 'O';
        jogadorDois = 'X';
    }
    else x_ou_o();
    
    return;
}

int main(){
    
    x_ou_o();
    menu();
    
    return 0;
}