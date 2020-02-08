#include <iostream>
#include "Tetris.h"

using namespace std;

    Tetris::Tetris(int l){
        largura = l;       // inicializa a largura(qtd de colunas com o valor passado como paramentro)
        creat();          //Função responável por construir a matriz do jogo e o vetor de alturas
    
    }

    Tetris::~Tetris(){
        destroy();      //Função responsável por destruir a matriz do jogo e o vetor de alturas
    }

    void Tetris::creat(){
      
        alturas = new int[largura];        //aloca o vetor alturas para quantidade de colunas(larguras)

        for(int i=0;i<largura;i++)      // todas colunas inicialmente apontam para nenhuma linha
            alturas[i] = 0;

        jogo = new char*[largura];           //criando matriz do jogo inicialmente com a qtd de colunas(largura) passadas
        
        for(int i = 0;i < largura; i++){
            jogo[i] = new char[alturas[i]];        
            for(int j = 0;j < alturas[i]; j++)
                jogo[i][j] = ' ';                  // atribuindo todas as posições da matriz como vazia
        }
    }

    Tetris::Tetris(const Tetris &t){
        
        jogo = NULL;        //Faz jogo apontar para NULL
        alturas = NULL;    //Inicializa todas as alturas com NULL
        largura = 0;      //como criaremos outro jogo, setamos a largura para 0
        creat();         //chamamos o a função creat (construtor)
        *this = t;      //atribui-se(chama o operador de atribuição) o jogo para oque foi passado por parâmetro
    }

    Tetris & Tetris::operator=(const Tetris &t){

        if(this==&t)               //Verifica se this ja está apontando para Tetris que ele quer apontar
            return *this;          //se sim, retorna
	    
        destroy();           //como this não é igual a t,destruimos this
        
        largura = t.getNumColunas();       //faz com que a largura de this seja igual a largura de t

        //cria um novo vetor alturas de tamanho igual a t, e logo depois copia o conteúdo
        //de t para o vetor alturas de this
        
        alturas = new int[getNumColunas()];
        for(int i=0;i<getNumColunas();i++)    
            alturas[i] = t.getAltura(i);  

        //cria uma nova matriz de tamanho igual a t, e logo depois copia o conteúdo
        //de t para a matriz de this

        jogo = new char*[getNumColunas()];        
        for(int i=0;i<getNumColunas();i++){   
            jogo[i] = new char[getAltura(i)];
            for(int j = 0;j < getAltura(i); j++)
                jogo[i][j] = t.get(i,j);
        } 

       
        return *this;  //retorna this
    }

    void Tetris::destroy(){
        for(int i = 0;i < getNumColunas(); i++)     // deleta a matriz jogo
            delete []jogo[i];
        delete []jogo;

        delete []alturas;                // delta o vetor com as alturas

        largura = 0;                     //como deletou a matriz, a qtd de colunas é 0
    }

    char Tetris::get(int c,int l)const{
        //recebe dois argumentos: a coluna (primeiro argumento) e a linha (segundo argumento) de um pixel 
       // e retorna um caractere que representa o estado de tal pixel no jogo atual
        
        if(c < 0 || c > (largura -1) || l < 0)  //Verifica se a coluna passada como parâmtro não existe ou se é uma linha
            return ' ';                      // negativa , se não existe retorna vazio
        
        if( l > ( alturas[c] - 1 )) //Após verificar se aa coluna existe, verifica se a altura daquela coluna é menor que
            return ' ';            //a linha passada, se é, quer dizer que está tentando pegar uma posição inválida,logo
                                  //retorna vazio
        
        return jogo[c][l];  // retorna o pixel
    }

    int Tetris::getNumColunas()const{
        //retorna o número de colunas (largura) do jogo Tetris. 
    
        return largura;
    }

    int Tetris::getAltura(int c)const{
        //retorna a altura da coluna c do jogo. A altura de uma coluna é igual a altura 
        //do pixel (não vazio) mais alto da coluna. Uma coluna onde todos os pixels são vazios possui altura 0

        if(c < 0 || c > (largura-1))  //Verifica se a coluna passada como parâmtro não existe
            return 0;                //se não existe, retorna 0
 
        return alturas[c];   //se existe retorna a altura daquela posição
    }

    int Tetris::getAltura()const{
        //retorna a altura maxima do jogo atual.

        int max = alturas[0];
        
        for(int i=1;i<getNumColunas();i++)  //Faz uma busca em todo vetor de alturas, e alturas[i] for maior que 0, ou seja,
            if(getAltura(i) > max)    //se algum tiver algum pixel ele pega essa altura, daí ao acabar o for a função
                max = alturas[i];   //ira rtornar o maior valor que tem o vetor alturas, que no caso é a altura do 
                                    //maior pixel
        return max;
        
    }


    void Tetris::removeColuna(int c){

        if(c<0 || c > (getNumColunas()-1))       //Testa se c (coluna) é negativa ou um número maior do que a qtd que vc alocou
            return;

        int *altura = new int[getNumColunas()-1];  //cria um vetor auxiliar para armazenar as alturas das colunas 
                                          //que nao foram removidas

        int j = 0;                     //variavel auxliar para salvar corretamente a posição do vetor altura
        for(int i=0;i<getNumColunas();i++){
            if(i == c)              //se i(coluna) for igual a coluna c, vamos deletar essa coluna, logo a ignoramos
                continue;
            else{
                altura[j] = getAltura(i); //se i não for igual a c, copiamos a altura de i para o vetor auxiliar na pos j
                j++;                    // iteramos a posição
            }
        }

        delete []alturas;
        alturas = new int[getNumColunas()-1];  //realocamos o vetor de altura original para largura-1 (numero de colunas)
                                       // ja que excluimos uma coluna, realocaremos com uma coluna a menos
        for(int i=0;i<(getNumColunas()-1);i++) //copiamos oq está no vetor auxiliar para o principal, o for varia até largura -1
            alturas[i] = altura[i];    //porque agora temos uma coluna a menos 
        
        delete []altura;              //como não precimas mais do vetor auxiliar, o destruimos


        char **aux = new char*[getNumColunas()-1];   //mesmo procedimento, so que agora criamos uma matriz auxiliar
        for(int i=0;i<(getNumColunas()-1);i++)       //com uma coluna a menos
            aux[i] = new char[getAltura(i)];
        
        int k = 0;          //variavel auxliar para salvar corretamente a posição da matriz aux
        
        for(int i = 0;i < getNumColunas(); i++){ //se i(coluna) for igual a coluna c, vamos deletar essa coluna, logo a ignoramos
            if(i == c)
                continue;
            
            else{
                for(int j = 0;j < alturas[k]; j++)
                    aux[k][j] = get(i,j);//se i não for igual a c, copiamos o jogo de i para o vetor auxiliar na pos k,j
                k++;  // iteramos a posição
            }
        }

        largura = largura - 1;   //como a temos uma coluna a menos, colocamos a largura igual a ela mesma -1
 
        for(int i = 0;i < (getNumColunas()+1); i++) //deletamos o jogo antigo com (getNumColunas()+1) pois 
            delete []jogo[i];                      //é referente a qtd de largura que o jogo tinha  antes
        delete []jogo;

        //realocamos a matriz de jogo original para largura-1 (numero de colunas)
        // ja que excluimos uma coluna, realocaremos com uma coluna a menos (largura agora vale largura -1)

        jogo = new char*[getNumColunas()];
        for(int i=0;i<getNumColunas();i++){
            jogo[i] = new char[getAltura(i)];
            for(int j = 0;j < getAltura(i); j++)
                jogo[i][j] = aux[i][j];
        }

         //copiamos oq está no jogo auxiliar para o principal, o for varia até a nova largura
        //porque agora temos uma coluna a menos 

        //como não precimas mais do jogo auxiliar, o destruimos

        for(int i = 0;i < getNumColunas(); i++)
            delete []aux[i];
        delete []aux;
    
    }

    void Tetris::desaloca(){
        for(int i=0;i<getNumColunas();i++){        //varremos todas as colunas para verificar se vamos desalocar algo
            for(int j=(getAltura(i)-1);j>=0;j--){  //começa do final para ver se tem algo la no topo que não precisa de memoria
                if(jogo[i][j] !=' ' )          //se jogo[i][j] tiver pixel, essa coluna ja ta com a altura certa
                    break;                     // logo passamos para a próxima
                if(jogo[i][j] == ' '){         //se jogo[i][j] n tiver pixel, a altura dessa coluna pode ser diminuida
                    //com isso, criamos uma nova linha, que recebe a altura atual de linha -1, ja que diminuiremos 1 nela
                    char *novalinha = new char[getAltura(i)-1];
                    
                    //copiamos oque está na linha antiga -1 para a nova
                    for(int k=0;k<getAltura(i)-1;k++)
                        novalinha[k] = jogo[i][k];
                    
                    //deletamos a linha aantiga e fazemos o jogo daquela posição apontar para a nova linha 
                    delete []jogo[i];
                    jogo[i] = novalinha;

                    //atualizamos o vetor alturas, ja que a linha daquela posição abaixou 1 nivel
                    alturas[i] = alturas[i] - 1;
                }
            }
            //agora o codigo vai para a proxima coluna
        }
    }


    void Tetris::removeLinhasCompletas(){ 
        //Verifique se todas as alturas tem pelo menos 1 pixel em cada coluna, se não, não
        //precisa continuar a função já que não terá nehuma linha completa
        
        for(int i=0;i<getNumColunas();i++) 
            if(getAltura(i) == 0)
                return;
        
        bool completa = true;  //Variável auxiliar para saber se todas as colunas tem pelo menos uma certa altura, para 
                              //poder ser aplicado a tentativa de remover a linha
        bool linhaC = false;  //variável auxiliar para verifacar se todas as colunas de certa linha tem pixel

        //criamos uma nova matriz de mesmo tamanho que o jogo com todos pixels vazio
        

        //verifica se todas as altura de da coluna i tem um número maior ou igual a i, se sim, 
        //podemos conitnuar, se não, pode ser q alguma não tenha nenhum pixel, logo não podemos remover a linha
        int i=0;
        for(i=0;i<getAltura();){
            for(int j=0;j<getNumColunas();j++)
               if(getAltura(j) < i)
                    completa = false;   
            
                        
            //como podemos continuar agora o código verifca se tem alguma posição é vazia, se sim não podemos limpar aquela
            //linha, se todas as posições daquela linha tiver pixel, quer dizer que podemos limpar a linha, com isso,
            //linhaC recebe true
            if(completa == true){
                for(int k=0;k<getNumColunas();k++){
                    if(get(k,i) == ' '){
                        linhaC = false;
                        break;
                    }
                    else
                        linhaC = true;
                }
            }
            
            //limpamos a linha colocando todos valores dela como vazio
            if(linhaC == true){
                
                //nessa pate do código já é certo que tem uma linha completa, logo para a excluirmos,
                //criamos um jogo auxiliar (novojogo) e setamos todas as posições para ' '
                char **novojogo;
                novojogo = new char*[getNumColunas()];       
                for(int m=0;m<getNumColunas();m++){  
                    novojogo[m] = new char[getAltura(m)-1];
                    for(int n=0;n<(getAltura(m)-1);n++)
                        novojogo[m][n] =  ' ';
                }
                
                //limpamos a linha completa
                for(int k=0;k<getNumColunas();k++){
                    jogo[k][i] = ' ';
                }

                //agora copiamos o conteúdo do jogo com a linha apagada para o novo jogo, ignorando a linha apagada
                //com o comando continue
                int aux = 0;
                for(int c=0;c<getNumColunas();c++){
                    for(int l=0;l<getAltura(c);l++){
                        if(l == i )
                            continue;
                        novojogo[c][aux] =  get(c,l);
                        aux++;
                    }
                    aux = 0;
                }

                //com tudo copiado, deletamos a matriz jogo
                for(int c = 0;c < getNumColunas(); c++)  
                    delete []jogo[c];
                delete []jogo;

                //agora criamos a matriz jogo novamente com  todas as alturas -1, ja qe removemos uma linha de cada altura
                // e copiamos o conteúdo de noovojogo para o jogo original
                jogo = new char*[getNumColunas()];       
                for(int i=0;i<getNumColunas();i++){      
                    jogo[i] = new char[getAltura(i)-1];
                    for(int l=0;l<(getAltura(i)-1);l++)
                        jogo[i][l] = novojogo[i][l];
                }

                //como não preciamos mais da matriz novojogo, a deletamos
                for(int c = 0;c < getNumColunas(); c++)  
                    delete []novojogo[c];
                delete []novojogo;
                
                //como  uma linha foi removida, todas as alturas descrementam uma unidade 
                for(int c=0;c<getNumColunas();c++)
                    alturas[c]--;
    
            }
            
            //toda vez que uma linha é excluida, temos que voltar do inicio para verifcar, logo se linhaC não for
            //true o i itera, e se for , voltmaos a verificar do inicio
            if(linhaC != true)
                i++;
            else
                i = 0;
            
            
            //variáveis voltam ao seus valores originais para recomeçar o for
            completa = true;
            linhaC = false;
        }
        
        desaloca();  //chama a função para desalocar oque pode ter ficado sobrando no no jogo 
    }


    bool Tetris::adicionaForma(int coluna,int linha,char id, int rotacao){
        if(coluna<0 || coluna > (getNumColunas()-1))  //Testa se c (coluna) é negativa ou um número maior do que a qtd que vc alocou
            return false;     //Se sim , ja retorna false, logo não é possível adicionar a peca
        
        char peca[4][4];   //Matriz que amazena a peca (id) 

        //seta todas as posições da matriz como vazio
        for(int i = 0;i < 4; i++)
            for(int j = 0;j < 4; j++)
                peca[i][j] = ' ';
          
        //Nesse momento ele verifica primeiro o id que é a o tipo de peca que ai ser armazenado nao matriz peca
        //depois ele verifica a rotação, com isso pra cada caso armazenei na matriz como ficaria a peca com cada
        //tipo de rotação. Com isso a matriz peca recebe um tipo de peca com sua determinada rotação
        
        if(id == 'I'){
            if(rotacao == 0  || rotacao == 180){
                peca[0][0] = 'I';
                peca[1][0] = 'I';
                peca[2][0] = 'I';
                peca[3][0] = 'I';
            }

            else if(rotacao == 90|| rotacao == 270){
                peca[0][0] = 'I';
                peca[0][1] = 'I';
                peca[0][2] = 'I';
                peca[0][3] = 'I';
            }
        }
        
        else if(id == 'J'){
            if(rotacao == 0){
                peca[0][3] = 'J';
                peca[1][3] = 'J';
                peca[0][2] = 'J';
                peca[0][1] = 'J';
                peca[0][0] = 'J';
            }

            else if(rotacao == 90){
                peca[3][0] = 'J';
                peca[0][1] = 'J';
                peca[1][1] = 'J';
                peca[2][1] = 'J';
                peca[3][1] = 'J';
            }

            else if(rotacao == 180){
                peca[0][0] = 'J';
                peca[1][0] = 'J';
                peca[1][1] = 'J';
                peca[1][2] = 'J';
                peca[1][3] = 'J';
            }

            else if(rotacao == 270){
                peca[0][1] = 'J';
                peca[0][0] = 'J';
                peca[1][0] = 'J';
                peca[2][0] = 'J';
                peca[3][0] = 'J';
            }
            
        }

        else if(id == 'L'){
            if(rotacao == 0){
                peca[0][0] = 'L';
                peca[0][1] = 'L';
                peca[0][2] = 'L';
                peca[0][3] = 'L';
                peca[1][0] = 'L';
            }

            else if(rotacao == 90){
                peca[0][1] = 'L';
                peca[1][1] = 'L';
                peca[2][1] = 'L';
                peca[3][1] = 'L';
                peca[0][0] = 'L';
            }

            else if(rotacao == 180){
                peca[1][0] = 'L';
                peca[1][1] = 'L';
                peca[1][2] = 'L';
                peca[1][3] = 'L';
                peca[0][3] = 'L';
            }

            else if(rotacao == 270){
                peca[0][0] = 'L';
                peca[1][0] = 'L';
                peca[2][0] = 'L';
                peca[3][0] = 'L';
                peca[3][1] = 'L';
            }
            
        }

        else if(id == 'O'){
            peca[0][0] = 'O';
            peca[0][1] = 'O';
            peca[1][0] = 'O';
            peca[1][1] = 'O';

            
        }

        else if(id == 'S'){
            
            if(rotacao == 0 || rotacao == 180){
                peca[0][1] = 'S';
                peca[0][2] = 'S';
                peca[1][0] = 'S';
                peca[1][1] = 'S';

            }

            else if(rotacao == 90 || rotacao == 270){
                peca[0][0] = 'S';
                peca[1][0] = 'S';
                peca[1][1] = 'S';
                peca[2][1] = 'S';

            }
        }

        else if(id == 'T'){
            if(rotacao == 0){
                peca[0][0] = 'T';
                peca[0][1] = 'T';
                peca[0][2] = 'T';
                peca[1][1] = 'T';
            }

            else if(rotacao == 90){
                peca[0][1] = 'T';
                peca[1][1] = 'T';
                peca[2][1] = 'T';
                peca[1][0] = 'T';
            }

            else if(rotacao == 180){
                peca[1][0] = 'T';
                peca[1][1] = 'T';
                peca[1][2] = 'T';
                peca[0][1] = 'T';
            }

            else if(rotacao == 270){
                peca[0][0] = 'T';
                peca[1][0] = 'T';
                peca[2][0] = 'T';
                peca[1][1] = 'T';
            }
        }

        else if(id == 'Z'){
            if(rotacao == 0 || rotacao == 180){
                peca[0][0] = 'Z';
                peca[0][1] = 'Z';
                peca[1][1] = 'Z';
                peca[1][2] = 'Z';

            }

            else if(rotacao == 90 || rotacao == 270){
                peca[0][1] = 'Z';
                peca[1][1] = 'Z';
                peca[1][0] = 'Z';
                peca[2][0] = 'Z';
            }
        }

        //as posições que não tem pixel viram ' '
        for(int i = 0;i < 4; i++)
            for(int j = 0;j < 4; j++)
                if(peca[i][j] != id)
                    peca[i][j] = ' ';
       

        //Vamos alocar inicialmente um vetor alturas auxiliar e uma matriz jogo auxiliar exatamente
        //iguais aos originais, caso necessitar fazer alguma alocação, alocaremos na matriz auxiliar e só depois 
        //copiaremos pra original caso uma peça possa realamente ser adicionado Vamo supor que aloquei
        //uma certa altura para um pedaço da peça mas na hora de ver o outro pedaço da peça ela não poderia
        //ser adicionad, logo o jogo retornaria false e eu teria alocado atoa, com essas matriz auxiliar , 
        //se o joog retornar true eu copio das auxliares para as originais e se o jogo retornar false, 
        //eu apenas deleto as matriz auxiliar como também o vetor altura auxiliar.

        int *AlturaAux = new int[getNumColunas()];
        for(int i=0;i<getNumColunas();i++)
            AlturaAux[i] = getAltura(i);
        
        char **jogoAux = new char*[getNumColunas()];        
        for(int i=0;i<getNumColunas();i++){
            jogoAux[i] = new char[getAltura(i)];
            for(int j = 0;j < getAltura(i); j++)
                jogoAux[i][j] = get(i,j);
        }

        //Parte principal do código, verifca se a a peca poderá ser adicionada ao jogo, ele só verifica quando a
        //posição do de peca tem um pixel

        //coluna+j , é a posição na matriz jogo da peca atual, pois coluna é o que foi pasado por parâmetro e j é
        //é coluna q o pixel está na matriz peca

        //linha-i , é a posição na matriz jogo da peca atual, pois linha é o que foi pasado por parâmetro e i é
        //é linha q o pixel está na matriz peca
        
        
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(peca[i][j] != ' '){
                    if((coluna+j) > (getNumColunas() - 1) || (linha -i ) < 0){  // verifica se está tentando adicionar um pixel em alguma
                        
                        //deleta o vetor e a matriz auxiliar já que retornara false, e não poderemos alocar nada
                        delete []AlturaAux;
                        
                        for(int i = 0;i < getNumColunas(); i++)    
                            delete []jogoAux[i];
                        delete []jogoAux;
                        
                        
                        return false;                      // posição inválida, se sim, retotna false
                    }
                    // verifica se está tentado adicionar um pixel em uma altura ja existente, ou seja, não precisará
                    //alocar mais memória pois ess linha - i existe
                    if((getAltura(coluna+j) - 1) >= (linha -i)){ 
                        //verifica se a posição do jogo ja tem pixel, se sim, o pixel não pde ficar ser adicionado
                        //naquela posição
                        if(get(coluna+j,linha-i) != ' '){
                            //deleta o vetor e a matriz auxiliar já que retornara false, e não poderemos alocar nada
                            delete []AlturaAux;

                            for(int i = 0;i < getNumColunas(); i++) 
                                delete []jogoAux[i];
                            delete []jogoAux;

                            return false;
                        }     
                    }
                    
                    //como não existe a altura na qual o pixel era pra ser adicinada, nesse parte do código
                    //será alocada a altura necessária
                    else{
                        
                    
                        //cria uma nova linha com a altura passada pelo função inicalmente toda vazia
                       
                        char *novaLinha = new char[linha+1];
                        for(int k=0;k<(linha+1);k++)
                            novaLinha[k] = ' ';

                        //copia o conteúdo da linha pequena para a linha maior q acaba de ser criada

                        for(int k=0;k<getAltura(coluna+j);k++)
                            novaLinha[k] = jogoAux[coluna+j][k];
                        
                        //deletamos a linha na qual vai ser alocada um tamanho maior
                        delete []jogoAux[coluna+j];

                        //fazemos a coluna correspondente ao que precisa ser alocado apontar para a nova linha
                        jogoAux[coluna+j] = novaLinha;

                        //atualizmaos a altura da coluna alocada , como o novo tamanho

                        AlturaAux[coluna + j] = linha + 1;
                    }  
                }   
            }
        }  

        //como dito acima, nessa parte do código, a função retornara true, logo a peça poderar ser adicionada,
        //com isso atualizamos o vetor alturas com os tamanhos de alturaAux
        for(int i=0;i<getNumColunas();i++)
            alturas[i] = AlturaAux[i];
        
        //deletamos o jogo antigo
        for(int i = 0;i < getNumColunas(); i++)
            delete []jogo[i];
        delete []jogo;

        //criamos o novo jogo do mesmo tamanho que jogoAux e copiamos o conteúdo de jogoAux para o jogo original
        jogo = new char*[getNumColunas()];        
        for(int i=0;i<getNumColunas();i++){
            jogo[i] = new char[getAltura(i)];
            for(int j = 0;j < getAltura(i); j++)
                jogo[i][j] = jogoAux[i][j];
        }
        
        //deletamos a matriz e o vetor auxiliar que criamos ja que não precisamos mais deles
        delete []AlturaAux;

        for(int i = 0;i < getNumColunas(); i++)     // deleta a matriz jogo
            delete []jogoAux[i];
        delete []jogoAux;
        
        //se após verifacar todas as posições da matriz peca e não retornou false, quer dizer q a peca pode ser adiconada
        //na posição escolhida, logo a adicionamos ao jogo

        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                if(peca[i][j] != ' ')
                    jogo[coluna+j][linha-i] = peca[i][j];
        
        
        desaloca();  //chama a função para desalocar oque pode ter ficado sobrando no no jogo

        // retornamos true, pois conseguimos adicionar a peca
        return true;
    }