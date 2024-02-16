#include<stdio.h>
#include<string.h>
#include <conio2.h>
#include <ctype.h>

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

struct TpDesc
{
	TpEditora *editora;
	TpAutor *autor;
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
    fclose(arqBin);
}

void gera_arq_bin()
{
	FILE *arq = fopen("livros.txt","r");
    TpRegistro reg;
    FILE *arqBin = fopen("livros.dat","wb");
    fscanf(arq,"%[^|]|%[^|]|%[^|]|%d|%d\n", &reg.autores, &reg.titulo_livro, &reg.editora, &reg.ano, &reg.paginas);
    while(!feof(arq))
	{
    	//printf("%s\t%s\t%s\t%d\t%d\n",reg.autores, reg.titulo, reg.editora, reg.ano, reg.pag );
    	fwrite(&reg,sizeof(TpRegistro),1,arqBin);
    	fscanf(arq,"%[^|]|%[^|]|%[^|]|%d|%d\n", &reg.autores, &reg.titulo_livro, &reg.editora, &reg.ano, &reg.paginas);
    };
    fclose(arq);
    fclose(arqBin);
		
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

TpLisAut *NovaCaixaLis(TpAutor *aut)
{
	TpLisAut *NC = new TpLisAut;
	NC->autor = aut;
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
	while(p != NULL && stricmp(p -> editora, edi) != 0)
		p = p -> prox;
	return p;
}

TpLivros *BuscaLiv(char liv[30], TpLivros *p)
{
	while(p != NULL && stricmp(p -> titulo, liv) != 0)
		p = p -> prox;
	return p;
}

TpLisAut *BuscaLis(char nome[30], char sobrenome[30], TpLisAut *p)
{
//  TpLisAut *aux = NULL;
//	TpAutor *aux2;
//	
//	if(p == NULL)
//		return NULL;
//	else
//	{
//		aux = p;
//		aux2 = p->autor;
//		while(aux != NULL && strcmp(aux2->sobrenome,sNome) != 0)
//		{
//			aux = aux->prox;
//			aux2 = aux->autor;
//		}
//	}
//	return aux;

	while(p != NULL && (stricmp(p -> autor -> nome, nome) != 0 || stricmp(p -> autor -> sobrenome, sobrenome) != 0))
		p = p -> prox;
	return p;
}

TpAutor *BuscaAut(char nome[30], char sobrenome[30], TpAutor *p)
{
	while(p != NULL && (stricmp(p -> nome, nome) != 0 || stricmp(p -> sobrenome, sobrenome) != 0))
		p = p -> prox;
	return p;
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

TpLisAut *InserirLis(TpLisAut *p, TpAutor *aut)
{
	TpLisAut *aux, *NC = NovaCaixaLis(aut);
	
	if(p == NULL)
		p = NC;
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

void *gera_est_din(TpDesc &desc)
{
	FILE *Ptr = fopen("livros.dat","rb");
	TpRegistro reg;
	TpEditora *e;
	TpLivros *L,*l;
	TpLisAut **LA, *la;
	TpAutor *a;
	int i, j;
	char aux, str1[30], str2[30];
	
	fread(&reg,sizeof(TpRegistro),1,Ptr);
	while(!feof(Ptr))
	{
		if(desc.editora == NULL || BuscaEdi(reg.editora,desc.editora) == NULL)
			desc.editora = InserirEdi(reg.editora,desc.editora);
		e = BuscaEdi(reg.editora,desc.editora);
		
		e->livros;
		if(e->livros == NULL || BuscaLiv(reg.titulo_livro,e->livros) == NULL)
			e -> livros = InserirLiv(reg,e->livros);
		l = BuscaLiv(reg.titulo_livro,e->livros);
		
		i = 0;
		
		l->pListaAutor;
		while(reg.autores[i] != '\0')
		{
			aux = reg.autores[i];
			for(j = 0;aux != ','; j++)
			{
				if(toupper(aux) >= 'A' && toupper(aux) <= 'Z' || aux == '.');
					str1[j] = aux; 
				aux = reg.autores[++i];
			}
			str1[j] = '\0';
			
			for(j = 0; aux != ';' && aux != '\0' ; j++)
			{
				if(toupper(aux) >= 'A' && toupper(aux) <= 'Z' || aux == '.');
					str2[j] = aux;
				aux = reg.autores[++i];
			}
			str2[j] = '\0';
			
			if(desc.autor == NULL || BuscaAut(str2, str1,desc.autor) == NULL)
				desc.autor = InserirAut(str2,str1,desc.autor);
			
			if(l->pListaAutor == NULL || BuscaLis(str2, str1, l->pListaAutor) == NULL)
				l->pListaAutor = InserirLis(l->pListaAutor, BuscaAut(str2, str1, desc.autor));
		}
		fread(&reg,sizeof(TpRegistro),1,Ptr);
	}
	fclose(Ptr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RelEdi(TpDesc desc)
{
	TpEditora *e = desc.editora;
	TpLivros *l;
	TpLisAut *la;
	
	clrscr();
	while(e != NULL)
	{
		printf("\n%s\n",e->editora);
		l = e->livros;
		while(l != NULL)
		{
			printf("%s\t%d\t%d\n",l->titulo,l->paginas,l->ano);
			la = l->pListaAutor;
			while(la != NULL)
			{
				printf("%s,%s\t",la->autor->sobrenome,la->autor->nome);
				la = la -> prox;
			}
			printf("\n");
			l = l->prox;
		} 
		e = e->prox;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









int main(void)
{
	TpDesc desc;
	desc.autor = NULL;
	desc.editora = NULL;
	gera_arq_bin();
	//imprime();
	
	gera_est_din(desc);
	RelEdi(desc);
	
	return 0;
}


























































