//https://github.com/open-source-parsers/jsoncpp
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


#include "const.cpp"
#include "scanfill.cpp"
#include "fillFlood.cpp"




int getColorByName(string color){
  if(color == "branco")
    return BRANCO;
   if(color == "preto")
    return PRETO;
   if(color == "azul")
    return AZUL;
   if(color == "verde")
    return VERDE;
  if(color == "vermelho")
    return VERMELHO;
if(color == "khaki")
    return KHAKI;
return PRETO;
}

color getColorByiD(int color){
  if(color == BRANCO)
    return branco;
   if(color == PRETO)
    return preto;
   if(color == AZUL)
    return azul;
   if(color == VERDE)
    return verde;
  if(color == VERMELHO)
    return vermelho;
 if(color == KHAKI)
    return khaki;
return preto;
}


void gerarImagem(){

    FILE *fp = fopen("images/imagem1.ppm", "wb"); /* b - modo binário */

    //Descrição do arquivo
     fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
    // Desenha a matriz no arquivo
     for (j = dimy; j > 0; --j){
        for (i = 0; i < dimx; ++i){
           fwrite(getColorByiD(matriz[i][j]).pixel, 1, 3, fp);//Escreve no arquivo a cor
       }
   }
    fclose(fp);//Salva o arquivo
}


/*
variáveis que descfrevem o segmento (x0,y0),(x1,y1)
deslocamento do segmento (vx,vy)
*/
void lineDDA( int x0, int y0, int x1, int y1, int colorForma,int vx, int vy ) {
	x0 +=vx;
	y0 +=vy;
	x1 +=vx;
	y1 +=vy;
    
    float dx, dy,x, y, step;
    dx = (x1 - x0);
    dy = (y1 - y0);
    
    if(absoluto(dx) >= absoluto(dy)){
      step=absoluto(dx);
    } else{
      step=absoluto(dy);
    }
 
    dx=dx/step;
    dy=dy/step;
    
    y = y0;
    x = x0;
   // cout << dx <<","<< dy << "step:"<< step << endl;
    for( int i = 0; i <= step; i++ ) {
        //"Pinta o pixel com a cor informada"
       matriz[(int)x][(int)y] = colorForma;
       matriz[(int)x+1][(int)y] = colorForma;
       matriz[(int)x][(int)y+1] = colorForma;
        y += dy;
        x += dx;
    }  
}
void lineBresenham( int x0, int y0, int x1, int y1, int colorForma,int vx, int vy ){

  x0 = x0+vx;
  y0 = y0+vy;
  x1 = x1+vx;
  y1 = y1+vy;

  int dx = x1-x0;
  int dy = y1-y0;

  int pk = 2*dy - dx;
  int x = x0;
  int y = y0;
  matriz[x][y] = colorForma;
  for (x = x0+1; x <= x1 ; ++x){
    if(pk <0 ){
      pk = pk + 2*dy;
    }else{
      y=y+1;
      pk=pk+2*dy - 2*dx;
    }
    matriz[x][y] = colorForma;
  }
}
void midPointCircle( int raio, int x0,int y0, int colorForma ) {
    int x = 0;
    int y = raio;
    int d = 1 - raio;

    while(y > x){
      matriz[x0+x][y0+y] = colorForma;
      matriz[x0+x+1][y0+y] = colorForma;
      matriz[x0+x][y0+y+1] = colorForma;

      matriz[x0+y][y0+x] = colorForma;
      matriz[x0+y+1][y0+x] = colorForma;
      matriz[x0+y][y0+x+1] = colorForma;

      matriz[x0-x][y0+y] = colorForma;
      matriz[x0-x+1][y0+y] = colorForma;
      matriz[x0-x][y0+y+1] = colorForma;

      matriz[x0-y][y0+x] = colorForma;
      matriz[x0-y+1][y0+x] = colorForma;
      matriz[x0-y][y0+x+1] = colorForma;

      matriz[x0-x][y0-y] = colorForma;
      matriz[x0-x+1][y0-y] = colorForma;
      matriz[x0-x][y0-y+1] = colorForma;

      matriz[x0-y][y0-x] = colorForma;
      matriz[x0-y+1][y0-x] = colorForma;
      matriz[x0-y][y0-x+1] = colorForma;

      matriz[x0+x][y0-y] = colorForma;
      matriz[x0+x+1][y0-y] = colorForma;
      matriz[x0+x][y0-y+1] = colorForma;

      matriz[x0+y][y0-x] = colorForma;
      matriz[x0+y+1][y0-x] = colorForma;
      matriz[x0+y][y0-x+1] = colorForma;

      if(d < 0){
        d = d + 2 * x + 3;
      }else{
        d = d + 2 * (x-y) + 5;
        y = y-1;
      }
      x = x + 1;
      
    }
}

