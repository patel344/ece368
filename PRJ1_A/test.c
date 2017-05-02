
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
  struct Queue_list * next;
  } Queue;

typedef struct Fut_event_list {
    int service_time;
    int arrival_time;
    int priority; //priority of task
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
FEL* create_initial_node(int curr_time, int priority, float mu, float lambda){
    //srand(time(NULL));
    FEL*new_node = malloc(sizeof(FEL));
    new_node->service_time = generate_random_time(mu);
    new_node->arrival_time = curr_time;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}
FEL* create_FEL_node(int curr_time, int priority, float mu, float lambda){
    FEL* new_node = malloc(sizeof(FEL));
    //srand(time(NULL));
    new_node->service_time = generate_random_time(mu);
    new_node->arrival_time = curr_time + (generate_random_time(lambda));
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}
void create_FEL_0(int taskNum, int priority, float mu, float lambda, FEL** list){
    int tasks = 0;
    int curr_time = 0;
    FEL* first_node = create_initial_node(0,0,mu,lambda);
    schedule_event(first_node,list);
    int arr_time = first_node->arrival_time;
    while(tasks < taskNum - 1){
	//srand(time(NULL));
	FEL*node = create_FEL_node(arr_time,0,mu,lambda);
	arr_time = node->arrival_time;
	schedule_event(node,list);
	tasks++;
    }
    return;
}
void create_FEL_1(int taskNum, int priority, float mu, float lambda,FEL** list){
    int tasks = 0;
    int curr_time = 0;
    FEL* first_node = create_initial_node(0,1,mu,lambda);
    schedule_event(first_node,list);
    int arr_time = first_node->arrival_time;
    while(tasks < taskNum - 1){
	//srand(time(NULL));
	FEL*node = create_FEL_node(arr_time,1,mu,lambda);
	arr_time = node->arrival_time;
	schedule_event(node,list);
	tasks++;
    }
    return;
}
Queue* create_queue_node(int priority, int arrival_time, int service_time){
    Queue* new_node = malloc(sizeof(Queue));
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
    free(temp);
}
void removeQueue(Queue** queue){ //removes first node from queue
    Queue * temp = (*queue);
    if(temp == NULL){
	return;
    }
    *queue = temp->next;
    free(temp);
    return;
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

/*Function Declarations*/
FEL* create_inital_node(int curr_time, int priority, float mu, float lambda);      //intializes FEL 
FEL* create_FEL_node(int curr_time, int priority, float mu, float lambda);         //creates an FEL node for mode1
void create_FEL_0(int taskNum, int priority, float mu, float lambda, FEL** list);  //generates type 0 arrival and service times  and adds to a common FEL list
void create_FEL_1(int taskNum, int priority, float mu, float lambda, FEL** list);  //generates type 1 arrival and service times  and adds to a common FEL list
Queue* create_queue_node(int priority, int arrival_time, int service_time);        //creates a queue node
void addQueue(Queue* queue_node, Queue** queue);                                   //adds a node to the queue
void remove_FEL_node(FEL** list);                                                  //removes top node from FEL
void removeQueue(Queue** queue);                                                   //removes top node from queue
int generate_random_time(float rate);                                              //generates random service times and arrival times for both types
void schedule_event(FEL* node, FEL** list);                                        //adds an arrival(node) to FEL
char * * explode(const char * str, const char * delims, int * arrLen);             //separates text file lines into three different entities (Taken from ECE264 assignment)
FEL* create_FEL_node2(int arr, int priority, int service_time);                    //creates an FEL node for mode2

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
    int service;
    FEL * arr_node;
    
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
	delim = " \r\n\t\v\f";
	length_arr = 1;
	arr_node = NULL;
	mode = 2;
	taskNum = 0;
    }
    /*Initialization of shared variables for Mode 1 and Mode 2*/
    int S = 0;
    int Q = 0;
    int time_until_free = 0;
    int queue_length = 0;
    int latest_dep_time = 0;
    int wait_time_0 = 0;
    int wait_time_1 = 0;
    int tot_wait_time_0 = 0;
    int tot_wait_time_1 = 0;
    int serverBusy = 0;
    int service_time = 0;
    int tasks = 0;
    int curr_time = 0;
    int CPU_activity = 0;
    Queue* queue_node_0 = NULL;
    Queue* queue_node_1 = NULL;
    int counter = 0;
    float CPU_util = 0;
    float avg_queue_length = 0;
    float avg_waiting_time_0 = 0;
    float avg_waiting_time_1 = 0;
    FEL* list = NULL; 
    Queue* queue_0 = NULL;
    Queue* queue_1 = NULL;
    
    /*Initial Steps needed before beginning simulation depending on the mode*/
    if (mode == 1) {
	
	/*Generates random arrival and service times for type 0 and type 1 and places it an FEL (sorted by time) */
	create_FEL_0(taskNum,0,mu,lambda0,&list);
	create_FEL_1(taskNum,1,mu,lambda1,&list);
    }
    else {                                            

	/*Reads in all the data from the text file and generates an FEL*/
	while((read = getline(&entry, &len,fp))!=-1){
	    if(read > 1){
		//printf("read:%d\n", read);
	    entry_Arr = explode(entry,delim, &length_arr);
	    arrive = atoi(entry_Arr[0]);
	    priority = atoi(entry_Arr[1]);
	    service = atoi(entry_Arr[2]);
	    
	    arr_node = create_FEL_node2(arrive, priority, service);
	    schedule_event(arr_node, &list);
	    taskNum++;

	    free(entry_Arr[0]);
	    free(entry_Arr[1]);
	    free(entry_Arr[2]);
	    if(entry_Arr != NULL){
		free(entry_Arr);
	    }
	    }
	}
	if(entry){
	    free(entry);
	}
	printf("taskNum: %d\n", taskNum);
	fclose(fp);
    }
    
    /*Actual simulation of a priority queue*/
    while((mode == 1 && tasks < (2*taskNum)) || (mode == 2 && tasks < taskNum)) {                       //Ends when total tasks have been reached. Also handles different modes
	
	/*Deals with all tasks at current time*/
	while(list != NULL && list->arrival_time == curr_time){                                       
	    if(list->priority == 0){  //adds to the type 0 queue if it is a type 0 arrival
		queue_node_0 = create_queue_node(list->priority,list->arrival_time,list->service_time);
		queue_length = queue_length + Q; //calculates queue_length
		Q = Q + 1;                       //increments current queue length  
		addQueue(queue_node_0, &queue_0);
		remove_FEL_node(&list);
	    }
	    else{ //adds to the type 1 queue if it is a type 1 arrival
		queue_node_1 = create_queue_node(list->priority,list->arrival_time,list->service_time);
		queue_length = queue_length + Q;
		Q = Q + 1;
		addQueue(queue_node_1,&queue_1);
		remove_FEL_node(&list);
	    }
	}
	
	/*Type 0 task is ready to be served*/
	if(serverBusy == 0 && queue_0 != NULL){
	    serverBusy = 1;                                  //sets server to be busy
	    service_time = queue_0->service_time;            //gets service time of task
	    CPU_activity = CPU_activity + service_time;      //running total of time CPU is servicing tasks
	    time_until_free = service_time;                  //time until servier is free
	    wait_time_0 = curr_time - queue_0->arrival_time; //gets waiting time of current task
	    tot_wait_time_0 = tot_wait_time_0 + wait_time_0; //running total of waiting time for type 0 tasks
	    Q = Q - 1;                                       //reduces current queue length, for a task is leaving the queue to be serviced  
	    removeQueue(&queue_0);
	}
	
	/*Type 1 task is ready to be served*/
	if(serverBusy == 0 && queue_0 == NULL && queue_1 != NULL){ //only serves if server is free, no type 0 tasks are waiting, and there is a task in the type 1 queue
	    serverBusy = 1;
	    service_time = queue_1->service_time;
	    CPU_activity = CPU_activity + service_time;
	    time_until_free = service_time; 
	    wait_time_1 = curr_time - queue_1->arrival_time;
	    tot_wait_time_1 = tot_wait_time_1 + wait_time_1;
	    Q = Q - 1;
	    removeQueue(&queue_1);
	}

	if(serverBusy == 1){                             //if server is currently busy
	    if(time_until_free != 0){                     
		time_until_free = time_until_free - 1;   //decrements the service time every loop simulating the server serving a task
	    }
	    else{
		printf("Error, a departure has not been completed correctly\n");
	    }
	    if(time_until_free == 0){                       //Server is done serving task and is ready to serve another
		tasks++;                                 //signifies departure of event
		serverBusy = 0;     //sets server to be free
	    }
	}
	curr_time++;               //increments current time in simulation
    }

  /*Calculations of Performance Parameters*/
    float avg_queue_length_0 = 0;
    float avg_queue_length_1 = 0;
    if(mode == 1){
	avg_queue_length = (float) queue_length /(float) (2*taskNum);
	avg_waiting_time_0 = (float)tot_wait_time_0 /(float) taskNum;
	avg_waiting_time_1 = (float)tot_wait_time_1 / (float)taskNum;
	CPU_util = (float)CPU_activity / (float)(curr_time);
    }
    if(mode == 2){
	avg_queue_length = (float) queue_length /(float) taskNum;
	avg_waiting_time_0 = (float)tot_wait_time_0 /((float) (taskNum / 2));
	avg_waiting_time_1 = (float)tot_wait_time_1 / ((float)(taskNum / 2));
        CPU_util = (float)CPU_activity / (float)(curr_time);
    }
  
  /*Outputting of Statistics to File*/
  FILE * fp_out = fopen("proj1-a_output","wb");
  fprintf(fp_out, "%f\n", avg_waiting_time_0);
  fprintf(fp_out, "%f\n", avg_waiting_time_1);
  fprintf(fp_out, "%f\n", avg_queue_length);
  fprintf(fp_out, "%f\n", CPU_util);
  fclose(fp_out);
  
  return 0;
}
