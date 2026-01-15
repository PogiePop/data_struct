#ifndef _WA_GRAPH_H
#define _WA_GRAPH_H
#include "object.h"

typedef struct graphnode
{
    //指向顶点的数据,用于快速访问
    Obj_ptr data;
    //标记顶点
    int tag;
    struct graphnode* next;
}graphnode;

#define  g_node graphnode*
#define g_node_ptr g_node*

typedef struct graphnodelist
{
    Obj_ptr data;
    //标记每个邻接表开头的顶点
    int tag;
    g_node head;
    //指向下一个邻接表
    struct graphnodelist* next;
}graphnodelist;

#define g_list graphnodelist*
#define g_list_ptr g_list*

typedef struct graph
{
    //邻接表
    g_list list;
    //顶点权重表
    int* vertex_weights;
    //边权重表
    int** edge_weights;

}graph;

#define wa_graph graph*
#define wa_graph_ptr wa_graph*

typedef struct edge{
    int from_tag;
    int to_tag;
    int weight;
}edge;

wa_graph create_wagraph();
g_list create_nodelist();
g_node create_graphnode();
void destory_graphnode(g_node_ptr node_ptr);
void destory_nodelist(g_list_ptr list_ptr);
void destory_wagraph(wa_graph_ptr graph_ptr);
void add_vertex(wa_graph gh, int tag, obj_type type, void* data, int weight);
void add_vertex_int(wa_graph gh, int tag, int data, int weight);
void add_vertex_float(wa_graph gh, int tag, float data, int weight);
void add_vertex_double(wa_graph gh, int tag, double data, int weight);
void add_vertex_char(wa_graph gh, int tag, char data, int weight);
void add_vertex_char_ptr(wa_graph gh, int tag, const char* data, int weight);
void del_vertex(wa_graph gh, int tag);
g_list find_vertex(wa_graph gh, int tag);
void add_edge(wa_graph gh, int from_tag, int to_tag, int weight);
void del_edge(wa_graph gh, int from_tag, int to_tag);
void wa_print_list_info(g_list list);
void wa_print_edges(wa_graph gh);
int get_vertex_num(wa_graph gh);
void wa_print_vertex_weight_table(wa_graph gh);
void wa_print_edges_weight_table(wa_graph gh);
void wa_print_edge_with_data(wa_graph gh);
void wa_print_list_info_with_data(g_list list);
int wa_prim_print(wa_graph gh);
int wa_dijkstra(wa_graph gh);

int get_vertex_num(wa_graph gh)
{
    if(!gh)return 0;
    int size = 0;
    g_list move = gh->list;
    while(move)
    {
        ++size;
        move = move->next;
    }
    return size;
}

void destory_graphnode(g_node_ptr node_ptr)
{
    if(!node_ptr || !(*node_ptr))return;
    (*node_ptr)->data = NULL;
    free(*node_ptr);
    *node_ptr = NULL;
}


g_node create_graphnode()
{
    g_node node = (g_node)malloc(sizeof(graphnode));
    node->data = NULL;
    node->next = NULL;
    node->tag = -1;
    return node;
}

g_list create_nodelist()
{
    g_list list = (g_list)malloc(sizeof(graphnodelist));
    list->head = NULL;
    list->next = NULL;
    list->data = create_object();
    list->tag = -1;
    return list;
}


wa_graph create_wagraph()
{
    wa_graph gh = (wa_graph)malloc(sizeof(graph));
    gh->vertex_weights = (int*)malloc(sizeof(int) * 10);
    memset(gh->vertex_weights, 0, sizeof(int) * 10);
    gh->edge_weights = (int**)malloc(sizeof(int*) * 10);
    for(int i = 0; i < 10; i++)
    {
        gh->edge_weights[i] = (int*)malloc(sizeof(int) * 10);
        memset(gh->edge_weights[i], 0, sizeof(int) * 10);
    }
    gh->list = NULL;
    return gh;
}