void rasterizar(Json::Value formas){
   // Monta a matriz da imagem
    for (j = 0; j < dimy; ++j){
        for (i = 0; i < dimx; ++i){ 
            matriz[i][j] = PRETO;
       }
   }

    /*
    Percorre o arquivo de descrição da cena rederizando cada figura
    */
    for (int i = 0; i < formas.size(); ++i){
	      const Json::Value& forma = formas[i];

	      /*
	      Função para rasterizar Linhas
	      */
	      if(forma["type"].asString() == "line"){
		      int x0=forma["coord"]["x0"].asUInt();
		      int y0=forma["coord"]["y0"].asUInt(); 
		      int x1=forma["coord"]["x1"].asUInt(); 
		      int y1=forma["coord"]["y1"].asUInt();
		      int dx=forma["coord"]["dx"].asUInt(); 
		      int dy=forma["coord"]["dy"].asUInt();
		      int cor = getColorByName(forma["color"].asString());
	          lineDDA(x0,y0,x1,y1,cor,dx,dy);
	      }

	      /*
			Desenhando poliLinhas
	      */
	      if(forma["type"].asString() == "polyLine"){
	      	
          Json::Value points = forma["points"];
		      int dx=forma["coord"]["dx"].asUInt(); 
		      int dy=forma["coord"]["dy"].asUInt();
		      int cor = getColorByName(forma["color"].asString());

		      const Json::Value& point0 = points[0];

		      int xTemp=point0["x"].asUInt(); 
			    int yTemp=point0["y"].asUInt();
	      	for (int j = 1; j < points.size(); ++j){
	      	 	const Json::Value& point = points[j];

		      	int x=point["x"].asUInt(); 
			      int y=point["y"].asUInt();
            //cout << "Deseanhando o linha ("<<xTemp<<","<<yTemp<<") - (" << x<<","<<y<<") "<< endl;
  			    lineDDA(xTemp,yTemp,x,y,cor,dx,dy);
  			    xTemp = x;
  			    yTemp = y;

	      	}
	      }

          /*
      Desenhando poliGONOS
        */
        if(forma["type"].asString() == "polygon"){
          
          Json::Value points = forma["points"];
          int dx=forma["coord"]["dx"].asUInt(); 
          int dy=forma["coord"]["dy"].asUInt();
          int cor = getColorByName(forma["color"].asString());

          const Json::Value& point0 = points[0];

          int xTemp=point0["x"].asUInt(); 
          int yTemp=point0["y"].asUInt();
          for (int j = 1; j < points.size(); ++j){
            const Json::Value& point = points[j];

            int x=point["x"].asUInt(); 
            int y=point["y"].asUInt();
            //cout << "Deseanhando o linha ("<<xTemp<<","<<yTemp<<") - (" << x<<","<<y<<") "<< endl;
            lineDDA(xTemp,yTemp,x,y,cor,dx,dy);
            xTemp = x;
            yTemp = y;
          }
          lineDDA(xTemp,yTemp,point0["x"].asUInt(),point0["y"].asUInt(),cor,dx,dy);//linha para fechar o poligono

          int fill = getColorByName(forma["fill"].asString());
          int xfill=forma["xfill"].asUInt(); 
          int yfill=forma["yfill"].asUInt();
          // Pinta o circulo
          if(fill > 0)
   		 	 floodFill4(xfill, yfill, fill, PRETO);

        }
        /*
        DESENHANDO CIRCULOS
        */
        if(forma["type"].asString() == "circle"){
          
	      	int dx=forma["coord"]["dx"].asUInt(); 
		      int dy=forma["coord"]["dy"].asUInt();
		      int raio=forma["raio"].asUInt();
		      int cor = getColorByName(forma["color"].asString());
	     	  midPointCircle(raio,dx,dy,cor);

	     	  int fill = getColorByName(forma["fill"].asString());
       
	          // Pinta o circulo
	   		  floodFill4(dx+2, dy+2, KHAKI, PRETO);
	  	}
     
    }
}



int main(void){

  std::ifstream myfile("cenaConcurso.json");
  
 // myfile.open ("cena.json");

  Json::Reader reader;
  Json::Value formas;
  reader.parse(myfile, formas); // reader can also read strings


  myfile.close();

   //Desenhas as formas lidas do arquivo de descrição de cena
   rasterizar(formas);

  
   gerarImagem();
   
    return EXIT_SUCCESS;
}