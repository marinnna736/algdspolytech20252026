#pragma once

#include <math.h> 
#include <locale.h> 
#include <malloc.h> 
#include <stdlib.h> 
#include <crtdbg.h> 


typedef struct {
    int* adjacent;          
    int adjCount;           
    int nodeId;             
} GraphNode;

typedef struct PathNode {
    GraphNode data;         
    struct PathNode* next;  
} PathNode;

typedef struct {
    PathNode* front;        
    PathNode* rear;        
} VertexQueue;

int ConvertToInt(char* str, int len);                
PathNode* RemoveFromQueue(VertexQueue* queue);       
void AddToQueue(PathNode* node, VertexQueue* queue); 
int* FindShortestPath(int* pathLen, GraphNode* graph, int nodes, int start, int end); 
GraphNode* ParseGraphData(char* input, int length, int* nodeCount); 
void FreeGraphMemory(GraphNode* graph, int count);   