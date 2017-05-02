/*Parth Patel and Caleb Niemann*/
/*patel344@purdue.edu and niemann@purdue.edu*/

#include<stdio.h>
#include<stdlib.h>
#include<libgen.h>
#include<math.h>
#include<time.h>
#include<string.h>

/*Structure Definitions for Queue linked list and FEL linked list*/
typedef struct Queue_list {
  int priority;
  int arrival_time;
  int service_time;
  int subTasks;
  int* subTask_service_times;
  struct Queue_list * next;
  } Queue;

typedef struct Fut_event_list {
    int service_time;
    int arrival_time;
    int priority; //priority of task
    int subTasks;
    int* subTask_service_times;
    struct Fut_event_list * next;
} FEL;

/*Helper Functions used in simulation (descriptions below in function declarations) */
FEL* create_FEL_node2(int arr, int priority, int service_time){ //creates and initializes event
    FEL* new_node = malloc(sizeof(FEL));
    new_node->arrival_time = arr;
    new_node->priority = priority;
    new_node->service_time = service_time;
    new_node->next = NULL;

    return new_node;
}

int generate_random_time(float rate){ //generates random time for exp. dist. (for service and arrival)
  double X = 1;
  while(X == 1){
      X =  (double) rand() / (double) RAND_MAX;
  }
  double Y1 = (log(1-X)) / (-rate);
    
  return(ceil(Y1));
}
int generate_random_subTasks(){
    double X = (rand() % (32 + 1 - 1)) + 1;
    if((floor(X)) > 32 || (floor(X)) < 1){
	    printf("error\n");
	}
    return floor(X);
}
    
void schedule_event(FEL* node, FEL** list){ //shedules an event to add to FEL
  FEL* temp = *list;
  if(*list == NULL){
      *list = node;
      return;
  }
  if((*list)->next == NULL){
      (*list)->next = node;
      return;
  }
  
  if (node->arrival_time < temp->arrival_time)
    {
      node->next = temp;
      return;
    }      

  while(node->arrival_time >= temp->next->arrival_time){
      temp = temp->next;
      
      if (temp->next == NULL) {
	  temp->next = node;
	  return;
      }
  }
  FEL * temp2 = temp->next;
  node->next = temp2;
  temp->next = node;

  return;
}
FEL* create_node_mode2(int priority, int arrival, int numTasks, int* subTaskTimes) {
    FEL* node = malloc(sizeof(FEL));
    int max = 0;
    int i;

    for (i = 0; i < numTasks; i++) {
	if (subTaskTimes[i] > max) {
	    max = subTaskTimes[i];
	}
    }

    node->service_time = max;
    node->priority = priority;
    node->arrival_time = arrival;
    node->subTasks = numTasks;
    node->subTask_service_times = subTaskTimes;
    node->next = NULL;

    return node;
}
FEL* create_initial_node(int curr_time, int priority, float mu, float lambda){
    int i;
    int max = 0;
    FEL*new_node = malloc(sizeof(FEL));
    new_node->subTasks = generate_random_time(lambda);
    new_node->subTask_service_times = malloc(new_node->subTasks * sizeof(int));
    for(i = 0; i < new_node->subTasks; i++){
	new_node->subTask_service_times[i] = generate_random_time(mu);
	if(new_node->subTask_service_times[i] > max){
	    max = new_node->subTask_service_times[i];
	}
    }
    new_node->service_time = max;
    new_node->arrival_time = curr_time;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}
