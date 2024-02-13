#include<stdio.h>
#include<string.h>

struct TpRegistro 
{
	char autores[100],titulo_livro[100], editora[50];
	int ano, paginas;
};

struct TpAutor
{
	TpAutor *prox;
	char nome[30], sobrenome[30];
};

struct TpLisAut
{
	TpLisAut *prox;
	TpAutor *autor;	
};

struct TpLivros
{
	TpLivros *ant, *prox;
	char titulo[100];
	int ano, paginas;
	TpLisAut *pListaAutor;
};

struct TpEditora
{
	char editora[30];
	TpEditora *prox;
	TpLivros *livros;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void imprime()
{
	FILE *arqBin = fopen("livros.dat","rb");
    TpRegistro reg;
    fread(&reg,sizeof(TpRegistro),1,arqBin);
    while (!feof(arqBin))
	{	
    	printf("%s\n%s\n%s\t%d\t%d\n\n",reg.autores, reg.titulo_livro, reg.editora, reg.ano, reg.paginas);
        fread(&reg,sizeof(TpRegistro),1,arqBin);
    }  
}

void gera_arq_bin()
{
	FILE *arq = fopen("livros.txt","r");
    TpRegistro reg;
    FILE *arqBin = fopen("livros.dat","wb");
    fscanf(arq,"%[^|]|%[^|]|%[^|]|%d|%d", &reg.autores, &reg.titulo_livro, &reg.editora, &reg.ano, &reg.paginas);
    while(!feof(arq))
	{
    //	printf("%s\t%s\t%s\t%d\t%d\n",reg.autores, reg.titulo, reg.editora, reg.ano, reg.pag );
    	fwrite(&reg,sizeof(TpRegistro),1,arqBin);
    	fscanf(arq,"%[^|]|%[^|]|%[^|]|%d|%d", &reg.autores, &reg.titulo_livro, &reg.editora, &reg.ano, &reg.paginas);
    };
    fclose(arq);
    fclose(arqBin);
    printf("\n\nConcluido\n");
		
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TpEditora *NovaCaixaEdi(char edi[30])
{
	TpEditora *NC = new TpEditora;
	strcpy(NC->editora,edi);
	NC->livros = NULL;
	NC->prox = NULL;
	return NC;
}

TpLivros *NovaCaixaLiv(TpRegistro reg)
{
	TpLivros *NC = new TpLivros;
	NC->ant = NC->prox = NULL;
	NC->pListaAutor = NULL;
	NC->ano = reg.ano;
	NC->paginas = reg.paginas;
	strcpy(NC->titulo,reg.titulo_livro);
	return NC;
}

TpLisAut *NovaCaixaLis()
{
	TpLisAut *NC = new TpLisAut;
	NC->autor = NULL;
	NC->prox = NULL;
	return NC;
}

TpAutor *NovaCaixaAut(char nome[30], char sobrenome[30])    //lembrar de separa os autores e de separar os nomes dos sobrenomes
{
	TpAutor *NC = new TpAutor;
	NC->prox = NULL;
	strcpy(NC->nome,nome);
	strcpy(NC->sobrenome,sobrenome);
	return NC;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TpEditora *BuscaEdi(char edi[30], TpEditora *p)
{
	TpEditora *aux;
	
	if(p == NULL)
		return NULL;
	else
	{
		aux = p;
		while(aux != NULL && strcmp(aux->editora,edi) != 0)
			aux = aux->prox;
		return aux;
	}
}

TpLivros *BuscaLiv(char liv[30], TpLivros *p)
{
	TpLivros *aux;
	
	if(p == NULL)
		return NULL;
	else
	{
		aux = p;
		while(aux != NULL && strcmp(aux->titulo,liv) != 0)
			aux = aux->prox;
		return aux;
	}
}

TpLisAut *BuscaLis(char sNome[30], TpLisAut *p)
{
	TpLisAut *aux;
	TpAutor *aux2;
	
	if(p == NULL)
		return NULL;
	else
	{
		aux = p;
		aux2 = p->autor;
		while(aux != NULL && strcmp(aux2->sobrenome,sNome) != 0)
		{
			aux = aux->prox;
			aux2 = aux->autor;
		}
		return aux;
	}
}

TpAutor *BuscaAut(char SobNome[30],TpAutor *p)
{
	TpAutor *aux;
	
	if(p == NULL)
		return NULL;
	else
	{
		aux = p;
		while(aux != NULL && strcmp(aux->sobrenome,SobNome) != 0)
			aux = aux->prox;	
		return aux;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TpEditora *InserirEdi(char edi[30], TpEditora *p)
{
	TpEditora *aux, *NC = NovaCaixaEdi(edi);
	
	if(p == NULL)
		p = NC;
	else
	{
		aux = p;
		while(aux->prox != NULL )
			aux = aux->prox;
		aux->prox = NC;
	}
	return p;
}

TpLivros *InserirLiv(TpRegistro reg,TpLivros *p)
{
	TpLivros *aux, *NC = NovaCaixaLiv(reg);
	
	if(p == NULL)
		p = NC;
	else
	{
		aux = p;
		while(aux->prox !=NULL)
			aux = aux->prox;
		aux->prox = NC;
		NC->ant = aux;
	}
	return p;
}

TpLisAut *InserirLis(TpLisAut *p)
{
	TpLisAut *aux, *NC = NovaCaixaLis();
	
	if(p = NULL)
		return NULL;
	else
	{
		aux = p;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = NC;
	}
	return p;
}

TpAutor *InserirAut(char nome[30], char sobreNome[30], TpAutor *p)
{
	TpAutor *aux, *NC = NovaCaixaAut(nome,sobreNome);
	
	if(p == NULL)
		p = NC;
	else
	{
		aux = p;
		while(aux->prox !=0)
			aux = aux->prox;
		aux->prox = NC;
	}
	return p;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TpEditora *gera_est_din(TpEditora *E, TpAutor *A)
{
	FILE *Ptr = fopen("livros.dat","rb");
	TpRegistro reg;
	TpEditora *e;
	TpLivros *L,*l;
	TpLisAut *LA, *la;
	TpAutor *a;
	int i, j;
	char aux, str1[30], str2[30];
	
	fread(&reg,sizeof(TpRegistro),1,Ptr);
	while(!feof(Ptr))
	{
		if(E == NULL || BuscaEdi(reg.editora,E) == NULL)
			E = InserirEdi(reg.editora,E);
		e = BuscaEdi(reg.editora,E);
		
		L = e->livros;
		if(L == NULL || BuscaLiv(reg.titulo_livro,L) == NULL)
			L = InserirLiv(reg,L);
		l = BuscaLiv(reg.titulo_livro,L);
		
		
		LA = l->pListaAutor;
		i = 0;
		while(reg.autores[i] != '|')
		{
			aux = reg.autores[i];
			for(j = 0;aux != ','; j++)
			{
				str1[j] = aux; 
				aux = reg.autores[++i];
			}
			str1[++j] = '/0';
			
			for(j = 0; aux != ';' || aux != '|' ; j++)
			{
				str2[j] = aux;
				aux = reg.autores[++i];
			}
			str2[++j] = '/0';
			
			
			if(LA == NULL || BuscaLis(str1,LA) == NULL)
				InserirLis(LA);
			
			
			if(A == NULL || BuscaAut(str1,A) == NULL)
				A = InserirAut(str2,str1,A);
			
			la = BuscaLis(str1,LA);
			la->autor = BuscaAut(str1,A);
			
			
			
		}
	}
	
	
	
}











int main(void)
{
	gera_arq_bin();
	imprime();
	return 0;
}



























































