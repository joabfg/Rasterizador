class color{
    public: unsigned char pixel[3];
};
const int dimx = 602, dimy = 602;//Dimensão da matriz
int i, j;      

class aresta{
    public:
    int x0,y0,x1,y1,xMin,yMin;
};   
 
 aresta allArestas[20];
 aresta arestasAtivas[20];

color branco =   {255,255,255};
color preto =    {0,0,0}; 
color azul =     {29, 95, 160};
color vermelho = {139, 29, 27};
color verde =    {122, 200, 83};
color khaki =    {240,230,140};

enum cores{
  BRANCO,PRETO,AZUL,VERMELHO,VERDE,KHAKI
};


float absoluto(float valor){
  if(valor >=0 )
    return valor;
  else
    return -(valor);
}

int min(int a,int b){
  if(a >= b)
    return b;
  else 
    return a;
}

//Matriz principal que será convertida em imagem
int matriz[dimx][dimy] ;