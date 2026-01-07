#pragma warning (disable:4996)
#include "Header.h" 
#define _CRTDBG_MAP_ALLOC 

int ConvertToInt(char* str, int len) {               
    int result = 0;                                   
    for (int i = 0; i < len; i++) {
        result *= 10;
        if ((str[i] < 48) || (str[i] > 57)) {
            return -1;
        }
        result += ((int)str[i] - 48);
    }
    return result;
}

PathNode* RemoveFromQueue(VertexQueue* queue) {      
    if (queue->front == NULL) { return NULL; }
    PathNode* temp = queue->front;                   
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    temp->next = NULL;
    return temp;
}

void AddToQueue(PathNode* node, VertexQueue* queue) { 
    node->next = NULL;
    
    if (queue->front == NULL) {
        queue->front = node;
        queue->rear = node;
    }
    else {
        queue->rear->next = node;
        queue->rear = node;
    }
}

int* FindShortestPath(int* pathLen, GraphNode* graph, int nodes, int start, int end) { 
    if (graph == NULL || nodes <= 0 || start <= 0 || end <= 0) {
        return NULL;
    }

    VertexQueue searchQueue;                          
    VertexQueue* queuePtr = &searchQueue;            
    queuePtr->front = NULL;
    queuePtr->rear = NULL;

    PathNode* current = (PathNode*)malloc(sizeof(PathNode)); 
    int* parent = (int*)malloc(nodes * sizeof(int)); 
    int* visited = (int*)malloc(nodes * sizeof(int)); 
    
    if ((parent == NULL) || (visited == NULL) || (current == NULL)) { 
        return NULL; 
    }

    int currentNode;                                   
    *pathLen = 0;
    
    for (int i = 0; i < nodes; i++) {
        parent[i] = -1;
        visited[i] = 0;
    }
    
    current->data = graph[start-1];
    current->next = NULL;
    AddToQueue(current, queuePtr);
    visited[start - 1] = 1;
    parent[start - 1] = -1;

    while (queuePtr->front != NULL) {
        current = RemoveFromQueue(queuePtr);
        currentNode = current->data.nodeId;            

        if (currentNode == end) {
            int temp = end;                           
            *pathLen = 0;

            while (temp != -1) {
                temp = parent[temp - 1];
                (*pathLen)++;
            }

            int* path = (int*)malloc((*pathLen) * sizeof(int)); 
            if ((path == NULL)) { return NULL; }

            temp = end;
            for (int i = (*pathLen) - 1; i >= 0; i--) {
                path[i] = temp;
                temp = parent[temp-1];
            }

            free(current);
            free(parent);
            free(visited);
            return path;
        }

        for (int i = 0; i < current->data.adjCount; i++) {
            int neighbor = current->data.adjacent[i];  

            if (!visited[neighbor - 1]) {
                visited[neighbor - 1] = 1;
                parent[neighbor - 1] = currentNode;

                PathNode* newNode = (PathNode*)malloc(sizeof(PathNode)); 
                if ((newNode == NULL)) { return NULL; }

                newNode->data = graph[neighbor - 1];
                newNode->next = NULL;
                AddToQueue(newNode, queuePtr);
            }
        }
        free(current);
    }

    free(parent);
    free(visited);
    return NULL;
}

char* LoadTextFile(const char* filename, int* size) { 
    FILE* file = fopen(filename, "r");                
    char* buffer = (char*)malloc(sizeof(char));       
    char ch;                                          
    int index = 0;                                    
    
    while (fscanf(file, "%c", &ch) != EOF) {
        buffer = (char*)realloc(buffer, (index + 1) * sizeof(char));
        *(buffer + index) = ch;
        index++;
    }
    *size = index;                                   

    fclose(file);
    return buffer;
}

