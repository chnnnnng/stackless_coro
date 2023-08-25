#include "memory.h"
#include "log.h"


typedef struct {
    void *data;
    struct mem_pool_block_t *next;
} mem_pool_block_t;


typedef struct {
    size_t block_size;
    size_t block_num;
    mem_pool_block_t *free_list;
    mem_pool_block_t *blocks;
    void *data;
} mem_pool_t;


static mem_pool_t pools[] = 
{
    //bloco_size：一个内存池的块大小，单位字节；block_num：块的个数
    //务必按照从小到达排序!
    {.block_size = 16, .block_num = 20},
    {.block_size = 32, .block_num = 100},
    {.block_size = 64, .block_num = 20},
};


static size_t pool_num = sizeof(pools)/sizeof(mem_pool_t);


static retval mem_pool_init(mem_pool_t *pool, size_t block_num, size_t block_size)
{
    if(pool && block_num && block_size)
    {
        int i;
        pool->block_size = block_size;
        pool->block_num = block_num;
        pool->free_list = NULL;
        pool->data = (void *)malloc_default((size_t)block_size*block_num);
        pool->blocks = (void *)malloc_default(sizeof(mem_pool_block_t)*block_num);
        if(pool->data == NULL || pool->blocks == NULL)
        {
            log_error("No enough memory");
            return RET_ERR;
        }
        for(i=0; i<block_num; i++)
        {
            mem_pool_block_t *block = &pool->blocks[i];
            block->data = (uint8_t *)pool->data + i*block_size;
            block->next = (struct mem_pool_block_t *) pool->free_list;
            pool->free_list = block;
        }
        return RET_OK;
    }
    else 
    {
        return RET_ERR;
    }
}


static void * mem_pool_alloc(mem_pool_t *pool)
{
    mem_pool_block_t *block;
    if (pool->free_list == NULL) {
        return NULL;
    }
    block = pool->free_list;
    pool->free_list = (mem_pool_block_t*) block->next;
    return block->data;
}


static void mem_pool_free(mem_pool_t *pool, void *data)
{
    int i;
    mem_pool_block_t *block;
    i = ((uint8_t *)data - (uint8_t *)pool->data)/pool->block_size;
    block = &pool->blocks[i];
    block->next = (struct mem_pool_block_t *) pool->free_list;
    pool->free_list = block;
}


static int mem_pool_check_belonging(mem_pool_t *pool, void *data)
{
    uint32_t base_addr = (uint32_t) pool->data;
    uint32_t p_addr = (uint32_t) data;   
    int32_t bias = p_addr - base_addr;
    if( bias >= 0 && bias < pool->block_num*pool->block_size && bias % pool->block_size == 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void memory_init(void)
{
    int i;
    for(i=0; i<pool_num; i++)
    {
        mem_pool_init(&pools[i], pools[i].block_num, pools[i].block_size);
    }
}


void * memory_alloc(size_t size)
{
    int i;
    void * p;
    for(i=0; i<pool_num; i++)
    {
        if(size <= pools[i].block_size)
        {
            p = mem_pool_alloc(&pools[i]);
            if(p != NULL)
            {
                memset(p, 0, size);
                return p;
            }
        }
    }
    return malloc_default(size);
}


void memory_free(void * ptr)
{
    if(ptr)
    {
        int i;
        for(i=0; i<pool_num; i++)
        {
            if(mem_pool_check_belonging(&pools[i], ptr))
            {
                mem_pool_free(&pools[i], ptr);
                return;
            }
        }
        free_default(ptr);
    }
}