void add_vertex(wa_graph gh, int tag, obj_type type, void* data, int weight)
{
    if(!gh)return;
    SETOBJECT set_func = set_object_funcs[type];
    if(!gh->list)
    {
        gh->list = create_nodelist();
        gh->list->tag = tag;
        set_func(gh->list->data, data);
        gh->vertex_weights[tag] = weight;
        return;
    }
    g_list move = gh->list;
    while(move)
    {
        if(move->tag == tag)return;
        if(move->next == NULL)break;
        move = move->next;
    }
    move->next = create_nodelist();
    move->next->tag = tag;
    set_func(move->next->data, data);
     gh->vertex_weights[tag] = weight;
}


g_list find_vertex(wa_graph gh, int tag)
{
    if(!gh)return NULL;
    g_list move = gh->list;
    while(move)
    {
        if(move->tag == tag)return move;
        move = move->next;
    }
    return NULL;
}

void add_edge(wa_graph gh, int from_tag, int to_tag, int weight)
{
    if(!gh)return;
    g_list vh = find_vertex(gh, from_tag);
    g_list to = find_vertex(gh, to_tag);
    if(!vh || !to)return; 
    g_node v = vh->head; 
    if(!v)
    {
        vh->head = create_graphnode();
        vh->head->tag = to_tag;
        vh->head->data = to->data;
        gh->edge_weights[from_tag][to_tag] = weight;
        return;
    }
    while(v)
    {   
        if(v->tag == to_tag)return;
        if(!v->next)break;
        v = v->next;
    }
    v->next = create_graphnode();
    v->next->data = to->data;
    v->next->tag = to->tag; 
    gh->edge_weights[from_tag][to_tag] = weight;
}

void wa_print_edges(wa_graph gh)
{
    if(!gh)return;
    g_list move = gh->list;
    while(move)
    {
        wa_print_list_info(move);
        move = move->next;
    }
}


void wa_print_list_info(g_list list)
{
    if(!list)return;
    g_node v = list->head;
    printf("%d  ", list->tag);
    while(v)
    {
        printf("->%d ", v->tag);
        v = v->next;
    }
    printf("\n");
}

void del_edge(wa_graph gh, int from_tag, int to_tag)
{
    if(!gh)return;
    g_list vh = find_vertex(gh, from_tag);
    g_list to = find_vertex(gh, to_tag);
    if(!vh || !to)return; 
    g_node v = vh->head;
    g_node pre = NULL;
    while(v)
    {
        if(v->tag == to_tag)
        {
            if(!pre){
                vh->head = v->next;
            }else{
                pre->next = v->next;
            }
            destory_graphnode(&v);
            gh->edge_weights[from_tag][to_tag] = 0;
            return;
        }
        pre = v;
        v = v->next;
    }
}


void del_vertex(wa_graph gh, int tag)
{
    if(!gh)return;
    g_list move = gh->list;
    g_list pre = NULL;
    while(move)
    {
        //起点
        if(move->tag == tag)
        {
            g_list cur;
            if(!pre){
               cur = gh->list = move->next;
            }else{
               cur = pre->next = move->next;
            }
            destory_nodelist(&move);
            move = cur;
            continue;
        }else{
            g_node m = move->head;
            g_node p = NULL;
            while(m)
            {
                if(m->tag == tag)
                {
                    if(!p)move->head = m->next;
                    else p->next = m->next;
                    destory_graphnode(&m);
                    break;
                }
                p = m;
                m = m->next;
            }
        }
        pre = move;
        move = move->next;
    }
    gh->vertex_weights[tag] = 0;
}

void destory_nodelist(g_list_ptr list_ptr)
{
    if(!list_ptr || !(*list_ptr))return;
    destory_object(&(*list_ptr)->data);
    g_node move = (*list_ptr)->head;
    while(move)
    {
        g_node t = move->next;
        destory_graphnode(&move);
        move = t;
    }
    free(*list_ptr);
    *list_ptr = NULL;
}

void wa_print_vertex_weight_table(wa_graph gh)
{
    if(!gh)return;
    int size = get_vertex_num(gh);
    for(int i = 0; i < size; i++)printf("v[%d](weight) = %d\n", i, gh->vertex_weights[i]);
}
void wa_print_edges_weight_table(wa_graph gh)
{
    if(!gh)return;
    int size = get_vertex_num(gh);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("edge from v[%d] to [%d](weight) = %d\n", i, j, gh->edge_weights[i][j]);
        }
    }
}

