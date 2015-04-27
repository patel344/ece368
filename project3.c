#include "project3.h"

char * * explode(const char * str, const char * delims, int * arrLen)
{
	//Local Declarations
	int N = 0;
	int i = 0;
	int k = 0;
	int arrInd = 0; // this is the next position where we'll create a string
	int last = 0; // 1 + the last index we saw a delimiter. Init to 0.
	char * * strArr;
	char * newArray;

	//Executables Statements
	// Count how many delimiters are in 'str'
	for (i = 0; i < (strlen(str)); i++) 
	{
  		if (strchr(delims, str[i]) != NULL)
  		{
  			N++;
  		}
	}
	// Create the return array
	strArr = malloc((N+1) * sizeof(char *));
    //strArr = NULL;
	//Filling the Arrays
    if(N != 0)
    {


	   for(i = 0; i < strlen(str); i++) 
        {
       
    	   if (strchr(delims,str[i]) != NULL)
    	   {
                newArray = malloc((1 + strlen(str)) * sizeof(char));
                *newArray = '\0';
    	    	for (k = last; k < i; k++)
    	    	{
                  newArray[k-last] = str[k];
    	       	}

    	    newArray[k-last] = '\0';
    	    strArr[arrInd] = newArray;
    	    last = i + 1;
    	    arrInd++;		
     	   } 
        }
    }
    
    
    newArray = malloc((1 + strlen(str)) * sizeof(char));
    *newArray = '\0';
    for(i = last; i < strlen(str); i++)
    {
    	newArray[i-last] = str[i];
    }
    newArray[i-last] = '\0';
    strArr[N] = newArray;
    *arrLen = N+1;
    //free(newArray);
    return strArr;

}
    
Vertex create_Vertex(int id, int data1, int data2, int data3, int data4, int data5, int data6, int data7, int data8){
    Vertex V;
    V.id = id;
    V.data = malloc(sizeof(int) * 8);
    V.data[0] = data1;
    V.data[1] = data2;
    V.data[2] = data3;
    V.data[3] = data4;
    V.data[4] = data5;
    V.data[5] = data6;
    V.data[6] = data7;
    V.data[7] = data8;
    return V;
}
Graph create_empty_Graph(int users, Vertex* Vertex_Array){
    Graph graph;
    int row,col;
    graph.users = users;
    graph.V = Vertex_Array;
    graph.Edges = (double*)malloc(users*users*sizeof(double));
    for(row = 0; row < users; row++){
	for(col = 0; col < users; col++){
	    *(graph.Edges + row*users + col) = 0.0;
	}
    }
    return graph;
}
void print_graph(Graph graph){
    int row,col;
    int i = 0;
    for(row = 0; row < graph.users; row++){
	for(col = 0; col < graph.users; col++){
	    if(col == (graph.users-1)){
		//printf("%.2f\n", *(graph.Edges + row*graph.users + col));
	     }
	     else{
		 //printf("%.2f ", *(graph.Edges + row*graph.users + col));
	     }	
	    if(*(graph.Edges+row*graph.users+col) > 0.0){
		i++;
	    }
	}
    }
    printf("\nEdges: %d\n", i); 
    return;
}
double calc_UL(Vertex user1, Vertex user2){
    double UL = 0.0;
    int i = 0;
    for(i = 0; i<8; i++){
	UL = UL + pow((user1.data[i] - user2.data[i]), 2);
    }
    UL = sqrt(UL);
    return UL;
}
double find_max(Graph G){
    double max = 0.0;
    int row,col;
    for(row = 0; row < G.users; row++){
	for(col = 0; col < G.users; col++){
	    if(*(G.Edges + row*G.users + col) > max){
		max = *(G.Edges + row*G.users + col);
	    }
	}
    }
    return max;
}
Graph UNnorm_Graph(Graph G){
    int row,col;
    for(row = 0; row<G.users; row++){
	for(col = 0; col<G.users; col++){
	    *(G.Edges + row*G.users + col) = calc_UL(G.V[row],G.V[col]);
	}
    }
    return G;
}
						     
