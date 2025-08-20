#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MY_SUCCESS 5




typedef enum {
    HEADER,
    PARAGRAPH
} TagType;

typedef enum {

    H1,
    H2,
    H3,
    H4,
    H5,
    H6

} HeaderType;


typedef struct HTML_node {

    TagType tagType;
    HeaderType headerType;
    char *content;
    struct HTML_node **children;
    int numChildren;    
    
} HTML_node;


int html_parse(char *input, char *output){
	

    int i = 0;

    char *token = (char *)malloc(sizeof(token) * 100);
    memset(token, 0, 100);
    int internal_counter=0;



/*<h1>// ______  //</h1> */

    for (i = 0; input[i] != '\0'; i++ ){
	
        /*comincia il parsing */ 
        if (input[i] == '<'){

            /*
            //inizio di un tag, creare un token finche non si trova > 
            //quello che c'e' in questo token da' forma al contenuto dopo >
       
            //se c'e' / subito dopo allora e' un closing token 
            //
       */
            i++;
            while (input[i] != '>'){
                /*ingesta im un token il contenuto del tag */
                if (input[i] == ' ' || input[i] == 9){
                    i++;
                } else {
                    token[internal_counter] = input[i];
                    internal_counter++;
		}
	    i++;
            }
        } 
        token[internal_counter+1] = '\0';        
        /*
        //ora hai il token, procedi a verificare che tipo di header e'
        //qui serve uno switch */
        
//	printf("%s\n", token);
	if (strcmp(token, "h1") == 0){
            i += 1;
            int j = 0;
            while (input[i] != '<'){
                output[j] = input[i];
                j++;
                i++;
            }
            output[j+1] = '\0';
		return 2;
	} else {
            strcpy(output,"no header found");
            return 0;
        }


        /*
            //i tag interni che consideriamo per prova quali sono ?
            //serve uno switch case per la rappresentazione dei primi da poi ampliare 
*/
    }
    free(token);
    return MY_SUCCESS; 
}


int main(){
/*
    //da cambiare ovviamente ma intanto per provare senza spargere il malloc in altre funzioni
  */
    char *output = (char *)malloc(sizeof(output) * 100);
    memset(output, 0, 100);

    char *input = (char*) malloc(sizeof(output) * 22);
    memset(input, 0, 22);
    
    strcpy(input,"<h1>Hello, world!</h1>");


	/*dovresti : allocare una volta ingestando il documento html in questione on the fly
	//parsare questa lunga stringa in un array o lista o albero che allochi grazie a una pool ampia 
	//albero_di_html -> che tiene in memoria il tipo di tag, le specifiche interne al tag di formattazione e css, e il contenuto all'interno dello stesso. 
	//			-> c'e' da considerare la logica dei nesting dei vari tag uno dentro l'altro ...
	//come si distingue dal CSS? come si interfaccia il CSS con l'html?
	//supppongo che serva un CSS parser a cui viene passato l'output dell'html parser appena questo ha finito. 
	//
	//
	//
	//una volta che hai tutte queste info,l'albero puo' essere passato a un renderer che lo organizza in base alle specifiche HTML e al DOM 
	//
	//il renderer puo' essere quello gia esistente di un browser, ma puo' anche essere un renderer custom offline come per altri programmi, che risponde allo standard ma separato 
	//da un browser 
	*/



     if (html_parse(input, output)){
     	printf("parse successful\n");
     }

    printf("the parsed text is \e[1m %s\e[0m\n", output);


    free(output);
    free(input);
}