void wa_print_list_info_with_data(g_list list)
{
    if(!list)return;
    g_node v = list->head;
    PRINT_OBJECT("%o ", list->data);
    while(v)
    {
        PRINT_OBJECT("->%o ", v->data);
        v = v->next;
    }
    printf("\n");
}

void wa_print_edge_with_data(wa_graph gh)
{
    if(!gh)return;
    g_list move = gh->list;
    while(move)
    {
        wa_print_list_info_with_data(move);
        move = move->next;
    }
}

void add_vertex_int(wa_graph gh, int tag, int data, int weight)
{
    add_vertex(gh, tag, INTEGER, &data, weight);
}
void add_vertex_float(wa_graph gh, int tag, float data, int weight)
{
    add_vertex(gh, tag, FLOAT, &data, weight);
}
void add_vertex_double(wa_graph gh, int tag, double data, int weight)
{
    add_vertex(gh, tag, DOUBLE, &data, weight);
}
void add_vertex_char(wa_graph gh, int tag, char data, int weight)
{
    add_vertex(gh, tag, CHAR, &data, weight);
}
void add_vertex_char_ptr(wa_graph gh, int tag, const char* data, int weight)
{
    add_vertex(gh, tag, STRING, (void*)data, weight);
}

int wa_prim_print(wa_graph gh)
{
    // 1. 基础空指针检查
    if (!gh)
        return 0;
    int size = get_vertex_num(gh);
    if (size <= 1)
    {
        printf("Vertex count ≤ 1, no need to generate MST\n");
        return 0;
    }

    // 2. 内存分配 + 正确初始化（核心修复）
    int* visited = (int*)malloc(sizeof(int) * size);    // 标记顶点是否被选中
    int* parent = (int*)malloc(sizeof(int) * size);     // 记录MST中顶点的父节点
    int* low_cost = (int*)malloc(sizeof(int) * size);   // 未选顶点到已选集合的最小权重
    edge* mst = (edge*)malloc(sizeof(edge) * (size - 1)); // 存储MST的边
    // 内存分配失败检查
    if (!visited || !parent || !low_cost || !mst)
    {
        printf("Memory allocation failed\n");
        free(visited);
        free(parent);
        free(low_cost);
        free(mst);
        return 0;
    }

    // 正确初始化数组（替换错误的memset）
    memset(visited, 0, sizeof(int) * size);       // visited初始化为0（未选中）
    memset(parent, -1, sizeof(int) * size);       // parent初始化为-1（无父节点）
    for (int i = 0; i < size; i++)                // low_cost初始化为INT_MAX（无穷大）
    {
        low_cost[i] = INT_MAX;
    }

    int k = 0; // MST边的计数
    visited[0] = 1; // 选tag=0作为起点

    // 3. 初始化起点（tag=0）的邻接边到low_cost和parent
    g_list list = find_vertex(gh, 0);
    if (!list) // 空指针检查：起点不存在
    {
        printf("Start vertex tag=0 does not exist\n");
        free(visited);
        free(parent);
        free(low_cost);
        free(mst);
        return 0;
    }
    g_node move = list->head;
    while (move)
    {
        int tag = move->tag;
        int weight = gh->edge_weights[0][tag];
        if (weight != 0) // 0表示不可达，仅初始化可达的边
        {
            low_cost[tag] = weight;
            parent[tag] = 0;
            printf("Initialization: tag=%d, weight=%d\n", tag, low_cost[tag]);
        }
        move = move->next;
    }

    int res = 0;
    // 4. 迭代size-1次（选size-1条边构建MST）
    for (int i = 1; i < size; i++) // 外层循环：选边次数
    {
        int mincost = INT_MAX;
        int u = -1; // 每次迭代重置u为-1（核心修复）

        // 内层循环：找low_cost最小的未选顶点u（变量名改为j，避免冲突）
        for (int j = 0; j < size; j++)
        {
            // 条件：未访问 + 可达（weight≠0） + 权重更小
            if (!visited[j] && low_cost[j] != 0 && low_cost[j] < mincost)
            {
                mincost = low_cost[j];
                u = j;
            }
        }

        // 图不连通，无法生成MST
        if (u == -1)
        {
            printf("The graph is disconnected, cannot generate MST\n");
            free(visited);
            free(parent);
            free(low_cost);
            free(mst);
            return 0;
        }

        // 将u加入已选集合，并记录到MST
        visited[u] = 1;
        res += mincost;
        mst[k++] = (edge){parent[u], u, mincost}; // 存储MST边
        printf("Selected vertex u=%d (Edge: %d->%d, weight=%d)\n", u, parent[u], u, mincost);

        // 更新未选顶点的low_cost和parent
        for (int j = 0; j < size; j++) // 变量名改为j，避免与外层i冲突
        {
            int weight = gh->edge_weights[u][j];
            printf("Check: %d->%d, weight=%d  ", u, j, weight);
            // 条件：j未访问 + 可达（weight≠0） + 权重更小
            if (!visited[j] && weight != 0 && weight < low_cost[j])
            {
                low_cost[j] = weight;
                parent[j] = u;
                printf("-> Updated: low_cost[%d]=%d, parent=%d\n", j, low_cost[j], u);
            }
            else
            {
                printf("\n");
            }
        }
    }

    // 5. 打印最终的MST父节点关系
    printf("\n=== MST Parent Node Relationship ===\n");
    for (int i = 1; i < size; i++)
    {
        if (parent[i] != -1)
        {
            printf("Vertex %d -> Parent %d (weight=%d)\n", i, parent[i], gh->edge_weights[parent[i]][i]);
        }
        else
        {
            printf("Vertex %d: No parent node (unconnected)\n", i);
        }
    }

    // 6. 打印完整的MST边列表
    printf("\n=== MST Complete Edge List ===\n");
    for (int i = 0; i < k; i++)
    {
        printf("%d -> %d, weight=%d\n", mst[i].from_tag, mst[i].to_tag, mst[i].weight);
    }

    // 7. 释放内存（核心修复：避免内存泄漏）
    free(visited);
    free(parent);
    free(low_cost);
    free(mst);

    return res;
}

