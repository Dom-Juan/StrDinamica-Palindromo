#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Node que forma a string dinamica.
typedef struct node{
    char caractere;
    struct node *next;
}char_node;

// Descritor da lista q forma a string dinamica.
typedef struct arrayOfCharacter{
    struct node *first_char;
    struct node *last_char;
}array_char;

// Estrutura da pilha.
typedef struct Stack{
    char c;
    struct Stack *next;
}stStack;

void MostrarString(array_char *string);
void InserirNaString(array_char *string, char c);
void VerificaPalindromo(array_char *string, stStack *stackHead);

// Inicia a pilha
stStack *initStack(stStack *stackHead){
    stackHead = (stStack*)malloc(sizeof(stStack));
    stackHead->c = ' ';
    stackHead->next = NULL;

    return stackHead;
}

// Adiciona na pilha
void AdicionarNaPilha(stStack **stackHead, char c){
    stStack *newNode = (stStack*)malloc(sizeof(stStack));

    // Adicionando info.
    newNode->c = c;

    // Ligando o node ao topo.
    newNode->next = (*stackHead);
    (*stackHead) = newNode;
}

// Retira da Pilha.
char RetirarDaPilha(stStack **stackHead){
    stStack *newNode = (*stackHead);
    char ch;

    ch = newNode->c;
    (*stackHead) = (*stackHead)->next;
    free(newNode);

    return ch;
}

// Mostra a Pilha, usado para verificar se a pilha funciona.
void MostrarPilha(stStack *stackHead){
    while(stackHead->next != NULL) {
        printf("***************************************\n");
        printf("*  Info: %c                            \n",stackHead->c);
        printf("***************************************\n\n");
        stackHead = stackHead->next;
    }
}

// Verifica se a string dinamica eh palindroma.
void VerificaPalindromo(array_char *string, stStack *stackHead){
    array_char *reverseString = (array_char*)malloc(sizeof(array_char));

    char_node *auxNode1 = string->first_char;

    bool verdura = false;

    int i = 0;


    while(auxNode1 != NULL){
        //printf("\ncaractere a inserir: %c\n",auxNode1->caractere);
        AdicionarNaPilha(&stackHead,auxNode1->caractere);
        auxNode1 = auxNode1->next;
    }

    free(auxNode1);
    auxNode1 = string->first_char;

    char ch;
    printf("\nVerificando se eh palindromo. . .\n\n");
    while(auxNode1 != NULL){
        ch = RetirarDaPilha(&stackHead);
        if(auxNode1->caractere == ch){
            printf("%c == %c\n" ,auxNode1->caractere, ch);
            verdura = true;
        } else{
            printf("%c != %c\n" ,auxNode1->caractere, ch);
            verdura = false;
        }
        auxNode1 = auxNode1->next;
    }

    if(verdura == true)
        printf("\n**Eh palindromo\n");
    else
        printf("\n**Nao eh palindromo\n");
}

// Insere elementos na string dinamica.
void InserirNaString(array_char *string, char c){
    char_node *newNode = (char_node*)malloc(sizeof(char_node));

    if(string->first_char == NULL) {
        newNode->caractere = c;
        newNode->next = NULL;

        string->first_char = string->last_char = newNode;
    } else {
        newNode->caractere = c;
        newNode->next = NULL;

        string->last_char->next = newNode;
        string->last_char = newNode;
    }
}

// Usado para mostrar a string dinamica.
void MostrarString(array_char *string){
    char_node *auxNode = string->first_char;
    printf("\n");
    while(auxNode != NULL){
        printf("%c",auxNode->caractere);
        auxNode = auxNode->next;
    }
    printf("\n");
}

int main() {
    array_char *string;
    array_char *string2;
    stStack *stackHead = NULL;

    string = (array_char*)malloc(sizeof(array_char));
    string->first_char = NULL;
    string->last_char = NULL;

    string2 = (array_char*)malloc(sizeof(array_char));
    string2->first_char = NULL;
    string2->last_char = NULL;

    stackHead = initStack(stackHead);

    printf("* Verificar se a string dinamica eh palindroma *\n");

    InserirNaString(string,'a');
    InserirNaString(string,'n');
    InserirNaString(string,'a');

    InserirNaString(string2,'b');
    InserirNaString(string2,'a');
    InserirNaString(string2,'t');
    InserirNaString(string2,'a');
    InserirNaString(string2,'t');
    InserirNaString(string2,'a');

    printf("\nstring1:");
    MostrarString(string);
    printf("\nstring2:");
    MostrarString(string2);

    printf("\n");

    VerificaPalindromo(string,stackHead);
    printf("\n");
    VerificaPalindromo(string2,stackHead);

    printf("* Fim do programa*\n");
    system("pause");

    return 0;
}