Graph norm_Graph(double max, float lambda, Graph G){
    int row,col;
    for(row = 0; row<G.users; row++){
	for(col=0; col<G.users; col++){
	    if(row == col){
		*(G.Edges + row*G.users + col) = max;
	    }
	    *(G.Edges + row*G.users + col) /= max;
	    *(G.Edges + row*G.users + col) = 1.0 - *(G.Edges + row*G.users + col);
	    *(G.Edges + row*G.users + col) = (floorf(*(G.Edges+row*G.users+col) * 100)) / 100;
	    if(*(G.Edges + row*G.users + col) <= lambda){
		*(G.Edges + row*G.users + col) = 0.0;
	    }
	}
    }
    return G;
}
int* Query3(Graph G, int QueryNode){
    int k,row,col;
    int i = 0;
    int* temp = malloc(sizeof(int) * G.users);
    for(row = G.V[QueryNode-1].id - 1; row<G.V[QueryNode-1].id; row++){
	for(col = 0; col<G.users; col++){
	    if(*(G.Edges + row*G.users + col) > 0.0){
		temp[i] = G.V[col].id;
		i++;
	    }
	}
    }
    int* ID_array = malloc(sizeof(int)*(i+1));
    ID_array[0] = i;
    for(k=0; k<i; k++){
	ID_array[k+1] = temp[k];
    }
    free(temp);
    return ID_array;
}
double Query5(Graph G){
    int i;
    int neighbors = 0;
    double avg_neighbors = 0.0;
    int* array = NULL;
    for(i = 1; i<=G.users; i++){
	array = Query3(G,i);
	neighbors += array[0];
	free(array);
	array = NULL;
    }
    //printf("USERS: %d\n", G.users);
    avg_neighbors = (double)neighbors / (double)G.users;
    avg_neighbors = floorf(avg_neighbors*100) / 100;
    return avg_neighbors;
}
int minDist(Graph G,float* dist, int* S){
    float min = FLT_MAX;
    int minInd;
    int v;
    for(v = 0; v < G.users; v++){
	if(S[v] == 0 && dist[v] <= min){
	    min = dist[v];
	    minInd = v;
	}
    }
    return minInd;
}
void print_Dijkstras(float* dist, Graph G){
    int i;
    printf("Vertex   Distance From Source\n");
    for(i = 0; i < G.users; i++){
	printf("%d \t\t %.2f\n", i, dist[i]);
    }
}
int Query2(Graph G, int queryNode, float alpha){
    float dist[G.users];
    int S[G.users];
    int v,i,count,node;
    int counter = 0;
    int k = 1;
    float min = FLT_MAX;
    for(i = 0; i < G.users; i++){
	dist[i] = FLT_MAX;
	S[i] = 0;
    }
    dist[queryNode - 1] = 0;
    for(count = 0; count < G.users - 1; count++){
	node = minDist(G,dist,S);
	S[node] = 1;
	for(v = 0; v < G.users; v++){
	    if((S[v] == 0) && (*(G.Edges + node*G.users + v) != 0.0) && (dist[node] != FLT_MAX) && (dist[node]+ *(G.Edges + node*G.users + v) < dist[v])){
		dist[v] = dist[node] + *(G.Edges + node*G.users + v);
	    }
	}
    }
    for(k = 0; k < G.users; k++){
	if(dist[k] < alpha && ((k+1) != queryNode)){
	    counter++;
	}
	if(dist[k] < min && ((k+1) != queryNode)){
	    min = dist[k];
	}
    }
    fprintf(stdout, "%.2f", min);
    for(k = 0; k < G.users; k++){
	if(dist[k] == min && ((k+1) != queryNode)){
	    fprintf(stdout,",%d", k+1);
	}
    }
    fprintf(stdout,"\n");
    //print_Dijkstras(dist,G);
    return counter;
}
int cmpfunc (const void * a, const void * b)
{
    if((*(int*)a) <= (*(int*)b)){
	return -1;
    }
    else{
	return 1;
    }
}

int Query4(Graph G, int queryNode, int display){
    int* Flag = malloc(sizeof(int)*G.users);
    int* First_Neighbors = Query3(G,queryNode);
    int* Sec_Neighbors = malloc(sizeof(int)*G.users);
    int i,row,col;
    int k = 0;
    int j = 0;
    for(i = 0; i < G.users; i++){
	Flag[i] = 0;
	Sec_Neighbors[i] = 0;
    }
    for(i = 1; i <= First_Neighbors[0]; i++){
	for(row = G.V[First_Neighbors[i]-1].id - 1; row<G.V[First_Neighbors[i]-1].id; row++){
	    for(col = 0; col<G.users; col++){
		if(Flag[col] == 0 && (*(G.Edges + row*G.users + col) != 0.0) && (col+1 != queryNode)){
		    Sec_Neighbors[k] = col + 1;
		    Flag[col] = 1;
		    k++;
		}
	    }
	}
    }
    qsort(Sec_Neighbors,k,sizeof(int),cmpfunc);
    if(display){
	fprintf(stdout, "\n%d", k);
	for(j = 0; j<k; j++){
	    fprintf(stdout, ",%d", Sec_Neighbors[j]);
	}
    }
    free(First_Neighbors);
    free(Sec_Neighbors);
    free(Flag);
    return k;
}
void Query6(Graph G){
    int i;
    int sec_neighbors = 0;
    double avg_neighbors = 0.0;

    for(i = 1; i<=G.users; i++){
	sec_neighbors += Query4(G,i,0);
    }
    avg_neighbors = (double)sec_neighbors / (double)G.users;
    avg_neighbors = floorf(avg_neighbors * 100) / 100;
    fprintf(stdout,"%.2lf\n", avg_neighbors);
}

