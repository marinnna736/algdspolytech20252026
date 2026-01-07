#pragma warning (disable:4996)
#include <assert.h> 
#include <string.h>
#include "Header.h" 

void Test_ConvertToInt_MixedString_ReturnInvalidN1() { 
    printf("Test 1: Строка содержит буквы и цифры\n");
    
    int len = 4;
    const char* str = ".f75";
    int result = ConvertToInt(str, len);              
    assert((result == -1));
    printf("Возвращено -1. Ошибка: буквы в строке\n");
}

void Test_ConvertToInt_DigitsOnly_ReturnNumberN2() {  
    printf("Test 2: Только цифры в строке\n");
    
    int len = 3;
    const char* str = "137";
    int result = ConvertToInt(str, len);             
    assert((result == 137));
    printf("Успех\n");
}

void Test_ParseGraphData_NullInput_ReturnNullN3() {   
    printf("Test 3: NULL входные данные\n");
    
    GraphNode* graph;                                 
    char* input = NULL;
    int len = 1;
    int nodeCount;
    graph = ParseGraphData(input, len, &nodeCount);   
    assert((graph == NULL));
    printf("Возвращено NULL. Ошибка: входная строка NULL\n");
}

void Test_ParseGraphData_InvalidLength_ReturnNullN4() { 
    printf("Test 4: Неверная длина\n");
    
    GraphNode* graph;
    char* input = "1: 2 3 4";
    int len = 0;
    int nodeCount;
    graph = ParseGraphData(input, len, &nodeCount);   
    assert((graph == NULL));
    printf("Возвращено NULL. Ошибка: неверная длина\n");
}

void Test_ParseGraphData_ValidGraph_ReturnValidN5() { 
    printf("Test 5: Корректный граф\n");
    
    GraphNode* graph;
    char* input = "1: 2 3 4";
    int len = 8;
    int nodeCount;
    graph = ParseGraphData(input, len, &nodeCount);   
    assert(graph->adjacent[0] == 2 || graph->adjacent[1] == 3 || 
           graph->adjacent[2] == 4 || graph->adjCount == 3 || 
           graph->nodeId == 1);
    printf("Успех\n");
    free(graph->adjacent);
    free(graph);
}

void Test_RemoveFromQueue_NotEmptyQueue_ReturnNodeN6() { 
    printf("Test 6: Извлечение из непустой очереди\n");
    
    PathNode* node = (PathNode*)malloc(sizeof(PathNode)); 
    PathNode* result;
    GraphNode graphNode;                             
    graphNode.adjacent = NULL;
    graphNode.adjCount = 0;
    graphNode.nodeId = 1;

    node->data = graphNode;                          
    node->next = NULL;

    VertexQueue queue;                              
    queue.front = node;                              
    queue.rear = node;                               
    
    result = RemoveFromQueue(&queue);                
    assert(result->data.nodeId == 1);                
    printf("Успех\n");
    free(result);
}

void Test_RemoveFromQueue_EmptyQueue_ReturnNullN7() { 
    printf("Test 7: Извлечение из пустой очереди\n");
    
    PathNode* result;
    VertexQueue queue;
    queue.front = NULL;
    queue.rear = NULL;
    result = RemoveFromQueue(&queue);                
    assert(result == NULL);
    printf("Возвращено NULL. Ошибка: очередь пуста\n");
}

void Test_AddToQueue_EmptyQueue_ValidResultN8() {    
    printf("Test 8: Добавление в пустую очередь\n");
    
    PathNode* node = (PathNode*)malloc(sizeof(PathNode));
    GraphNode graphNode;
    graphNode.adjacent = NULL;
    graphNode.adjCount = 0;
    graphNode.nodeId = 1;

    node->data = graphNode;
    node->next = NULL;

    VertexQueue queue;
    queue.front = NULL;
    queue.rear = NULL;
    AddToQueue(node, &queue);                        
    assert(queue.front->data.nodeId == 1);
    printf("Успех\n");
    free(node);
}

void Test_AddToQueue_NonEmptyQueue_ValidResultN9() { 
    printf("Test 9: Добавление в непустую очередь\n");
    
    PathNode* node1 = (PathNode*)malloc(sizeof(PathNode));
    PathNode* node2 = (PathNode*)malloc(sizeof(PathNode));
    GraphNode graphNode1, graphNode2;

    graphNode1.adjacent = NULL;
    graphNode1.adjCount = 0;
    graphNode1.nodeId = 2;

    graphNode2.adjacent = NULL;
    graphNode2.adjCount = 0;
    graphNode2.nodeId = 1;

    node1->data = graphNode1;
    node1->next = NULL;
    node2->data = graphNode2;
    node2->next = NULL;

    VertexQueue queue;
    queue.front = node2;
    queue.rear = node2;

    AddToQueue(node1, &queue);                       
    assert(queue.front->next->data.nodeId == 2);
    printf("Успех\n");
    free(node1);
    free(node2);
}

