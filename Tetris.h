#ifndef TETRIS_H
#define TETRIS_H

class Tetris{
    public:
        
        Tetris(int l);  //contrutor
        ~Tetris();      //destrutor

        Tetris(const Tetris &t);              //construtor por cópia
	    Tetris & operator=(const Tetris &t);  //operador de atribuição
        
        char get(int c,int l) const; //retorna um caractere que representa o estado de tal pixel no jogo atual
        int getNumColunas() const;   //retorna o número de colunas (largura) do jogo Tetris
        
        int getAltura(int c) const;  //retorna a altura da coluna c do jogo
        int getAltura() const;      //retorna a altura maxima do jogo atual.

        void removeColuna(int c);    //Remove a coluna c do jogo
        void removeLinhasCompletas(); //Remove linha que tem pixels não vazios em todas as linhas da mesma altura de coluna

        //Recebe como argumentos: coluna (um inteiro), linha (inteiro), o id de uma peca (um caractere) e uma 
        //rotacao (um inteiro que pode valer 0, 90, 180 ou 270).Essa funcao devera tentar adicionar a peca a tela atual
 
        bool adicionaForma(int coluna,int linha,char id, int rotacao);


    private:
        char **jogo;   //matriz dinamica para representar o jogo
        int *alturas;  //vetor dinamico para representar as alturas atuais d jogo
        int largura;   //quantidade de colunas do jogo

        void creat();   //Função auxiliar que constroi a matriz jogo e o vetor alturas
        void destroy(); //Função auxiliar que destroi a matriz jogo e o vetor alturas
       
        void desaloca(); //Função para desalocar as linhas quando tem certa atura n alocado para uma
                        //coluna por exemplo, mais o pixel mais alto está abaixo de n, logo podemos
                        //desalocar até a posição antes desse pixel
};

#endif