int main(int argc, char** argv){
        FILE* fp = fopen(argv[1],"r");
	char* entry = NULL;
	size_t len = 0;
	char* delim = ",\r\t\v\f\n";
	int length_arr = 1;
	char** entry_Arr = NULL;
	ssize_t read;
	int numUsers = 0;
	float lambda1 = 0.0;
	float lambda2 = 0.0;
	int queryNode = 0;
	float alpha = 0.0;
	int id = 0;
	int data1,data2,data3,data4,data5,data6,data7,data8 = 0;
	Vertex V;
	Vertex* Vertex_Array = NULL;
	int k;
	int i = 0;
	int count;
	int counter = 1;
	Graph G;
	double max = 0.0;
	int* Nodes = NULL;
	double avg_immed_neighbors = 0.0;
	int Num_Nodes = 0;

    	while((read = getline(&entry, &len,fp))!=-1){
	    if(read > 1){
		entry_Arr = explode(entry,delim, &length_arr);
		if(counter == 1){
		    numUsers = atoi(entry_Arr[0]);
		    lambda1 = atof(entry_Arr[1]);
		    lambda2 = atof(entry_Arr[2]);
		    queryNode = atoi(entry_Arr[3]);
		    alpha = atof(entry_Arr[4]);
		    Vertex_Array = malloc(sizeof(Vertex) * numUsers);
		    for(k=0;k<5;k++){
			free(entry_Arr[k]);
		    }
		}
		if(counter > 1){
		    id = atoi(entry_Arr[0]);
		    data1 = atoi(entry_Arr[1]);
		    data2 = atoi(entry_Arr[2]);
		    data3 = atoi(entry_Arr[3]);
		    data4 = atoi(entry_Arr[4]);
		    data5 = atoi(entry_Arr[5]);
		    data6 = atoi(entry_Arr[6]);
 		    data7 = atoi(entry_Arr[7]);
		    data8 = atoi(entry_Arr[8]);
		    V = create_Vertex(id,data1,data2,data3,data4,data5,data6,data7,data8);
		    Vertex_Array[i] = V;
		    i++;
		    for(k=0;k<9;k++){
			free(entry_Arr[k]);
		    }	   
		}
		if(entry_Arr != NULL){
		    free(entry_Arr);
		}
	    }
	    counter++;
	    }
	if(entry){
	    free(entry);
	}
	fclose(fp);

	//DENSE GRAPH
	G = create_empty_Graph(numUsers,Vertex_Array);
	G = UNnorm_Graph(G);
	max = find_max(G);
	G = norm_Graph(max,lambda1,G);

	//Query 1 and Query 2
	Num_Nodes = Query2(G,queryNode,alpha);
	fprintf(stdout,"%d", Num_Nodes);
	//Query 3
	Nodes = Query3(G,queryNode);
	fprintf(stdout,"\n%d", Nodes[0]);
	for(count = 1; count<=Nodes[0]; count++){
	    fprintf(stdout,",%d", Nodes[count]);
	}
	//Query 4
	int Sec_Level_Neighbors = Query4(G,queryNode,1);
	//Query 5
	avg_immed_neighbors = Query5(G);
	fprintf(stdout,"\n%.2lf\n", avg_immed_neighbors);
	//Query 6
	Query6(G);

	//print_graph(G);

	//Freeing 
	free(G.Edges);
	free(Nodes);
	printf("\n");

	//SPARSE GRAPH
	G = create_empty_Graph(numUsers,Vertex_Array);
        G = UNnorm_Graph(G);
	max = find_max(G);
	G = norm_Graph(max,lambda2,G);

        //Query 1 and Query 2                                                                                                                                                                         
        Num_Nodes = Query2(G,queryNode,alpha);
        fprintf(stdout,"%d", Num_Nodes);
        //Query 3                                                                                                                                                                                    
        Nodes = Query3(G,queryNode);
        fprintf(stdout,"\n%d", Nodes[0]);
        for(count = 1; count<=Nodes[0]; count++){
	    fprintf(stdout,",%d", Nodes[count]);
        }
        //Query 4                                                                                                                                                                                   
        Sec_Level_Neighbors = Query4(G,queryNode,1);
        //Query 5                                                                                                                                                                                     
        avg_immed_neighbors = Query5(G);
        fprintf(stdout,"\n%.2lf\n", avg_immed_neighbors);
	//Query 6                                                                                                                                                                                   
        Query6(G);
        
	//print_graph(G);                                                                                                                                                                            
        
	//Freeing                                                                                                                                                            
        free(G.Edges);
        free(Nodes);
        for(count = 0; count < numUsers; count++){
	    free(Vertex_Array[count].data);
        }
        free(Vertex_Array);

	return 0;
}