FEL* create_FEL_node(int curr_time, int priority, float mu, float lambda){
    int i;
    int max = 0;
    FEL* new_node = malloc(sizeof(FEL));
    new_node->subTasks = generate_random_subTasks();
    new_node->subTask_service_times = malloc(new_node->subTasks * sizeof(int));
    for(i = 0; i < new_node->subTasks; i++){
	new_node->subTask_service_times[i] = generate_random_time(mu);
	if(new_node->subTask_service_times[i] > max){
	    max = new_node->subTask_service_times[i];
	}
    }
    new_node->service_time = max;
    new_node->arrival_time = curr_time + (generate_random_time(lambda));
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}
void create_FEL_0(int taskNum, int priority, float mu, float lambda, FEL** list){
    int tasks = 0;
    FEL* first_node = create_initial_node(0,0,mu,lambda);
    schedule_event(first_node,list);
    int arr_time = first_node->arrival_time;
    while(tasks < taskNum - 1){
	FEL*node = create_FEL_node(arr_time,0,mu,lambda);
	arr_time = node->arrival_time;
	schedule_event(node,list);
	tasks++;
    }
    return;
}
void create_FEL_1(int taskNum, int priority, float mu, float lambda,FEL** list){
    int tasks = 0;
    FEL* node = NULL;
    FEL* first_node = NULL;
    first_node = create_initial_node(0,1,mu,lambda);
    schedule_event(first_node,list);
    int arr_time = first_node->arrival_time;
    while(tasks < taskNum - 1){
	node = create_FEL_node(arr_time,1,mu,lambda);
	arr_time = node->arrival_time;
	schedule_event(node,list);
	tasks++;
    }
    return;
}
Queue* create_queue_node(int priority, int arrival_time, int service_time,int subTasks, int* subTask_service_times){
    int i;
    Queue* new_node = malloc(sizeof(Queue));
    new_node->subTasks = subTasks;
    new_node->subTask_service_times = malloc(new_node->subTasks * sizeof(int));
    for(i = 0; i < new_node->subTasks; i++){
	new_node->subTask_service_times[i] = subTask_service_times[i];
    }
    new_node->priority = priority;
    new_node->arrival_time = arrival_time;
    new_node->service_time = service_time;
    new_node->next = NULL;
    return new_node;
}
void addQueue(Queue * node, Queue ** queue)
{
    Queue * temp = (*queue);
  if (*queue == NULL)
      {
	  *queue = node;
	  return;
      }
  while(temp->next != NULL){
	  temp = temp->next;
      }
      temp->next = node;  
  return;
}
void remove_FEL_node(FEL** list){ //removes event from FEL
    FEL * temp = (*list);
    if (temp == NULL){
	return;
    }
    *list = temp->next;
    free(temp->subTask_service_times);
    free(temp);
}

void assignServers(int** servers, int* subTask_service_times,int** CPU_busy,int subTasks) {
    int k;
    int i;
    
    for (k = 0; k < subTasks; k++) {
	for (i = 0; i < 64; i++) {
	    if ((*servers)[i] == 0) {
		(*servers)[i] = subTask_service_times[k];
		(*CPU_busy)[i] += subTask_service_times[k];
		break;
		//printf("%d\n", (*CPU_times)[i]);
	    }
	}
    }
}

int numServersFree(int* servers){
    int i;
    int serversFree = 0;
    for(i = 0; i < 64; i++){
	if((servers)[i] == 0){
	    serversFree++;
	}
    }
    return(serversFree);
}

void updateServers(int** servers, int* finished){
    int i;
    for(i = 0; i < 64; i++){
	if((*servers)[i] > 0){
	    (*servers)[i]--;
	    if ((*servers)[i] == 0) {
		(*finished)--;
		//printf("finished: %d\n", *finished);
	    }
	}
    }
}

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
    return strArr;

}

Queue * scanQueue(Queue** queue, int serversFree) {
    Queue* temp = *queue;
    Queue* head = *queue;
   
    if (*queue == NULL) {
    	return NULL;
    }
    
    if((*queue)->subTasks <= serversFree){\
	(*queue)->next = temp->next;
	head = (*queue)->next;
	*queue = head;
	return temp;
    }
    if ((*queue)->next == NULL && temp->subTasks <= serversFree) {
	temp = *queue;
	temp->next = NULL;
	*queue = NULL;

	return temp;
    }
 
    while (temp != NULL) {
	if (temp->subTasks <= serversFree) {
	    (*queue)->next = temp->next;
	    *queue = head;
	    temp->next = NULL;
	    return temp;
	}
	*queue = temp;
	temp = temp->next;
    }

    *queue = head; 

    return NULL;
}

float load_bal_factor(FEL** list,float mu,int taskNum){   //Calculates average load balancing factor
    FEL * temp = *list;
    float factor = 0;
    float max = 0;
    float min;
    int i;

    while(temp != NULL){
        max = 0;
	min = temp->subTask_service_times[0];
	for(i = 0; i < temp->subTasks; i++){
	    if(temp->subTask_service_times[i] < min){
		min = temp->subTask_service_times[i];
	    }
	    if(temp->subTask_service_times[i] > max){
		max = temp->subTask_service_times[i];
	    }
	}
	factor = factor + (max - min) / (1 / mu);
	temp = temp->next;
    }
    factor = factor / (2 * taskNum);
    return factor;
}
float load_bal_factor_2(FEL**list, int taskNum){
    FEL* temp = *list;
    float factor = 0;
    float max = 0;
    float min;
    int i;
    float avg_time = 0;
    
    while(temp != NULL){
        avg_time = 0;
	max = 0;
	min = temp->subTask_service_times[0];
	for(i = 0; i < temp->subTasks; i++){
	    if(temp->subTask_service_times[i] < min){
		min = temp->subTask_service_times[i];
	    }
	    if(temp->subTask_service_times[i] > max){
		max = temp->subTask_service_times[i];
	    }
	    avg_time += temp->subTask_service_times[i];
	}
        avg_time /= temp->subTasks;
	factor = factor + (max - min) / avg_time;
	temp = temp->next;
    }
    factor = factor / taskNum;
    printf("%d\n", taskNum);
    return factor;
}
                                                                         
