#include <stdio.h>  // Biblioteca padr�o de entrada e sa�da, , como printf(), scanf(), fopen(), fclose(). 
#include <string.h> // Biblioteca de manipula��o de strind e mem�rias. Ex: strcpy() e string.
#include <stdlib.h> // Biblioteca de fun��es utilit�rias gerais, como, malloc(), exit() e system().
#include <unistd.h> // No Linux/Mac (Coloquei porque uso o Lunix no trabalho e boa parte do c�digo fiz por l�)
#include <conio.h> // Biblioteca para  intera��o com o usu�rio atrav�s do console, como captura de caracteres sem necessidade de press�o "Enter"
#include <windows.h> // Biblioteca que aceita alguns codigos desse sistema operacional
#define CLEAN_BUFF do{ int c; while((c = getchar()) != '\n' && c != EOF);}while(0) // macro chamada CLEAN_BUFF, que � um mecanismo comum em C para limpar o "buffer" de entrada (ou seja, o que fica armazenado na mem�ria tempor�ria quando o programa l� dados do teclado).
#include <locale.h> // Biblioteca que permite definir conven��es regionais de um programa, como idioma.

	//O comando typedef permite ao programador definir um novo nome para um determinado tipo.
	// Usamos duas structs para "cadastrar", uma para registrar e outra para a lista de pedido. E uma terceira para ser o cadastro do funcion�rio
	typedef struct {
	    int codigoProduto;
	    char nomeProduto[30];
	    float precoProduto;
	    int quantidadeEstoque;  
	} structProduto;

	typedef struct {
	    structProduto produto;
	    int quantidade;
	} structListaPedido;

	typedef struct {
		int idFunc;
		char nomeFunc[30];
		int CPFFunc;
		char endFunc[50];
		int telFunc;
	} structFuncionario;
	

	void infoProduto(structProduto prod); // Fun��o que eont�m e retorna as informa��es do Produto
	void menu(); // Fun��o Menu com as op��es do sistema
	void cadastrarProduto(); // Fun��o que permite cadastrar o produto
	void listarProdutos(); // Fun��o que retorna os produtos cadastrados
	void comprarProduto(); // Fun��o que compra os produtos cadastrados
	void visualizarListaPedido(); // Fun��o que visualiza os produtos da compra
	void fecharPedido(); // fun��o que finaliza o pedido da compra e retorna o valor total dos pedidos
	void listarFuncionarios(); // Fun��o que retorna a lista dos funcion�rios cadastrados
	void cadastrarFuncionario(); // Fun��o que cadastra os funcion�rios
	void sistemaLoginCase(); // Fun��o que serve como o menu inicial, contendo o login, cadastro do usu�rio e a op��o sair.
	void mostrarRegistros(); // Fun��o que retorna o registro do login dos usu�rios registrados em um arquivo
	void exibirLinha(); // Fun��o criada no intuito de separar blocos e estilizar o layout
	
	structProduto pegarProdutoPorCodigo(int codigoProduto); // Fun��o do tipo structProduto
	int * temNoPedido(int codigoProduto); // Pronto, Verificar se o produto j� consta na lista
	
	static int contador_produto = 0; // Declara��o dos contadores que ser�o usados na l�gica do c�digo e para percorrer os vetores.
	static int contador_lista = 0;
	static int contador_Funcionario = 0;
	static structFuncionario funcionarios[15];
	static structListaPedido listaPedido[50];
	static structProduto produtos[50];
	// Armazena at� 50|15 itens no vetor. Cada elemento � um objeto da estrutura struct[continua��o], que cont�m um grupo de "variaveis", estamos utilizando como um array.
	// ou seja, array do tipo struct


	int main()
	{ // Abrinto o m�todo principal
		
		setlocale(LC_ALL, "");//c�digo para funcionar os acentos
	
		// Cadastrando produtos manualmente com nome, pre�o e quantidade
	    strcpy(produtos[contador_produto].nomeProduto, "Banana");
	    produtos[contador_produto].precoProduto = 3.50;
	    produtos[contador_produto].quantidadeEstoque = 100;
	    produtos[contador_produto].codigoProduto = ++contador_produto;
	
	    strcpy(produtos[contador_produto].nomeProduto, "Ma�a");
	    produtos[contador_produto].precoProduto = 4.00;
	    produtos[contador_produto].quantidadeEstoque = 80;
	    produtos[contador_produto].codigoProduto = ++contador_produto;
	
	    strcpy(produtos[contador_produto].nomeProduto, "Laranja");
	    produtos[contador_produto].precoProduto = 2.75;
	    produtos[contador_produto].quantidadeEstoque = 120;
	    produtos[contador_produto].codigoProduto = ++contador_produto;
	
	    strcpy(produtos[contador_produto].nomeProduto, "Abacaxi");
	    produtos[contador_produto].precoProduto = 6.00;
	    produtos[contador_produto].quantidadeEstoque = 60;
	    produtos[contador_produto].codigoProduto = ++contador_produto;
	
	    strcpy(produtos[contador_produto].nomeProduto, "Morango");
	    produtos[contador_produto].precoProduto = 8.50;
	    produtos[contador_produto].quantidadeEstoque = 50;
	    produtos[contador_produto].codigoProduto = ++contador_produto;
	
	    strcpy(produtos[contador_produto].nomeProduto, "Manga");
	    produtos[contador_produto].precoProduto = 5.25;
	    produtos[contador_produto].quantidadeEstoque = 90;
	    produtos[contador_produto].codigoProduto = ++contador_produto;
	
	    strcpy(produtos[contador_produto].nomeProduto, "Uva");
	    produtos[contador_produto].precoProduto = 7.00;
	    produtos[contador_produto].quantidadeEstoque = 75;
	    produtos[contador_produto].codigoProduto = ++contador_produto;
	
	    strcpy(produtos[contador_produto].nomeProduto, "Kiwi");
	    produtos[contador_produto].precoProduto = 9.00;
	    produtos[contador_produto].quantidadeEstoque = 40;
	    produtos[contador_produto].codigoProduto = ++contador_produto;
		// Retorna a fun��o sistemaLoginCase
			sistemaLoginCase();
	
			//menu();
	    return 0;
	}

	void exibirLinha(){ // Criada para servir como "separador" das a��es
	
		printf(" ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ \n");
		printf("|______|______|______|______|______|______|______|______|______|______|______|\n\n");
	}

	void infoProduto(structProduto prod){
		//Abrindo fun��o das informa��es do produto
		//Basicamente a fun��o serve para retornar os valores, sendo guardado no prod do tipo structProduto
	    printf("C�digo: %d \nNome: %s \nPre�o: %.2f \nQuantidade em estoque: %d\n", 
	    prod.codigoProduto, strtok(prod.nomeProduto, "\n"), prod.precoProduto, prod.quantidadeEstoque);
	}
	
	void menu(){	
	//Abrindo a fun��o menu
		printf("\n");
	    printf(" ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ \n");
	    printf("|______|______|______|______|______|______|______|______|______|______|______|\n\n");
	    printf(" _    _  ____  _____ _______ _____ ______ _____  _    _ _______ _____ \n");
	    printf("| |  | |/ __ \\|  __ \\__   __|_   _|  ____|  __ \\| |  | |__   __|_   _|\n");
	    printf("| |__| | |  | | |__) | | |    | | | |__  | |__) | |  | |  | |    | |  \n");
	    printf("|  __  | |  | |  _  /  | |    | | |  __| |  _  /| |  | |  | |    | |  \n");
	    printf("| |  | | |__| | | \\ \\  | |   _| |_| |    | | \\ \\| |__| |  | |   _| |_ \n");
	    printf("|_|  |_|\\____/|_|  \\_\\ |_|  |_____|_|    |_|  \\_\\\\____/   |_|  |_____|\n\n");
	    printf(" ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ \n");
	    printf("|______|______|______|______|______|______|______|______|______|______|______|\n\n");
		printf("                    Escolha e digite o número das operações abaixo: \n\n");
			printf("| 1 | - Cadastrar Produto\n");
			printf("| 2 | - Listar Produtos\n");
			printf("| 3 | - Comprar Produto\n");
			printf("| 4 | - Visualizar Lista Pedido\n");
			printf("| 5 | - Fechar pedido\n");
			printf("| 6 | - Cadastrar Funcion�rio\n");
			printf("| 7 | - Visualizar dados Funcionarios\n");
			printf("| 8 | - Mostrar Registros de Usuarios\n"); // Nova op��o para visualizar registros
	        printf("| 9 | - Sair do sistema\n\n");
			
	
	    int opcao;
	    scanf("%d", &opcao);
	    getchar(); 	// getchar para evitar o bug de pular linha pela string
	
	    switch (opcao) {
	        case 1:
	            cadastrarProduto(); // chama a fun��o dos cadastro dos produtos
	            break;
	        case 2:
	            listarProdutos(); // chama a fun��o que lista os produtos cadastrados
	            break;
	        case 3:
	            comprarProduto(); // Chama a fu��o de comprar produto
	            break;
	        case 4:
	            visualizarListaPedido(); // Chama a fun��o para visualizar o pedido da compra
	            break;
	        case 5:
	            fecharPedido(); // Chama fun��o para concluir o pedido da compra
	            break;
	  	    case 6:
				cadastrarFuncionario(); // chamada fun��o para cadastrar os funcion�rios
				break;
			case 7:
				listarFuncionarios(); // Chama fun��o para lisar os funcion�rios
				break;
			case 8:
	                mostrarRegistros();  // Chama a fun��o para exibir registros de usu�rios
	                break;
	            case 9:
	                printf("Obrigado, volte sempre!\n");
	                sleep(2);
	                exit(0);
			default: 
				printf("Op��o inv�lida \n");
				sleep(2); //Pausar o c�digo por dois segundos
				menu(); // Retorna o menu caso for digitado um nmr errado
				break;
			}
	    } // Fechando a fun��o Menu
	
	void mostrarRegistros() {
		// Fun��o que abre o arquivo contendo as informa��es de login
		exibirLinha();
	    FILE *fpIN = fopen("usuarios.txt", "r");  // Abre o arquivo em modo de leitura
	    
	    if (fpIN == NULL) { // Se for nulo, o arquivo n�o foi encontrado
	        printf("Nao foi possivel abrir o arquivo.\n");
	    } 
		else { // Se for diferente de nulo, tem arquivo, ent�o fa�a:
	        char login[50];
	        char senha[6];
			printf("               ========== Usu�rios Registrados ===========\n\n");
	
	        // Loop para ler e exibir todos os registros
	        while (fscanf(fpIN, "%s %s", login, senha) != EOF) {
	            printf("Usuario: %s | Senha: %s\n", login, senha); // Exibe o conte�do do arquivo
	        }
	        fclose(fpIN);  // Fecha o arquivo ap�s a leitura
	    }
	    sleep(5); // Atraso de 5 segundos
	    menu(); // Abrindo a fun��o menu ap�s concluir a a��o 
	} // Fechando a fun��o mostrar registros


	
	void cadastrarProduto(){
		// Abrindo a fun��o de cadastra os produtos
		exibirLinha(); // Exibe linha separadora -> Layout
	
	    printf("Cadastro de Produto\n\n");
	
	    printf("Informe o nome do produto: ");
	    fgets(produtos[contador_produto].nomeProduto, 30, stdin);
	    // produtos � o nosso array, vinculado ao structProdutos, portanto, conseguimos chamar os campos presente. 
	
	    printf("Informe o pre�o do produto: ");
	    scanf("%f", &produtos[contador_produto].precoProduto);
		// Vamos cadastrar o nome, declaramos o tamanho e por fim, declaramos a entrada padr�o
		
	    printf("Informe a quantidade em estoque do produto: ");
	    scanf("%d", &produtos[contador_produto].quantidadeEstoque);
	
	    produtos[contador_produto].codigoProduto = (contador_produto + 1);
	    ////A fun��o strtok devolve um ponteiro para a pr�xima palavra na string
	    printf("O produto %s foi cadastrado com sucesso.\n\n", strtok(produtos[contador_produto].nomeProduto, "\n"));
	    contador_produto++;
		
	
	    sleep(4); // Atraso de 4 segundos
	    menu(); // Fun��o para retornar ao menu
	} // Fechando a fun��o

	
	void listarProdutos(){
		// Abrindo a fun��o que lista os produtos cadastrados
		exibirLinha(); //Linha separador
		//Condi��o para verificar a existencia do produto;
		// Se o produto for maior (>) que 0, ele existe. Isso � poss�vel pois na fun��o cadastrarProduto, 
		//colocamos que o dado cadastrado no �ndice 0 do array apresenta o codigo valendo 1. 
		//Logo, contador_Produto > 0 significa que existe. 
	    if(contador_produto > 0)
		{
	        printf("                    Lista de produtos.\n");
			printf("____________________________________________________________________________ \n\n");
	        
	        for(int i = 0; i < contador_produto; i++) //For para rodar o vetor inteiro
			{
			// Chamamos a fun��o infoProduto (exibe as informa��es do produto) e chamados o array Produtos, para podermos chamar o i na posi��o 
	            infoProduto(produtos[i]);
	            // infoProduto(produtos[i]); chama a fun��o infoProduto para exibir as informa��es do produto na posi��o i do array produtos
				printf("____________________________________________________________________________ \n\n");
	            sleep(1);
	        }
	        sleep(2); // Atraso de 2 segundos
	        menu(); // Depois de cadastrar, retorna pro menu
	    }else{
	        printf("N�o temos ainda produtos cadastrados.\n");
	        sleep(2);
	        menu(); // Retorna para a fun��o menu, caso n�o tenha produto
	    }
	} // Fechando a fun��o listarProduto.

	void comprarProduto(){	
	// Abrindo a fun��o para comprar produto
	exibirLinha(); //Linha separador
		// Verificando a existencia do Produto no Array produtos
	    if(contador_produto > 0){
	    	
	        printf("               ========== Produtos Dispon�veis ===========\n");
	        
	        for(int i = 0; i < contador_produto; i++){
	        	// Colocamos para exibir os produtos para que a funcion�ria que for cadastrar, relembre qual �. 
	            infoProduto(produtos[i]);
	            printf("____________________________________________________________________________\n\n");
	            sleep(1);
	        }
		    printf("\nInforme o c�digo do produto que deseja adicionar a lista: ");

	        int codigoProduto;
	        scanf("%d", &codigoProduto);
	        getchar(); //Para n�o dar bugs quando recebemos um inteiro e dps uma strng
	
			// Validar se o identificador � valido
			// Essa variav�l foi criado no intuito de verificar se o identificador do produto existe.
	        int tem_mercado = 0;
	        for(int i = 0; i < contador_produto; i++){
	            if(produtos[i].codigoProduto == codigoProduto){ //// Se o mesmo identificador da nossa struct for igual ao identificador recebido pelo teclado, fa�a: 
	                tem_mercado = 1;// Logo, tem um produto.
	
	                int quantidadeDesejada;
	                printf("Informe a quantidade desejada: ");
	                scanf("%d", &quantidadeDesejada); // Obtendo o valor recebido pelo teclado
	
	                if (quantidadeDesejada > produtos[i].quantidadeEstoque) {
	                    printf("Quantidade insuficiente em estoque. Dispon�vel: %d\n", produtos[i].quantidadeEstoque);
	                } else {
	                    produtos[i].quantidadeEstoque -= quantidadeDesejada;
			
	                    if(contador_lista > 0){// Verificando se o produto que foi encontrado j� est� na lista do pedido, por isso retornamos a fun��o temNaListaPedido
	                        int *retorno = temNoPedido(codigoProduto);
	
	                        if(retorno[0] == 1){ // O array listaPedido[i].quantidade. O retorno[1] retorna o �ndice da listaPedido. Isso foi definidido na fun��o temNaListaPedido. 
												// Como j� tinha na lista do pedido, aumenta a quantidade do produto que foi colocado
	                            listaPedido[retorno[1]].quantidade += quantidadeDesejada;
	                            printf("A quantidade do produto %s foi atualizada para %d no carrinho.\n",
	                                    strtok(listaPedido[retorno[1]].produto.nomeProduto, "\n"),
	                                    listaPedido[retorno[1]].quantidade);
	                        } else {
	                            structProduto p = pegarProdutoPorCodigo(codigoProduto);
	                            listaPedido[contador_lista].produto = p;
	                            listaPedido[contador_lista].quantidade = quantidadeDesejada;
	                            contador_lista++;
	                            printf("O produto %s foi adicionado ao carrinho com a quantidade de %d.\n", 
	                                    strtok(p.nomeProduto, "\n"), quantidadeDesejada);
	                        }
	                    } else { // Caso n�o exista, ser� a primeira vez dele na lista, ent�o fazemos a inser��o dele
	                        structProduto p = pegarProdutoPorCodigo(codigoProduto);
	                        listaPedido[contador_lista].produto = p;
	                        listaPedido[contador_lista].quantidade = quantidadeDesejada;
	                        contador_lista++;
	                        printf("O produto %s foi adicionado ao carrinho com a quantidade de %d.\n", 
	                                strtok(p.nomeProduto, "\n"), quantidadeDesejada);
	                    }
	                }
	            }
	        }
	
	        if(tem_mercado < 1){ // S� tera o produto se for = > que 1, ou seja, se for menor, significa que n�o tem
	            printf("N�o foi encontrado o produto com c�digo %d.\n", codigoProduto);
	        }
	
	        printf("\nDeseja continuar comprando?\n\n | 1 | Continuar comprando. \n | 0 | Voltar ao menu. \n\n"); // Op��es de continuar ou n�o a cadastrar
	        int continuarComprando;
	        scanf("%d", &continuarComprando); // Resposta do teclado
	        getchar();
	
	        if (continuarComprando == 1) {
	            comprarProduto(); // Chama a fun��o novamente para permitir outra compra
	        } else {
	            menu(); // Volta ao menu principal
	        }
	    } else {
	        printf("Ainda n�o existem produtos para vender.\n");
	        sleep(4); // Atraso de 4 segundos
	        menu(); // Retornando para fun��o menu
	    }
	} // Fechando a fun��o de cadastrar

	
	void visualizarListaPedido(){
		// Abrindo a fun��o de visualizar o pedido
		exibirLinha(); //Linha separador
	
	    if(contador_lista > 0){ // SE for maior que 0, tem, ent�o fa�a
	    	printf("               ========== Listagem da Compra ===========\n");
	
	        printf("____________________________________________________________________________\n\n");
	        
	        for(int i = 0; i < contador_lista; i++){
	        	
	        	//Chamamos a fun��o de exibir o produto, pegamos o array listaPedido e definimos que 
				//queremos o produto (o qual � uma variavel da structListaProduto, e que armazena todas as informa��es da struct)
	
	            infoProduto(listaPedido[i].produto); 
				// Acessando a fun��o de informa��es, em especifico a listaPedido(que � uma referencia para a structListaPedido), 
				//no �ndice i, retornando a "classe filho"=>produto que pega toda a structProduto
	            printf("Quantidade no carrinho: %d\n", listaPedido[i].quantidade); // Depois de exibir as informa��es, chamamos o array listaPedido para exibir a quantidade. 
	
	            printf("____________________________________________________________________________\n\n");
	            sleep(2); // Atraso de dois segundos
	        }
	        sleep(3);
	        menu();
	    }else{
	        printf("N�o temos ainda produtos no carrinho.\n");
	        sleep(4); // Atraso de 4 segundos
	        menu(); // Retorna para o menu
	    }
	} // Fechando a fun��o de visualizar Pedido

	structProduto pegarProdutoPorCodigo(int codigoProduto){
	// Abrindo a fun��o que puxa o produto atrav�s do codigo (como se fosse uma chave prim�ria)
	exibirLinha(); //Linha separador
    structProduto p;
    
    // Condi��o para confirmar se h� alguma produto com o mesmo identificador, pq se tiver, ele est� presente, e retornamos a variavel P com o dado presente no i (indice)
    for(int i = 0; i < contador_produto; i++){
    	// Se no array produtos, na posi��o i => codigoProduto for igual a ele mesmo, fa�a:
        if(produtos[i].codigoProduto == codigoProduto){
            p = produtos[i];
        }
    }
    return p;
} // Fechando a fun��o
	
	int * temNoPedido(int codigoProduto){
		// Abrindo fun��o
	    static int retorno[] = {0, 0};
	    for(int i = 0; i < contador_lista; i++){
	        if(listaPedido[i].produto.codigoProduto == codigoProduto){
	            retorno[0] = 1; //tem o produto com este c�digo no carrinho
	            retorno[1] = i; //o �ndice do produto no carrinho
	        }
	    }
	    return retorno;
	}
	
	void fecharPedido(){ 
	//Abrindo fun��o fechar pedido
	exibirLinha(); //Linha separador
	
	    if(contador_lista > 0){ // Se for maior que 0, significa que tem, ent�o fa�a:
	        float valorTotal = 0.0;
		    printf("               ========== Concluir Pedido ===========\n");
	        printf("____________________________________________________________________________\n\n");
	        for(int i = 0; i < contador_lista; i++){ // Loop para percorrer
	        
	            structProduto p = listaPedido[i].produto; // p retorna o produto da structListaProduto, que cont�m a structProduto inteira. 
	            int quantidade = listaPedido[i].quantidade;
	            // Valor total vai ser igual o preco unit�rio do produto vezes a quantidade. 
	            valorTotal += p.precoProduto * quantidade;
	            
	            infoProduto(p); // Retorna as informa��es do produto
	            printf("Quantidade no carrinho: %d\n", quantidade);
	            printf("____________________________________________________________________________\n\n");
	            sleep(2); // Atraso de dois segundos
	        }
	        printf("Sua fatura � R$ %.2f\n", valorTotal); // Retornando o valor total
	
	        //limpar carrinho
	        contador_lista = 0;
	        printf("Obrigado pela prefer�ncia.\n");
	        sleep(4); // Atraso de 4 segundos
	        menu(); // Retorna para o menu
	    }else{
	        printf("Voc� n�o tem nenhum produto no carrinho ainda.\n");
	        sleep(3); // Atraso de 3 segundos
	        menu(); // Retorna para o menu
	    }
	} // Fechando a fun��o fecharPedido.

	void cadastrarFuncionario(){
		//Abrindo a fun��o que cadastro o funcion�rio
		exibirLinha(); //Linha separador
	
	    printf("               ========== Cadastro do Funcion�rio ===========\n\n");
		
		printf("Informe o nome do funcion�rio: ");
		// produtos � o nosso array, vinculado ao structProdutos, portanto, conseguimos chamar os campos presente. 
		fgets(funcionarios[contador_Funcionario].nomeFunc, 30, stdin); 
		
		printf("Informe o endere�o do funcion�rio: ");
		fgets(funcionarios[contador_Funcionario].endFunc, 50, stdin);
		
		printf("Informe o CPF do funcion�rio: ");
		scanf("%f", &funcionarios[contador_Funcionario].CPFFunc);
		
		printf("Informe o Telefone do funcion�rio: ");
		scanf("%f", &funcionarios[contador_Funcionario].telFunc);
		
		//A fun��o strtok devolve um ponteiro para a pr�xima palavra na string
		
		printf("____________________________________________________________________________\n\n");

		printf("Funcion�rio(a) %s cadastrado com sucesso. \n\n", strtok(funcionarios[contador_Funcionario].nomeFunc, "\n\n"));
		
		// Vamos incrementar o codigo do produto 0 para 1, para o cdg n�o come�ar no 0
		funcionarios[contador_Funcionario].idFunc = (contador_Funcionario + 1);
		contador_Funcionario++;

		sleep(5);
		menu();
	} // Fechando a fun��o cadastrarFuncionario
	
	
	void dadosFuncionario(structFuncionario func){
	// Fun��o que retorna as informa��es do funcion�rio
	printf("C�digo: %d \nNome: %s \nCPF: %d \nEndereco: %s \nTelefone: %d\n", func.idFunc, strtok(func.nomeFunc, "\n"),  func.CPFFunc, strtok(func.endFunc, "\n"), func.telFunc);

	}
	
	void listarFuncionarios(){
		exibirLinha(); //Linha separador

		//Condi��o para verificar a existencia do produto;
		// Se o produto for maior (>) que 0, ele existe. Isso � poss�vel pois na fun��o cadastrarProduto, colocamos que o dado cadastrado no �ndice 0 do array apresenta o codigo valendo 1. Logo, contador_Produto > 0 significa que existe. 

		if(contador_Funcionario > 0){
	    printf("               ========== Listagem dos Funcion�rios ===========\n\n");
		printf("____________________________________________________________________________\n\n");
			
			for(int i = 0; i < contador_Funcionario; i++)
			{
				// Chamamos a fun��o infoProduto (exibe as informa��es do produto) e chamados o array Produtos, para podermos chamar o i na posi��o 
				dadosFuncionario(funcionarios[i]);
				// infoProduto(produtos[i]); chama a fun��o infoProduto para exibir as informa��es do produto na posi��o i do array produtos
				printf("____________________________________________________________________________\n\n");
				sleep(1);
			}
		 sleep(4);
		menu();
		
		}
		else{
			printf("\nN�o temos ainda funcionarios cadastrados. \n");
			sleep(4);
			menu();
		}
	} // Fechando a fun��o listarProduto.
	
		
	int Usuario( FILE* file, char* user, char* senha ){ 
		// Abrindo a fun��o referente � colocar o usuario no arquivo
		//valida usuario, al�m disso, ta pegando o user e a senha de dentro do arquivo
		char vetorLogin[50]; // Criando a vari�vel de login, com o tamanho m�ximo de 51 caracteres
		char vetorSenha[6]; // Criando a vari�vel de senha, com o tamanho m�ximo de 7 caracteres
		fscanf(file, "%s", vetorLogin); // L� o primeiro login do arquivo
	
		//  Loop paara percorrer o arquivo at� o final, basicamente enquanto todos os 
		//  caracteres do arquivo forem diferentes do �ltimo caracter (denominado EOF) 
		//  da �ltima linha, fa�a o que a condi��o mandar:
		while( !feof(file) )
		{
			if( !strcmp(vetorLogin, user)) //strcmp = comparar strings. A string lida pelo teclado (dada pelo usu�rio = tpmLogin)
			                            // e o valor do teclado, fazendo uam valida��o se ambos sao iguais.
			{
				fscanf(file, "%s", vetorSenha); // Se o valor do login for igual, ele vai ler a senha que corresponnde.
	
				if( !strcmp(vetorSenha, senha)) // Mesma l�gica, compara a senha do teclado com a do arquivo.
					return 1;                 // Se login e senha conferem, retorna 1
			}
			else
			{
				fscanf(file, "%*s"); // Vai pulando a senha cado o login n�o bata, vai descendo as linhas do arquivo
			}
	
			fscanf(file, "%s", vetorLogin); // Vai lendo as proximas linhas
		}
	
		return 0; // Se realmente o usu�rio n�o existir no arquivo, tanto por ser erro de digita��o, ou n�o ter sido cadastrado
	}
	
	char* CriaSenha(){
		// Abrindo a fun��o 
		// Fun��o para criar uma senha com caracteres mascarados => *************
	    register int i;
	
		char* senha = (char*)malloc(sizeof *senha * 6); // Aloca mem�ria para a senha
	
	    // Loop para capturar a senha at� atingir o limite ou o usu�rio pressionar Enter
	    for(i = 0; i < 6; i++)
		{
	        senha[i] = getch(); // Captura um caractere sem precisar pressionar Enter
	        if(senha[i] == '\r') // '\r' indica Enter
	            break;
	        else
	            printf("*"); // Exibe '*' para ocultar o caractere digitado
	    }
		senha[i] = '\0'; // Finaliza a string senha com o caractere nulo
	
		return senha;  // Retorna a senha
	}
	
	void sistemaLoginCase(){
		// Abrindo fun��o que cont�m o menu do login
		// Ponteiro para o arquivo
		FILE* fpIN;
	
		int option = 0;  // Op��o do menu
	
		char *user  = (char*)malloc(sizeof *user * 50);  // Aloca mem�ria para o usu�rio atrav�s do ponteiro
		char *senha,
			 *confirmaSenha;
		
		
		printf("\n");
	    printf(" ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ \n");
	    printf("|______|______|______|______|______|______|______|______|______|______|______|\n\n");
	    printf(" _    _  ____  _____ _______ _____ ______ _____  _    _ _______ _____ \n");
	    printf("| |  | |/ __ \\|  __ \\__   __|_   _|  ____|  __ \\| |  | |__   __|_   _|\n");
	    printf("| |__| | |  | | |__) | | |    | | | |__  | |__) | |  | |  | |    | |  \n");
	    printf("|  __  | |  | |  _  /  | |    | | |  __| |  _  /| |  | |  | |    | |  \n");
	    printf("| |  | | |__| | | \\ \\  | |   _| |_| |    | | \\ \\| |__| |  | |   _| |_ \n");
	    printf("|_|  |_|\\____/|_|  \\_\\ |_|  |_____|_|    |_|  \\_\\\\____/   |_|  |_____|\n\n");
	    printf(" ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ \n");
	    printf("|______|______|______|______|______|______|______|______|______|______|______|\n\n");
		
		printf("                        Ol�, seja bem vinda(o)!\n");
		printf("                     Escolhe uma das op��es abaixo:\n\n");
		do
		{
			        // Exibe o menu de op��es
			printf("| 1 | - Login\n| 2 | - Cadastrar\n| 3 | - Sair\n\n");
			scanf("%d", &option);  // L� a op��o do usu�rio
			CLEAN_BUFF; // Limpa o buffer de entrada
	
	
			switch( option )
			{
				case 1: // Login de usu�rio
	
					printf("Usu�rio: ");
					gets(user); // L� o nome do usu�rio
					printf("Senha: ");
					senha = CriaSenha(); // Chama a fun��o para capturar a senha
	
					fpIN = fopen("usuarios.txt", "a+");  // Abre o arquivo de usu�rios em modo leitura e escrita
				   
				    // Verifica se o usu�rio est� registrado
					// O arquivo, pega o user, pega senha
					if(Usuario(fpIN, user, senha))
					{
					
	                    printf("\nUsuario registrado.");
	                    menu();
	                }
	                else
	                    printf("\nUsuario nao registrado\n");
	
					fclose(fpIN); // Fecha o arquivo
					free(senha); // Libera a mem�ria da senha
	                
	                sistemaLoginCase();
	
				// Cadastro de novo usu�rio
				case 2:
					printf("Usuario: ");
					gets(user); // L� o nome do usu�rio
	
	                // Loop para confirmar a senha
	
					do
					{
						printf("Senha: "); 
						senha = CriaSenha(); // L� a senha, conforme a fun��o
						printf("\nConfirmacao de senha: ");
						confirmaSenha = CriaSenha(); // L� a confirma��o da senha, conforme a fun��o
						printf("\n");
	
						if( !strcmp(senha, confirmaSenha) ) // Compara as senhas
							break; // se for igual, sai do do while
						else
							printf("As senhas n�o s�o iguais. Tente novamente.\n");
					}while(1);
					
				  // Abre o arquivo para adicionar o novo usu�rio e senha
	
					fpIN = fopen("usuarios.txt", "a+"); 
					// Salva o usu�rio e a senha no arquivo
					fprintf(fpIN, "%s %s\n", user, senha);
					fclose(fpIN); // Fecha o arquivo
	
					free(senha);
					free(confirmaSenha);
					
					sistemaLoginCase();
				break;
	
				case 3:  // Mostrar registros no arquivo
	                printf("\nObrigado, volte sempre!\n");
	                sleep(2);
	                exit(0);
	       	}
		}while( 1 );
	
	}

