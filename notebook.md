# Notebook
## Interrupt
### 中断流程
1. 保存现场
2. rt_interrupt_enter，通知内核进中断了
3. 中断处理函数
4. rt_interrupt_leave，通知内核出中断了
5. 恢复现场
### functions about enter and leave interrupt
`rt_interrupt_nest` is a global variable, 标志了中断嵌套层数

进中断
```c
void rt_interrupt_enter(void)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    rt_interrupt_nest ++;
    rt_hw_interrupt_enable(level);
}
```
出中断
```c
void rt_interrupt_leave(void)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    rt_interrupt_nest --;
    rt_hw_interrupt_enable(level);
}
```
挂载中断服务程序，将handler和vector关联起来
```c
rt_isr_handler_t rt_hw_interrupt_install(int vector,
                                        rt_isr_handler_t handler,
                                        void *param,
                                        char *name);
```
屏蔽中断和解除屏蔽
```c
void rt_hw_interrupt_mask(int vector);
void rt_hw_interrupt_umask(int vector);
```
全局中断锁和中断恢复
```c
rt_base_t rt_hw_interrupt_disable(void);
// 返回值是关中断前的中断状态

void rt_hw_interrupt_enable(rt_base_t level);
// 恢复调用rt_hw_interrupt_disable()函数前的中断状态
```