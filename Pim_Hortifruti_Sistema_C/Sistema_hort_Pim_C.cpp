#include <stdio.h>  // Biblioteca padrão de entrada e saída, , como printf(), scanf(), fopen(), fclose(). 
#include <string.h> // Biblioteca de manipulação de strind e memórias. Ex: strcpy() e string.
#include <stdlib.h> // Biblioteca de funções utilitárias gerais, como, malloc(), exit() e system().
#include <unistd.h> // No Linux/Mac (Coloquei porque uso o Lunix no trabalho e boa parte do código fiz por lá)
#include <conio.h> // Biblioteca para  interação com o usuário através do console, como captura de caracteres sem necessidade de pressão "Enter"
#include <stdbool.h> // Biblioteca para operadores lógicos
#include <windows.h> // Biblioteca que aceita alguns codigos desse sistema operacional
#define CLEAN_BUFF do{ int c; while((c = getchar()) != '\n' && c != EOF);}while(0) // macro chamada CLEAN_BUFF, que é um mecanismo comum em C para limpar o "buffer" de entrada (ou seja, o que fica armazenado na memória temporária quando o programa lê dados do teclado).
#include <locale.h> // Biblioteca que permite definir convenções regionais de um programa, como idioma.

	//O comando typedef permite ao programador definir um novo nome para um determinado tipo.
	// Usamos duas structs para "cadastrar", uma para registrar e outra para a lista de pedido. E uma terceira para ser o cadastro do funcionário
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
	
	typedef struct {
		int idCliente;
		char nomeCliente[30];
		char CPFCliente[11];
	} structCliente;

	void infoProduto(structProduto prod); // Função que eontém e retorna as informações do Produto
	void menu(); // Função Menu com as opções do sistema
	void cadastrarProduto(); // Função que permite cadastrar o produto
	void listarProdutos(); // Função que retorna os produtos cadastrados
	void comprarProduto(); // Função que compra os produtos cadastrados
	void visualizarListaPedido(); // Função que visualiza os produtos da compra
	void fecharPedido(); // função que finaliza o pedido da compra e retorna o valor total dos pedidos
	void listarFuncionarios(); // Função que retorna a lista dos funcionários cadastrados
	void cadastrarFuncionario(); // Função que cadastra os funcionários
	void sistemaLoginCase(); // Função que serve como o menu inicial, contendo o login, cadastro do usuário e a opção sair.
	void mostrarRegistros(); // Função que retorna o registro do login dos usuários registrados em um arquivo
	void exibirLinha(); // Função criada no intuito de separar blocos e estilizar o layout
	void cadastrarCliente(); // Função criada para cadastrar os clientes fidelidade
	void limpaConsole(); // Função para limpar o console, removendo qualquer conteúdo exibido anteriormente e deixar uma tela limpa para novas informações.
	bool verificarFidelidade(char* cpf);
	
	structProduto pegarProdutoPorCodigo(int codigoProduto); // Função do tipo structProduto
	int * temNoPedido(int codigoProduto); // Pronto, Verificar se o produto já consta na lista
	
	static int contador_produto = 0; // Declaração dos contadores que serão usados na lógica do código e para percorrer os vetores.
	static int contador_lista = 0;
	static int contador_Funcionario = 0;
	static int contator_cliente = 0;
	static structFuncionario funcionarios[15];
	static structListaPedido listaPedido[50];
	static structProduto produtos[50];
	static structCliente clientes[15];
	// Armazena até 50|15 itens no vetor. Cada elemento é um objeto da estrutura struct[continuação], que contém um grupo de "variaveis", estamos utilizando como um array.
	// ou seja, array do tipo struct


	int main()
	{ // Abrinto o método principal
		
		setlocale(LC_ALL, "");//código para funcionar os acentos
	
		// Cadastrando produtos manualmente com nome, preço e quantidade
	    strcpy(produtos[contador_produto].nomeProduto, "Banana");
	    produtos[contador_produto].precoProduto = 3.50;
	    produtos[contador_produto].quantidadeEstoque = 100;
	    produtos[contador_produto].codigoProduto = ++contador_produto;
	
	    strcpy(produtos[contador_produto].nomeProduto, "Maça");
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
		// Retorna a função sistemaLoginCase
			sistemaLoginCase();
	
			//menu();
	    return 0;
	}

	void exibirLinha(){ // Criada para servir como "separador" das ações
	
		printf(" ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ \n");
		printf("|______|______|______|______|______|______|______|______|______|______|______|\n\n");
	}

	void infoProduto(structProduto prod){
		//Abrindo função das informações do produto
		//Basicamente a função serve para retornar os valores, sendo guardado no prod do tipo structProduto
	    printf("Código: %d \nNome: %s \nPreço: %.2f \nQuantidade em estoque: %d\n", 
	    prod.codigoProduto, strtok(prod.nomeProduto, "\n"), prod.precoProduto, prod.quantidadeEstoque);
	}
	
	void menu(){	
	//Abrindo a função menu
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
			printf("| 2 | - Visualizar Estoque\n");
			printf("| 3 | - Comprar Produto\n");
			printf("| 4 | - Visualizar Lista Pedido\n");
			printf("| 5 | - Fechar pedido\n");
			printf("| 6 | - Cadastrar Funcionário\n");
			printf("| 7 | - Visualizar dados Funcionarios\n");
			printf("| 8 | - Mostrar Registros de Usuarios\n"); // Nova opção para visualizar registros
	        printf("| 9 | - Cadastrar Cliente\n");
			printf("| 0 | - Sair do sistema\n\n");
			
	
	    int opcao;
	    scanf("%d", &opcao);
	    getchar(); 	// getchar para evitar o bug de pular linha pela string
	
	    switch (opcao) {
	        case 1:
	        	sleep(2);
	            cadastrarProduto(); // chama a função dos cadastro dos produtos
	            break;
	        case 2:
	        	sleep(2);
	            listarProdutos(); // chama a função que lista os produtos cadastrados
	            break;
	        case 3:
	        	sleep(2);
	            comprarProduto(); // Chama a fução de comprar produto
	            break;
	        case 4:
	        	sleep(2);
	            visualizarListaPedido(); // Chama a função para visualizar o pedido da compra
	            break;
	        case 5:
	        	sleep(2);
	            fecharPedido(); // Chama função para concluir o pedido da compra
	            break;
	  	    case 6:
	  	    	sleep(2);
				cadastrarFuncionario(); // chamada função para cadastrar os funcionários
				break;
			case 7:
				sleep(2);
				listarFuncionarios(); // Chama função para lisar os funcionários
				break;
			case 8:
				sleep(2);
                mostrarRegistros();  // Chama a função para exibir registros de usuários
                break;
	        case 9:
	        	sleep(2);
	        	cadastrarCliente(); // Chama a função de cadastro de Cliente 
	        	break;
			case 0:
                printf("Obrigado, volte sempre!\n");
                sleep(2);
                exit(0);
			default: 
				printf("Opção inválida \n");
				sleep(2); //Pausar o código por dois segundos
				menu(); // Retorna o menu caso for digitado um nmr errado
				break;
			}
	    } // Fechando a função Menu
	
	void mostrarRegistros() {
		// Função que abre o arquivo contendo as informações de login
		exibirLinha();
	    FILE *fpIN = fopen("usuarios.txt", "r");  // Abre o arquivo em modo de leitura
	    
	    if (fpIN == NULL) { // Se for nulo, o arquivo não foi encontrado
	        printf("Nao foi possivel abrir o arquivo.\n");
	    } 
		else { // Se for diferente de nulo, tem arquivo, então faça:
	        char login[50];
	        char senha[6];
			printf("               ========== Usuários Registrados ===========\n\n");
	
	        // Loop para ler e exibir todos os registros
	        while (fscanf(fpIN, "%s %s", login, senha) != EOF) {
	            printf("Usuario: %s | Senha: %s\n", login, senha); // Exibe o conteúdo do arquivo
	        }
	        fclose(fpIN);  // Fecha o arquivo após a leitura
	    }
	    sleep(3); // Atraso de 3 segundos
	    menu(); // Abrindo a função menu após concluir a ação 
	} // Fechando a função mostrar registros


	
	void cadastrarProduto(){
		// Abrindo a função de cadastra os produtos
		exibirLinha(); // Exibe linha separadora -> Layout
	
	    printf("Cadastro de Produto\n\n");
	
	    printf("Informe o nome do produto: ");
	    fgets(produtos[contador_produto].nomeProduto, 30, stdin);
	    // produtos é o nosso array, vinculado ao structProdutos, portanto, conseguimos chamar os campos presente. 
	
	    printf("Informe o preço do produto: ");
	    scanf("%f", &produtos[contador_produto].precoProduto);
		// Vamos cadastrar o nome, declaramos o tamanho e por fim, declaramos a entrada padrão
		
	    printf("Informe a quantidade em estoque do produto: ");
	    scanf("%d", &produtos[contador_produto].quantidadeEstoque);
	
	    produtos[contador_produto].codigoProduto = (contador_produto + 1);
	    ////A função strtok devolve um ponteiro para a próxima palavra na string
	    printf("O produto %s foi cadastrado com sucesso.\n\n", strtok(produtos[contador_produto].nomeProduto, "\n"));
	    contador_produto++;
		
	
	    sleep(2); // Atraso de 2 segundos
	    menu(); // Função para retornar ao menu
	} // Fechando a função

	
	void listarProdutos(){
		// Abrindo a função que lista os produtos cadastrados
		exibirLinha(); //Linha separador
		//Condição para verificar a existencia do produto;
		// Se o produto for maior (>) que 0, ele existe. Isso é possível pois na função cadastrarProduto, 
		//colocamos que o dado cadastrado no índice 0 do array apresenta o codigo valendo 1. 
		//Logo, contador_Produto > 0 significa que existe. 
	    if(contador_produto > 0)
		{
	        printf("                    Lista de produtos.\n");
			printf("____________________________________________________________________________ \n\n");
	        
	        for(int i = 0; i < contador_produto; i++) //For para rodar o vetor inteiro
			{
			// Chamamos a função infoProduto (exibe as informações do produto) e chamados o array Produtos, para podermos chamar o i na posição 
	            infoProduto(produtos[i]);
	            // infoProduto(produtos[i]); chama a função infoProduto para exibir as informações do produto na posição i do array produtos
				printf("____________________________________________________________________________ \n\n");
	            sleep(1);
	        }
	        sleep(2); // Atraso de 2 segundos
	        menu(); // Depois de cadastrar, retorna pro menu
	    }else{
	        printf("Não temos ainda produtos cadastrados.\n");
	        sleep(2);
	        menu(); // Retorna para a função menu, caso não tenha produto
	    }
	} // Fechando a função listarProduto.

	void comprarProduto(){	
	// Abrindo a função para comprar produto
	exibirLinha(); //Linha separador
		// Verificando a existencia do Produto no Array produtos
	    if(contador_produto > 0){
	    	
	        printf("               ========== Produtos Disponíveis ===========\n");
	        
	        for(int i = 0; i < contador_produto; i++){
	        	// Colocamos para exibir os produtos para que a funcionária que for cadastrar, relembre qual é. 
	            infoProduto(produtos[i]);
	            printf("____________________________________________________________________________\n\n");
	            sleep(1);
	        }
		    printf("\nInforme o código do produto que deseja adicionar a lista: ");

	        int codigoProduto;
	        scanf("%d", &codigoProduto);
	        getchar(); //Para não dar bugs quando recebemos um inteiro e dps uma strng
	
			// Validar se o identificador é valido
			// Essa variavél foi criado no intuito de verificar se o identificador do produto existe.
	        int tem_mercado = 0;
	        for(int i = 0; i < contador_produto; i++){
	            if(produtos[i].codigoProduto == codigoProduto){ //// Se o mesmo identificador da nossa struct for igual ao identificador recebido pelo teclado, faça: 
	                tem_mercado = 1;// Logo, tem um produto.
	
	                int quantidadeDesejada;
	                printf("Informe a quantidade desejada: ");
	                scanf("%d", &quantidadeDesejada); // Obtendo o valor recebido pelo teclado
	
	                if (quantidadeDesejada > produtos[i].quantidadeEstoque) {
	                    printf("Quantidade insuficiente em estoque. Disponível: %d\n", produtos[i].quantidadeEstoque);
	                } else {
	                    produtos[i].quantidadeEstoque -= quantidadeDesejada;
			
	                    if(contador_lista > 0){// Verificando se o produto que foi encontrado já está na lista do pedido, por isso retornamos a função temNaListaPedido
	                        int *retorno = temNoPedido(codigoProduto);
	
	                        if(retorno[0] == 1){ // O array listaPedido[i].quantidade. O retorno[1] retorna o índice da listaPedido. Isso foi definidido na função temNaListaPedido. 
												// Como já tinha na lista do pedido, aumenta a quantidade do produto que foi colocado
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
	                    } else { // Caso não exista, será a primeira vez dele na lista, então fazemos a inserção dele
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
	
	        if(tem_mercado < 1){ // Só tera o produto se for = > que 1, ou seja, se for menor, significa que não tem
	            printf("Não foi encontrado o produto com código %d.\n", codigoProduto);
	        }
	
	        printf("\nDeseja continuar comprando?\n\n | 1 | Continuar comprando. \n | 0 | Voltar ao menu. \n\n"); // Opções de continuar ou não a cadastrar
	        int continuarComprando;
	        scanf("%d", &continuarComprando); // Resposta do teclado
	        getchar();
	
	        if (continuarComprando == 1) {
	            comprarProduto(); // Chama a função novamente para permitir outra compra
	        } else {
	            menu(); // Volta ao menu principal
	        }
	    } else {
	        printf("Ainda não existem produtos para vender.\n");
	        sleep(2); // Atraso de 2 segundos
	        menu(); // Retornando para função menu
	    }
	} // Fechando a função de cadastrar

	
	void visualizarListaPedido(){
		// Abrindo a função de visualizar o pedido
		exibirLinha(); //Linha separador
	
	    if(contador_lista > 0){ // SE for maior que 0, tem, então faça
	    	printf("               ========== Listagem da Compra ===========\n");
	
	        printf("____________________________________________________________________________\n\n");
	        
	        for(int i = 0; i < contador_lista; i++){
	        	
	        	//Chamamos a função de exibir o produto, pegamos o array listaPedido e definimos que 
				//queremos o produto (o qual é uma variavel da structListaProduto, e que armazena todas as informações da struct)
	
	            infoProduto(listaPedido[i].produto); 
				// Acessando a função de informações, em especifico a listaPedido(que é uma referencia para a structListaPedido), 
				//no índice i, retornando a "classe filho"=>produto que pega toda a structProduto
	            printf("Quantidade no carrinho: %d\n", listaPedido[i].quantidade); // Depois de exibir as informações, chamamos o array listaPedido para exibir a quantidade. 
	
	            printf("____________________________________________________________________________\n\n");
	            sleep(2); // Atraso de 2 segundos
	        }
	        sleep(2);
	        menu();
	    }else{
	        printf("Não temos ainda produtos no carrinho.\n");
	        sleep(2); // Atraso de 2 segundos
	        menu(); // Retorna para o menu
	    }
	} // Fechando a função de visualizar Pedido

	structProduto pegarProdutoPorCodigo(int codigoProduto){
	// Abrindo a função que puxa o produto através do codigo (como se fosse uma chave primária)
	exibirLinha(); //Linha separador
    structProduto p;
    
    // Condição para confirmar se há alguma produto com o mesmo identificador, pq se tiver, ele está presente, e retornamos a variavel P com o dado presente no i (indice)
    for(int i = 0; i < contador_produto; i++){
    	// Se no array produtos, na posição i => codigoProduto for igual a ele mesmo, faça:
        if(produtos[i].codigoProduto == codigoProduto){
            p = produtos[i];
        }
    }
    return p;
} // Fechando a função
	
	int * temNoPedido(int codigoProduto){
		// Abrindo função
	    static int retorno[] = {0, 0};
	    for(int i = 0; i < contador_lista; i++){
	        if(listaPedido[i].produto.codigoProduto == codigoProduto){
	            retorno[0] = 1; //tem o produto com este código no carrinho
	            retorno[1] = i; //o índice do produto no carrinho
	        }
	    }
	    return retorno;
	}
	
	void fecharPedido(){ 
	//Abrindo função fechar pedido
	exibirLinha(); //Linha separador
	
	    if(contador_lista > 0){ // Se for maior que 0, significa que tem, então faça:
	        float valorTotal = 0.0;
	        bool fidelidade = false;
		    printf("               ========== Concluir Pedido ===========\n");
	        printf("____________________________________________________________________________\n\n");
	        for(int i = 0; i < contador_lista; i++){ // Loop para percorrer
	        
	            structProduto p = listaPedido[i].produto; // p retorna o produto da structListaProduto, que contém a structProduto inteira. 
	            int quantidade = listaPedido[i].quantidade; // Valor total vai ser igual o preco unitário do produto vezes a quantidade. 
	            valorTotal += p.precoProduto * quantidade; // Calcula o valor total
	            
	            infoProduto(p); // Retorna as informações do produto
	            printf("Quantidade no carrinho: %d\n", quantidade);
	            printf("____________________________________________________________________________\n\n");
	            sleep(2); // Atraso de dois segundos
	        }
	        
	       printf("O cliente tem fidelidade? (1 para Sim, 0 para Não): ");
        scanf("%d", &fidelidade); // Leitura da resposta
		for(int i =0 ; i<3; i++){
	        if (fidelidade) { // Se o cliente tem fidelidade
	        	char cpf[12];
		        printf("Informe o CPF do cliente: ");
		        scanf("%s", cpf); 
	        	if(verificarFidelidade(cpf)){
		            printf("\nDesconto de fidelidade aplicado! 10%% de desconto.\n");
		            valorTotal *= 0.9; // Aplica 10% de desconto
		            break;
				}else{
					printf("CPF não encontrado\n");
					printf("Tente novamente (%d de 3)\n", i+1);
				}
	        }
		}
        
        printf("\nValor Total do Pedido: R$ %.2f\n", valorTotal);
	        //limpar carrinho
	        contador_lista = 0;
	        printf("Obrigado pela preferência.\n");
	        sleep(2); // Atraso de 2 segundos
	        menu(); // Retorna para o menu
	    }else{
	        printf("Você não tem nenhum produto no carrinho ainda.\n");
	        sleep(3); // Atraso de 3 segundos
	        menu(); // Retorna para o menu
	    }
	} // Fechando a função fecharPedido.
	
	bool verificarFidelidade(char* cpf) {
	    FILE* fpIN = fopen("clientes.txt", "r");
	    if (fpIN == NULL) {
	   	 	printf("Erro ao abrir o arquivo de clientes.\n");
	   		return false;
	    }
	
	    char cpfArquivo[12];
	    while (fscanf(fpIN, "%*d %*s %s", cpfArquivo) != EOF) { // Lê apenas o CPF no arquivo
	        if (strcmp(cpf, cpfArquivo) == 0) { // Verifica se o CPF está no arquivo
	            fclose(fpIN);
	            return true; // CPF encontrado, cliente fidelidade
	        }
	    }
	
	    fclose(fpIN);
	    return false; // CPF não encontrado
	}
	
	void cadastrarFuncionario(){
	
		//Abrindo a função que cadastro o funcionário
		exibirLinha(); //Linha separador
	
	    printf("               ========== Cadastro do Funcionário ===========\n\n");
		
		printf("Informe o nome do funcionário: ");
		// produtos é o nosso array, vinculado ao structProdutos, portanto, conseguimos chamar os campos presente. 
		fgets(funcionarios[contador_Funcionario].nomeFunc, 30, stdin); 
		
		printf("Informe o endereço do funcionário: ");
	    fgets(funcionarios[contador_Funcionario].endFunc, 50, stdin);
	    
		printf("Informe o CPF do funcionário: ");
		scanf("%f", &funcionarios[contador_Funcionario].CPFFunc);
		
		printf("Informe o Telefone do funcionário: ");
		scanf("%f", &funcionarios[contador_Funcionario].telFunc);
		
		//A função strtok devolve um ponteiro para a próxima palavra na string
		
		printf("____________________________________________________________________________\n\n");

		printf("Funcionário(a) %s cadastrado com sucesso. \n\n", strtok(funcionarios[contador_Funcionario].nomeFunc, "\n\n"));
		
		// Vamos incrementar o codigo do produto 0 para 1, para o cdg não começar no 0
		funcionarios[contador_Funcionario].idFunc = (contador_Funcionario + 1);
		contador_Funcionario++;

		sleep(3);
		menu();
	} // Fechando a função cadastrarFuncionario
	
	
	void dadosFuncionario(structFuncionario func){
	// Função que retorna as informações do funcionário
	printf("Código: %d \nNome: %s \nCPF: %d \nEndereco: %s \nTelefone: %d\n", func.idFunc, strtok(func.nomeFunc, "\n"),  func.CPFFunc, strtok(func.endFunc, "\n"), func.telFunc);

	}
	
	void listarFuncionarios(){
		exibirLinha(); //Linha separador

		//Condição para verificar a existencia do produto;
		// Se o produto for maior (>) que 0, ele existe. Isso é possível pois na função cadastrarProduto, colocamos que o dado cadastrado no índice 0 do array apresenta o codigo valendo 1. Logo, contador_Produto > 0 significa que existe. 

		if(contador_Funcionario > 0){
	    printf("               ========== Listagem dos Funcionários ===========\n\n");
		printf("____________________________________________________________________________\n\n");
			
			for(int i = 0; i < contador_Funcionario; i++)
			{
				// Chamamos a função infoProduto (exibe as informações do produto) e chamados o array Produtos, para podermos chamar o i na posição 
				dadosFuncionario(funcionarios[i]);
				// infoProduto(produtos[i]); chama a função infoProduto para exibir as informações do produto na posição i do array produtos
				printf("____________________________________________________________________________\n\n");
				sleep(1);
			}
		 sleep(2);
		menu();
		
		}
		else{
			printf("\nNão temos ainda funcionarios cadastrados. \n");
			sleep(2);
			menu();
		}
	} // Fechando a função listarProduto.
	
		
	int Usuario( FILE* file, char* user, char* senha ){ 
		// Abrindo a função referente à colocar o usuario no arquivo
		//valida usuario, além disso, ta pegando o user e a senha de dentro do arquivo
		char vetorLogin[50]; // Criando a variável de login, com o tamanho máximo de 51 caracteres
		char vetorSenha[6]; // Criando a variável de senha, com o tamanho máximo de 7 caracteres
		fscanf(file, "%s", vetorLogin); // Lê o primeiro login do arquivo
	
		//  Loop paara percorrer o arquivo até o final, basicamente enquanto todos os 
		//  caracteres do arquivo forem diferentes do último caracter (denominado EOF) 
		//  da última linha, faça o que a condição mandar:
		while( !feof(file) )
		{
			if( !strcmp(vetorLogin, user)) //strcmp = comparar strings. A string lida pelo teclado (dada pelo usuário = tpmLogin)
			                            // e o valor do teclado, fazendo uam validação se ambos sao iguais.
			{
				fscanf(file, "%s", vetorSenha); // Se o valor do login for igual, ele vai ler a senha que corresponnde.
	
				if( !strcmp(vetorSenha, senha)) // Mesma lógica, compara a senha do teclado com a do arquivo.
					return 1;                 // Se login e senha conferem, retorna 1
			}
			else
			{
				fscanf(file, "%*s"); // Vai pulando a senha cado o login não bata, vai descendo as linhas do arquivo
			}
	
			fscanf(file, "%s", vetorLogin); // Vai lendo as proximas linhas
		}
	
		return 0; // Se realmente o usuário não existir no arquivo, tanto por ser erro de digitação, ou não ter sido cadastrado
	}
	
	char* CriaSenha(){
		// Abrindo a função 
		// Função para criar uma senha com caracteres mascarados => *************
	    register int i;
	
		char* senha = (char*)malloc(sizeof *senha * 6); // Aloca memória para a senha
	
	    // Loop para capturar a senha até atingir o limite ou o usuário pressionar Enter
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
		// Abrindo função que contém o menu do login
		// Ponteiro para o arquivo
		FILE* fpIN;
	
		int option = 0;  // Opção do menu
	
		char *user  = (char*)malloc(sizeof *user * 50);  // Aloca memória para o usuário através do ponteiro
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
		
		printf("                        Olá, seja bem vinda(o)!\n");
		printf("                     Escolha e digite o número das operações abaixo:\n\n");
		do
		{
			        // Exibe o menu de opções
			printf("| 1 | - Login\n| 2 | - Cadastrar\n| 3 | - Sair\n\n");
			scanf("%d", &option);  // Lê a opção do usuário
			CLEAN_BUFF; // Limpa o buffer de entrada
	
	
			switch( option )
			{
				case 1: // Login de usuário
	
					printf("Usuário: ");
					gets(user); // Lê o nome do usuário
					printf("Senha: ");
					senha = CriaSenha(); // Chama a função para capturar a senha
	
					fpIN = fopen("usuarios.txt", "a+");  // Abre o arquivo de usuários em modo leitura e escrita
				   
				    // Verifica se o usuário está registrado
					// O arquivo, pega o user, pega senha
					if(Usuario(fpIN, user, senha))
					{
					
	                    printf("\nUsuario registrado.");
	                    menu();
	                }
	                else
	                    printf("\nUsuario nao registrado\n");
	
					fclose(fpIN); // Fecha o arquivo
					free(senha); // Libera a memória da senha
	                
	                sistemaLoginCase();
	
				// Cadastro de novo usuário
				case 2:
					printf("Usuario: ");
					gets(user); // Lê o nome do usuário
	
	                // Loop para confirmar a senha
	
					do
					{
						printf("Senha: "); 
						senha = CriaSenha(); // Lê a senha, conforme a função
						printf("\nConfirmacao de senha: ");
						confirmaSenha = CriaSenha(); // Lê a confirmação da senha, conforme a função
						printf("\n");
	
						if( !strcmp(senha, confirmaSenha) ) // Compara as senhas
							break; // se for igual, sai do do while
						else
							printf("As senhas não são iguais. Tente novamente.\n");
					}while(1);
					
				  // Abre o arquivo para adicionar o novo usuário e senha
	
					fpIN = fopen("usuarios.txt", "a+"); 
					// Salva o usuário e a senha no arquivo
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
	
	void cadastrarCliente(){
		FILE* fpIN;
		limpaConsole();
		exibirLinha(); //Linha separador
		printf("  _____          _____           _____ _______ _____   ____  \n");
	    printf(" / ____|   /\\   |  __ \\   /\\    / ____|__   __|  __ \\ / __ \\ \n");
	    printf("| |       /  \\  | |  | | /  \\  | (___    | |  | |__) | |  | |\n");
	    printf("| |      / /\\ \\ | |  | |/ /\\ \\  \\___ \\   | |  |  _  /| |  | |\n");
	    printf("| |____ / ____ \\| |__| / ____ \\ ____) |  | |  | | \\ \\| |__| |\n");
	    printf("\\_____/_/    \\_\\_____/__/    \\_\\_____/   |_|  |_|  \\_\\____/ \n\n");
	    printf("  _____ _      _____ ______ _   _ _______ ______ \n");
	    printf(" / ____| |    |_   _|  ____| \\ | |__   __|  ____|\n");
	    printf("| |    | |      | | | |__  |  \\| |  | |  | |__   \n");
	    printf("| |    | |      | | |  __| | . ` |  | |  |  __|  \n");
	    printf("| |____| |____ _| |_| |____| |\\  |  | |  | |____ \n");
	    printf(" \\_____|______|_____|______|_| \\_|  |_|  |______|\n\n");
				
		printf("Informe o nome do cliente: ");
	    fgets(clientes[contator_cliente].nomeCliente, 30, stdin); 
	
	    printf("Informe o CPF do cliente: ");
	    fgets(clientes[contator_cliente].CPFCliente, 12, stdin);

		
		//A função strtok devolve um ponteiro para a próxima palavra na string
		
		printf("____________________________________________________________________________\n\n");

		printf("Cliente %s cadastrado com sucesso. \n\n", strtok(clientes[contator_cliente].nomeCliente, "\n\n"));
		
		fpIN = fopen("clientes.txt", "a+"); 
		// Salva o usuário e a senha no arquivo
		if (fpIN != NULL) {
        // Salva o cliente no arquivo
        	fprintf(fpIN, "%d %s %s\n", clientes[contator_cliente].idCliente, 
                                        clientes[contator_cliente].nomeCliente, 
                                        clientes[contator_cliente].CPFCliente);
        	fclose(fpIN); // Fecha o arquivo
    	} else {
        	printf("Erro ao abrir o arquivo!\n");
    	}
    	// Vamos incrementar o codigo do produto 0 para 1, para o cdg não começar no 0
		clientes[contator_cliente].idCliente = (contator_cliente + 1);
		contator_cliente++;
		sleep(2);
		menu();	    
	}
	
	void limpaConsole(){
		#ifdef _WIN32
			system("cls");  
    	#else
        	system("clear"); 
    	#endif
	}