int wa_dijkstra(wa_graph gh)
{
    if(!gh)return 0;
    int size = get_vertex_num(gh);
    int* dist = (int*)malloc(sizeof(int) * size);
    int* visited = (int*)malloc(sizeof(int) * size);
    int* parent = (int*)malloc(sizeof(int) * size);
    memset(dist, 0, sizeof(int) * size);
    for(int i = 1; i < size; i++)dist[i] = INT_MAX;
    memset(visited, 0, sizeof(int) * size);
    memset(parent, -1, sizeof(int) * size);
    g_list list = find_vertex(gh, 0);
    if(!list)
    {
        free(dist);
        free(visited);
        free(parent);
        return 0;
    }

    //初始化dist
    visited[0] = 1;
    g_node move = list->head;
    while(move)
    {
        int wt = gh->edge_weights[0][move->tag];
        if(wt != 0){
            dist[move->tag] = wt;
            parent[move->tag] = 0;
        }
        move = move->next;
    }

    for(int i = 1; i < size; i++)
    {
        int u = -1, mincost = INT_MAX;
        for(int j = 0; j < size; j++)
        {
            if(!visited[j] && dist[j] != INT_MAX && dist[j] < mincost)
            {
                mincost = dist[j];
                u = j;
            }
        }

        if(u == -1)
        {
            break;
        }

        visited[u] = 1;
        for(int k = 0; k < size; k++)
        {
            int wt = gh->edge_weights[u][k];
            if(!visited[k] && wt != 0 && dist[u] + wt < dist[k])
            {
                dist[k] = dist[u] + wt;
                parent[k] = u; 
            }
        }

    }

    printf("=== Dijkstra Result (Start: 0) ===\n");
    printf("Vertex\tShortest Distance\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t", i);
        if (dist[i] == INT_MAX) {
            printf("Unreachable\n");
        } else {
            printf("%d\n", dist[i]);
        }
    }

    free(dist);
    free(visited);
    free(parent);
    return 1;
}


void destory_wagraph(wa_graph_ptr graph_ptr)
{
    if(!graph_ptr && !(*graph_ptr))return;
    g_list move = (*graph_ptr)->list;
    while(move)
    {
        g_list t = move->next;
        destory_nodelist(&move);
        move = t;
    }
    free(*graph_ptr);
    *graph_ptr = NULL;
}



#endif