int main(int argc, char** argv){
    srand(time(NULL));
    /*Declaration of Variables*/
    float mu;
    float lambda0;
    float lambda1;
    int taskNum;
    FILE* fp;
    ssize_t read;
    char* entry;
    size_t len;
    char** entry_Arr;
    char* delim;
    int length_arr;
    int i;
    int mode;
    int arrive;
    int priority;
    FEL * arr_node;
    int * servers = NULL;
    int * CPU_busy = NULL;
    servers = malloc(sizeof(int) * 64);
    CPU_busy = malloc(sizeof(int) * 64);
    int finished = 0;
    
    for (i = 0; i < 64; i++) {
	servers[i] = 0;
	CPU_busy[i] = 0;
    }
    
    /*Determing which mode to follow based command line arguments*/
    if (argc > 2) {               //Initalizes variables needed for mode 1
	mu = atof(argv[3]);
	lambda0 = atof(argv[1]);
	lambda1 = atof(argv[2]);
	taskNum = atoi(argv[4]);
	mode = 1;
    } 
    else {                       //Initializes variables needed for mode 2
	fp = fopen(argv[1],"r");
	entry = NULL;
	len = 0;
	delim = " \n";
	length_arr = 1;
	arr_node = NULL;
	mode = 2;
	taskNum = 0;
    }
    /*Initialization of shared variables for Mode 1 and Mode 2*/
    int Q = 0;
    int numTasks = 0;
    int queue_length = 0;
    int wait_time_0 = 0;
    int wait_time_1 = 0;
    int tot_wait_time_0 = 0;
    int tot_wait_time_1 = 0;
    //int service_time = 0;
    int curr_time = 0;
    int CPU_activity = 0;
    Queue* queue_node_0 = NULL;
    Queue* queue_node_1 = NULL;
    float CPU_util = 0;
    float avg_queue_length = 0;
    float avg_waiting_time_0 = 0;
    float avg_waiting_time_1 = 0;
    FEL* list = NULL; 
    Queue* queue_0 = NULL;
    Queue* queue_1 = NULL;
    int serversFree = 0;
    Queue* scanNode_0 = NULL;
    Queue* scanNode_1 = NULL;
    float load_balancing_factor = 0;


    /*Initial Steps needed before beginning simulation depending on the mode*/
    if (mode == 1) {
	/*Generates random arrival and service times for type 0 and type 1 and places it an FEL (sorted by time) */
	create_FEL_0(taskNum,0,mu,lambda0,&list);
	create_FEL_1(taskNum,1,mu,lambda1,&list);
	FEL* temp = list;
	while(temp != NULL){
	    finished += temp->subTasks;
	    temp = temp->next;
	}

	load_balancing_factor = load_bal_factor(&list,mu,taskNum); 
    }
    else {                                            

	/*Reads in all the data from the text file and generates an FEL*/
	while((read = getline(&entry, &len,fp))!=-1){
	    entry_Arr = explode(entry,delim, &length_arr);
	    arrive = atoi(entry_Arr[0]);
	    priority = atoi(entry_Arr[1]);
	    numTasks = atoi(entry_Arr[2]);
	    int* subTasks = malloc(sizeof(int) * numTasks);

	    for (i = 0; i < numTasks; i++) {
		subTasks[i] = atoi(entry_Arr[i + 3]);
	    }

	    arr_node = create_node_mode2(priority, arrive, numTasks, subTasks);
	    schedule_event(arr_node, &list);
	    taskNum++;

	    for (i = 0; i < length_arr; i++) {
		free(entry_Arr[i]);
	    }
	    if(entry_Arr != NULL){
		free(entry_Arr);
	    }
	}
	
	if(entry){
	    free(entry);
	}
	fclose(fp);

	FEL* temp2 = list;
	finished = 0;
	while(temp2 != NULL){
	    finished += temp2->subTasks;
	    temp2 = temp2->next;
	}
	load_balancing_factor = load_bal_factor_2(&list,taskNum);
    }

    /*Actual simulation of a priority queue*/
    while ((mode == 1 && (finished > 0)) || (mode == 2 && (finished > 0))) {                       //Ends when total tasks have been reached. Also handles different modes

	/*Deals with all tasks at current time*/
	while(list != NULL && list->arrival_time == curr_time){                                       
	    if(list->priority == 0){  //adds to the type 0 queue if it is a type 0 arrival
		queue_node_0 = create_queue_node(list->priority,list->arrival_time,list->service_time,list->subTasks,list->subTask_service_times);
		queue_length = queue_length + Q; //calculates queue_length                  
		addQueue(queue_node_0, &queue_0);
		Q = Q + 1;
		remove_FEL_node(&list);
	    }
	    else{ //adds to the type 1 queue if it is a type 1 arrival
		queue_node_1 = create_queue_node(list->priority,list->arrival_time,list->service_time,list->subTasks, list->subTask_service_times);
		queue_length = queue_length + Q;
		addQueue(queue_node_1,&queue_1);
		Q = Q + 1;
		remove_FEL_node(&list);
	    }
	}
	/*CHECK HOW MANY SERVERS ARE FREE*/
	serversFree = numServersFree(servers);

	scanNode_0 = scanQueue(&queue_0,serversFree);
	while (scanNode_0 != NULL){
	    wait_time_0 = curr_time - scanNode_0->arrival_time; //gets waiting time of current task 
	    tot_wait_time_0 = tot_wait_time_0 + wait_time_0; //running total of waiting time for type 0 tasks 
	    Q = Q - 1;
	    assignServers(&servers, scanNode_0->subTask_service_times, &CPU_busy,scanNode_0->subTasks);
	    serversFree = numServersFree(servers);
	    free(scanNode_0->subTask_service_times);
	    free(scanNode_0);
	    scanNode_0 = NULL;
	    scanNode_0 = scanQueue(&queue_0,serversFree);
	}
	
	serversFree = numServersFree(servers);
	scanNode_1 = scanQueue(&queue_1,serversFree);
        while (scanNode_1 != NULL){
	    wait_time_1 = curr_time - scanNode_1->arrival_time; //gets waiting time of current task 
      	    tot_wait_time_1 = tot_wait_time_1 + wait_time_1; //running total of waiting time for type 0 tasks 
	    Q = Q - 1;
	    assignServers(&servers, scanNode_1->subTask_service_times,&CPU_busy,scanNode_1->subTasks);
	    serversFree = numServersFree(servers);
	    free(scanNode_1->subTask_service_times);
	    free(scanNode_1);
	    scanNode_1 = NULL;
	    scanNode_1 = scanQueue(&queue_1,serversFree);
	}
	
	if(curr_time > 0){
	    updateServers(&servers, &finished);
	}
	serversFree = numServersFree(servers);
	curr_time++;
    }

    for(i = 0; i < 64; i++){
	CPU_activity += CPU_busy[i];
    }

  // Calculations of Performance Parameters
  if(mode == 1){
  avg_queue_length = (float) queue_length /(float) (2*taskNum);
  avg_waiting_time_0 = (float)tot_wait_time_0 /(float) taskNum;
  avg_waiting_time_1 = (float)tot_wait_time_1 / (float)taskNum;
  CPU_util = (float)CPU_activity / (float)(curr_time * 64);
  } else {
  avg_queue_length = (float) queue_length /(float) (taskNum);
  avg_waiting_time_0 = (float)tot_wait_time_0 /((float) (taskNum / 2));
  avg_waiting_time_1 = (float)tot_wait_time_1 / ((float)(taskNum / 2));
  CPU_util = (float)CPU_activity / (float)(curr_time * 64);
  }


  /*Outputting of Statistics to File*/
  FILE * fp_out = fopen("proj1_output","wb");
  fprintf(fp_out, "%f\n", avg_waiting_time_0);
  fprintf(fp_out, "%f\n", avg_waiting_time_1);
  fprintf(fp_out, "%f\n", avg_queue_length);
  fprintf(fp_out, "%f\n", CPU_util);
  fprintf(fp_out, "%f\n", load_balancing_factor);
 
  fclose(fp_out);
  free(CPU_busy);
  free(servers); 

  return 0;

}
