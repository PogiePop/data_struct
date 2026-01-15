#include <stdio.h>
#include "tools/object.h"
#include "tools/arraylist.h"
#include "tools/linklist.h"
#include "tools/stack.h"
#include "tools/queue.h"
#include "tools/wamath.h"
#include "tools/wastring.h"
#include "tools/tree.h"
#include "tools/graph.h"
#define str(x) #x


int main()
{
  // 1. 创建空的加权图
    wa_graph gh = create_wagraph();
    if (!gh) {
        printf("Failed to create weighted graph!\n");
        return -1;
    }

    // 2. 添加顶点（共7个顶点，覆盖0-6，参数严格匹配：gh, tag, data, weight）
    // 格式：add_vertex_int(图指针, 顶点tag, 顶点数据, 顶点权重)
    add_vertex_int(gh, 0, 1, 1);   // 顶点0：tag=0，data=1，权重=1
    add_vertex_int(gh, 1, 9, 1);   // 顶点1：tag=1，data=9，权重=1
    add_vertex_int(gh, 2, 6, 2);   // 顶点2：tag=2，data=6，权重=2
    add_vertex_int(gh, 3, 4, 1);   // 顶点3：tag=3，data=4，权重=1
    add_vertex_int(gh, 4, 8, 2);   // 顶点4：tag=4，data=8，权重=2
    add_vertex_int(gh, 5, 3, 1);   // 顶点5：tag=5，data=3，权重=1
    add_vertex_int(gh, 6, 7, 2);   // 顶点6：tag=6，data=7，权重=2（不可达顶点）

    // 3. 添加有向带权边（覆盖核心测试场景，参数严格匹配：gh, from_tag, to_tag, weight）
    // 格式：add_edge(图指针, 起点tag, 终点tag, 边权重)
    
    // 场景1：基础最短路径链（0→1→2→4→5）
    add_edge(gh, 0, 1, 2);  // 0→1，边权重=2
    add_edge(gh, 1, 2, 1);  // 1→2，边权重=1
    add_edge(gh, 2, 4, 3);  // 2→4，边权重=3
    add_edge(gh, 4, 5, 2);  // 4→5，边权重=2

    // 场景2：备选路径（验证算法选最优）
    add_edge(gh, 0, 3, 5);  // 0→3，边权重=5
    add_edge(gh, 3, 1, 1);  // 3→1，边权重=1（0→3→1总权重6 > 0→1的2）
    add_edge(gh, 3, 5, 4);  // 3→5，边权重=4（0→3→5总权重9）

    // 场景3：环结构（验证算法不陷入死循环）
    add_edge(gh, 1, 0, 1);  // 1→0，边权重=1（0→1→0环）
    add_edge(gh, 2, 1, 2);  // 2→1，边权重=2（1→2→1环）

    // 场景4：大权重直接边（验证路径选择）
    add_edge(gh, 0, 5, 15); // 0→5，边权重=15（远大于间接路径）
    add_edge(gh, 2, 5, 9);  // 2→5，边权重=9（0→1→2→5总权重12）

    // 场景5：孤立顶点（验证不可达处理）
    // 顶点6无任何入/出边，无需添加edge

    // 4. 执行Dijkstra算法（起点固定为0）
    printf("Dijkstra algorithm execution result (1=success, 0=failed): %d\n", wa_dijkstra(gh));

    // 5. 释放图内存（需补充你的图销毁函数）
     destory_wagraph(&gh);

    return 0;
}