GraphNode* ParseGraphData(char* input, int length, int* nodeCount) { 
    if (input == NULL || length <= 0) {
        return NULL;
    }
    
    GraphNode* graph = (GraphNode*)malloc(sizeof(GraphNode)); 
    if ((graph == NULL)) { return NULL; }

    GraphNode current;                                 
    int* neighbors;                                    
    int neighborCount;                                
    char* tempStr;                                     
    int tempStrLen;                                    
    int endFlag = 0;                                   
    char* nodeStr;                                    
    int nodeStrLen = 0;                                
    int index = 0;                                     
    *nodeCount = 0;                                    

    while ((index < length) && (!endFlag)) {
        nodeStrLen = 0;
        nodeStr = (char*)malloc(sizeof(char));
        if ((nodeStr == NULL)) { return NULL; }

        while (input[index] != ':') {
            nodeStr = (char*)realloc(nodeStr, (nodeStrLen + 1) * sizeof(char));
            if ((nodeStr == NULL)) { return NULL; }

            nodeStr[nodeStrLen] = input[index];
            nodeStrLen++;
            index++;
        }

        index++; // пропускаем ':'
        if (input[index] == ' ') {
            index++;
        }

        neighbors = (int*)malloc(sizeof(int));
        if ((neighbors == NULL)) { return NULL; }
        neighborCount = 0;
        
        while (input[index] != '\n') {
            tempStr = (char*)malloc(sizeof(char));
            tempStrLen = 0;

            while ((input[index] != ' ') && (input[index] != '\n')) {
                tempStr = (char*)realloc(tempStr, (tempStrLen + 1) * sizeof(char));
                if ((tempStr == NULL)) { return NULL; }

                tempStr[tempStrLen] = input[index];
                tempStrLen++;
                index++;
                if (index >= length) { 
                    endFlag = 1;  
                    break; 
                }
            }

            neighbors = (int*)realloc(neighbors, (neighborCount + 1) * sizeof(int));
            if ((neighbors == NULL)) { return NULL; }

            neighbors[neighborCount] = ConvertToInt(tempStr, tempStrLen);
            neighborCount++;

            free(tempStr);

            if (input[index] == ' ') {
                index++;
            }
            if (endFlag) {
                break;
            }
        }

        current.adjacent = neighbors;                  
        current.adjCount = neighborCount;              

        *nodeCount = ConvertToInt(nodeStr, nodeStrLen);
        current.nodeId = *nodeCount;                   

        graph = (GraphNode*)realloc(graph, ((*nodeCount)) * sizeof(GraphNode));
        if ((graph == NULL)) { 
            return NULL; 
        }

        graph[(*nodeCount)-1] = current;
        free(nodeStr);
        index++;
    }

    return graph;
}

void FreeGraphMemory(GraphNode* graph, int count) {   
    for (int i = 0; i < count; i++) {
        free(graph[i].adjacent);
    }
    free(graph);
}

void DisplayPath(int* path, int length) {             
    if (length == 0) {
        printf("Путь не найден!");
    }
    else {
        printf("Длина = %d: ", length);
        for (int i = 0; i < length; i++) {
            if (i != length - 1) {
                printf("%d → ", path[i]);
            }
            else {
                printf("%d", path[i]);
            }
        }
        printf("\n");
    }
}

/*int main() {
    setlocale(LC_CTYPE, "Russian");
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

    const char* filename = "GraphFile.txt";           
    GraphNode* graph;                                 
    char* fileContent;                                
    int fileSize;                                     
    int nodeCount;                                    
    int* shortestPath;                                
    int pathLength;                                  
    
    fileContent = LoadTextFile(filename, &fileSize);
    graph = ParseGraphData(fileContent, fileSize, &nodeCount);
    shortestPath = FindShortestPath(&pathLength, graph, nodeCount, 1, 6);

    DisplayPath(shortestPath, pathLength);
    
    FreeGraphMemory(graph, nodeCount);
    free(shortestPath);
    free(fileContent);
    
    return 0;
}*/
