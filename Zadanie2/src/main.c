#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#define STACK_SIZE 1024

struct k_sem SemVar;


struct k_timer timer;



extern void timer_function(struct k_timer *timer_id){

	static int cnt = 0;

	if(cnt % 3 == 0){
		k_sem_give(&semaphores[2]);
	}
	

	current_semaphore = (current_semaphore + 1) % 6;
}




void thread_entry(void *, void *, void *){

while (1){
	
	
	}
}




int main(void){


	k_timer_init(&timer, timer_function, NULL);

	// define threads


	k_thread_create(&thread_entry,
                    K_THREAD_STACK_DEFINE(thread_stack, STACK_SIZE),
                    STACK_SIZE,
                    thread_entry,
                    INT_TO_POINTER(0),
                    NULL, NULL,
                    PRIORITY_BASE + 0,
                    0, K_NO_WAIT);




	k_timer_start(&timer, K_USEC(100), K_USEC(100));

}
