

void carregarArestas(Json::Value formas){
	for (int i = 0; i < formas.size(); ++i){
	    const Json::Value& forma = formas[i];
	    if(forma["type"].asString() == "polygon"){
          
          Json::Value points = forma["points"];
          int dx=forma["coord"]["dx"].asUInt(); 
          int dy=forma["coord"]["dy"].asUInt();
          //color cor = getColorByName(forma["color"].asString());

          const Json::Value& point0 = points[0];

         
          for (int j = 1; j < points.size()-1; ++j){
            const Json::Value& pointA = points[j];
            const Json::Value& pointB = points[j+1];

            int x0=pointA["x"].asUInt(); 
            int y0=pointA["y"].asUInt();
            int x1=pointB["x"].asUInt(); 
            int y1=pointB["y"].asUInt();
            
            allArestas[j].x0 = x0;
            allArestas[j].y0 = y0;
            allArestas[j].x1 = x1;
            allArestas[j].y1 = y1;     
            allArestas[j].xMin = min(x0,x1);
            allArestas[j].yMin = min(y0,y1);       
          }
          

        }
	 }
}

void ordenarArestas(int quantidadeArestas){
	for(int i=0; i < quantidadeArestas ; i++){
		for(int j=i+1; j < quantidadeArestas ; j++){
			aresta a = allArestas[i];
			aresta b = allArestas[j];
			aresta temp;

			if(a.yMin > b.yMin){
				temp = a;
				allArestas[i] = b;
				allArestas[j] = temp;
			}
		}

	}
}

void scanLineFill(Json::Value formas){

	carregarArestas(formas);
	ordenarArestas(formas.size());
}