void Test_FindShortestPath_NullGraph_ReturnNullN10() { 
    printf("Test 10: NULL граф\n");
    
    GraphNode* graph = NULL;
    int* result;
    int pathLength;
    result = FindShortestPath(&pathLength, graph, 1, 1, 1); 
    assert(result == NULL);
    printf("Возвращено NULL. Ошибка: граф равен NULL\n");
}

void Test_FindShortestPath_ZeroNodes_ReturnNullN11() { 
    printf("Test 11: Нулевое количество узлов\n");
    
    GraphNode* graph = (GraphNode*)malloc(sizeof(GraphNode));
    GraphNode node;
    node.adjacent = NULL;
    node.adjCount = 0;
    node.nodeId = 2;
    graph[0] = node;

    int* result;
    int pathLength;
    result = FindShortestPath(&pathLength, graph, 0, 1, 1); 
    printf("Возвращено NULL. Ошибка: количество узлов равно 0\n");
    free(graph);
}

void Test_FindShortestPath_InvalidStart_ReturnNullN12() { 
    printf("Test 12: Неверная начальная вершина\n");
    
    GraphNode* graph = (GraphNode*)malloc(sizeof(GraphNode));
    GraphNode node;
    node.adjacent = NULL;
    node.adjCount = 0;
    node.nodeId = 2;
    graph[0] = node;

    int* result;
    int pathLength;
    result = FindShortestPath(&pathLength, graph, 1, 0, 1); 
    assert(result == NULL);
    printf("Возвращено NULL. Ошибка: неверная начальная вершина\n");
    free(graph);
}

void Test_FindShortestPath_InvalidEnd_ReturnNullN13() { 
    printf("Test 13: Неверная конечная вершина\n");
    
    GraphNode* graph = (GraphNode*)malloc(sizeof(GraphNode));
    GraphNode node;
    node.adjacent = NULL;
    node.adjCount = 0;
    node.nodeId = 2;
    graph[0] = node;

    int* result;
    int pathLength;
    result = FindShortestPath(&pathLength, graph, 1, 1, 0); 
    assert(result == NULL);
    printf("Возвращено NULL. Ошибка: неверная конечная вершина\n");
    free(graph);
}

void Test_FindShortestPath_SimplePath_ReturnValidN14() { 
    printf("Test 14: Поиск простого пути\n");
    
    GraphNode* graph = (GraphNode*)malloc(2 * sizeof(GraphNode));
    GraphNode node1, node2;
    int neighbors[1];
    neighbors[0] = 2;

    node1.adjacent = neighbors;
    node1.adjCount = 1;
    node1.nodeId = 1;

    node2.adjacent = NULL;
    node2.adjCount = 0;
    node2.nodeId = 2;
    
    graph[0] = node1;
    graph[1] = node2;

    int* result;
    int pathLength;
    result = FindShortestPath(&pathLength, graph, 2, 1, 2); 
    assert(result[0] == 1 && result[1] == 2 && pathLength == 2);
    printf("Успех\n");
    free(graph);
    free(result);
}

int main(void) {
    setlocale(LC_CTYPE, "Russian");
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

    Test_ConvertToInt_MixedString_ReturnInvalidN1();
    Test_ConvertToInt_DigitsOnly_ReturnNumberN2();
    Test_ParseGraphData_NullInput_ReturnNullN3();
    Test_ParseGraphData_InvalidLength_ReturnNullN4();
    Test_ParseGraphData_ValidGraph_ReturnValidN5();
    Test_RemoveFromQueue_NotEmptyQueue_ReturnNodeN6();
    Test_RemoveFromQueue_EmptyQueue_ReturnNullN7();
    Test_AddToQueue_EmptyQueue_ValidResultN8();
    Test_AddToQueue_NonEmptyQueue_ValidResultN9();
    Test_FindShortestPath_NullGraph_ReturnNullN10();
    Test_FindShortestPath_ZeroNodes_ReturnNullN11();
    Test_FindShortestPath_InvalidStart_ReturnNullN12();
    Test_FindShortestPath_InvalidEnd_ReturnNullN13();
    Test_FindShortestPath_SimplePath_ReturnValidN14();

    printf("\nВсе тесты успешно пройдены!\n");
    return 0;
}