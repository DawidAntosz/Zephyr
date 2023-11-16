User
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#define STACK_SIZE 1024
#define max_samples 250

K_SEM_DEFINE(semaphore100, 0, 1);
K_SEM_DEFINE(semaphore300, 0, 1);
K_SEM_DEFINE(semaphore500, 0, 1);
K_SEM_DEFINE(semaphore1000, 0, 1);
K_SEM_DEFINE(semaphore2000, 0, 1);
K_SEM_DEFINE(semaphore5000, 0, 1);

K_THREAD_STACK_DEFINE(thread1, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread2, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread3, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread4, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread5, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread6, STACK_SIZE);

uint32_t tab1[max_samples];
uint32_t tab2[max_samples];
uint32_t tab3[max_samples];
uint32_t tab4[max_samples];
uint32_t tab5[max_samples];
uint32_t tab6[max_samples];

uint32_t tab1_t[max_samples];
uint32_t tab2_t[max_samples];
uint32_t tab3_t[max_samples];
uint32_t tab4_t[max_samples];
uint32_t tab5_t[max_samples];
uint32_t tab6_t[max_samples];

uint32_t lastLog_sem1 = 0;
uint32_t lastLog_sem2 = 0;
uint32_t lastLog_sem3 = 0;
uint32_t lastLog_sem4 = 0;
uint32_t lastLog_sem5 = 0;
uint32_t lastLog_sem6 = 0;

volatile bool isWorking = true;


struct k_timer timer;

extern void timer_function(struct k_timer *timer_id){
	static int cnt_us = 0;
	cnt_us ++;
	if (cnt_us > INT_MAX - 1){cnt_us = 0;}

	if (cnt_us%1 == 0){k_sem_give(&semaphore100);}
	if (cnt_us%3 == 0){k_sem_give(&semaphore300);}
	if (cnt_us%5 == 0){k_sem_give(&semaphore500);}
	if (cnt_us%10 == 0){k_sem_give(&semaphore1000);}
	if (cnt_us%20 == 0){k_sem_give(&semaphore2000);}
	if (cnt_us%50 == 0){
		k_sem_give(&semaphore5000);
		cnt_us = 0;	
	}

	if(isWorking == false){
		k_timer_stop(timer_id);
	}
}

K_TIMER_DEFINE(timer, timer_function, NULL);


void thread_fun1(void *semaphore, uint32_t *tab, uint32_t *tab_t, uint32_t *lastLog) {
    
	static __thread int i = 0;
	printk("Thread 1");
	while (1) {
		if (k_sem_take(semaphore, K_FOREVER) != 0) {
            printk("Input data not available!\n");
        } 
		else {
			if(i < max_samples){
				i++;
				printk("%d\n\r",i);
				uint32_t current_time = k_cycle_get_32();
				tab[i] = current_time - *lastLog;
				tab_t[i] = current_time;
				*lastLog = current_time;
			}
        }
    }
}

void thread_fun2(void *semaphore, uint32_t *tab, uint32_t *tab_t, uint32_t *lastLog) {
    
	static __thread int i = 0;
	printk("Thread 2");
	while (1) {
		if (k_sem_take(semaphore, K_FOREVER) != 0) {
            printk("Input data not available!\n");
        } 
		else {

			if(i < max_samples){
				i++;
				printk("%d\n\r",i);
				uint32_t current_time = k_cycle_get_32();
				tab[i] = current_time - *lastLog;
				tab_t[i] = current_time;
				*lastLog = current_time;
			}
        }
    }
}


int main(void){

	lastLog_sem1 = k_uptime_get();
	lastLog_sem2 = k_uptime_get();
	lastLog_sem3 = k_uptime_get();
	lastLog_sem4 = k_uptime_get();
	lastLog_sem5 = k_uptime_get();
	lastLog_sem6 = k_uptime_get();


	k_timer_start(&timer, K_USEC(100), K_USEC(100));


	k_thread_create(&thread1, thread1, STACK_SIZE, thread_fun1, &semaphore100, tab1, tab1_t, &lastLog_sem1, 0, K_NO_WAIT);
    k_thread_create(&thread2, thread2, STACK_SIZE, thread_fun2, &semaphore300, tab2, tab2_t, &lastLog_sem2, 0, K_NO_WAIT);
    // k_thread_create(&thread3, thread3, STACK_SIZE, thread_fun3, &semaphore500, tab3, tab3_t, &lastLog_sem3, 0, K_NO_WAIT);
    // k_thread_create(&thread4, thread4, STACK_SIZE, thread_fun4, &semaphore1000, tab4, tab4_t, &lastLog_sem4, 0, K_NO_WAIT);
    // k_thread_create(&thread5, thread5, STACK_SIZE, thread_fun5, &semaphore2000, tab5, tab5_t, &lastLog_sem5, 0, K_NO_WAIT);
    // k_thread_create(&thread6, thread6, STACK_SIZE, thread_fun6, &semaphore5000, tab6, tab6_t, &lastLog_sem6, 0, K_NO_WAIT);


    k_thread_start(&thread1);
    k_thread_start(&thread2);
    // k_thread_start(&thread3);
    // k_thread_start(&thread4);
    // k_thread_start(&thread5);
    // k_thread_start(&thread6);



	while(isWorking);

	printk("clk,period,time\r\n");
	for(int i = 0; i<max_samples;i++){
		printk("1,%llu,%llu\r\n", k_cyc_to_us_floor64(tab1[i]), k_cyc_to_us_floor64(tab1_t[i]));
		printk("2,%llu,%llu\r\n", k_cyc_to_us_floor64(tab2[i]), k_cyc_to_us_floor64(tab2_t[i]));
		// printk("3,%llu,%llu\r\n", k_cyc_to_us_floor64(tab3[i]), k_cyc_to_us_floor64(tab3_t[i]));
		// printk("4,%llu,%llu\r\n", k_cyc_to_us_floor64(tab4[i]), k_cyc_to_us_floor64(tab4_t[i]));
		// printk("5,%llu,%llu\r\n", k_cyc_to_us_floor64(tab5[i]), k_cyc_to_us_floor64(tab5_t[i]));
		// printk("6,%llu,%llu\r\n", k_cyc_to_us_floor64(tab6[i]), k_cyc_to_us_floor64(tab6_t[i]));
	}

	while(1) {
		k_sleep(K_MSEC(500));
    }
}