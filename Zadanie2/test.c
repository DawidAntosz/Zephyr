// void thread1_fun(void *p1, void *p2, void *p3){
// 	while(1){
// 		if (k_sem_take(p1, K_FOREVER) != 0) {
// 		printk("Input data not available!\n");
// 		} else {
// 			static int i = 0;
// 			i++;
// 			printk("%ld\n\r",i);

// 			if(i <= max_samples){
// 				uint32_t current_time = k_cycle_get_32();
// 				tab1[i] = current_time - lastLog_sem1;
// 				tab1_t[i] = current_time;

// 				lastLog_sem1 = current_time;
// 			}
// 		}	
// 	}
// }

// void thread2_fun(void *p1, void *p2, void *p3){
// 	while(1){
// 		if (k_sem_take(p1, K_FOREVER) != 0) {
// 		printk("Input data not available!\n");
// 		} else {
// 			static int i = 0;
// 			i++;
// 			printk("%ld\r\n",i);
// 			if(i <= max_samples){
// 				printk("%ld\r\n",i);
// 				uint32_t current_time = k_cycle_get_32();
// 				tab2[i] = current_time - lastLog_sem2;
// 				tab2_t[i] = current_time;

// 				lastLog_sem2 = current_time;
// 			}
// 		}	
// 	}
// }

// void thread3_fun(void *p1, void *p2, void *p3){
// 	while(1){
// 		if (k_sem_take(p1, K_FOREVER) != 0) {
// 		printk("Input data not available!\n");
// 		} else {
// 			static int i = 0;
// 			i++;
			
// 			if(i <= max_samples){
// 				uint32_t current_time = k_cycle_get_32();
// 				tab3[i] = current_time - lastLog_sem3;
// 				tab3_t[i] = current_time;

// 				lastLog_sem3 = current_time;
// 			}
// 		}	
// 	}
// }

// void thread4_fun(void *p1, void *p2, void *p3){
// 	while(1){
// 		if (k_sem_take(p1, K_FOREVER) != 0) {
// 		printk("Input data not available!\n");
// 		} else {
// 			static int i = 0;
// 			i++;
// 			if(i <= max_samples){
// 				uint32_t current_time = k_cycle_get_32();
// 				tab4[i] = current_time - lastLog_sem4;
// 				tab4_t[i] = current_time;

// 				lastLog_sem4 = current_time;
// 			}
// 		}	
// 	}
// }

// void thread5_fun(void *p1, void *p2, void *p3){
// 	while(1){
// 		if (k_sem_take(p1, K_FOREVER) != 0) {
// 		printk("Input data not available!\n");
// 		} else {
// 			static int i = 0;
// 			i++;
// 			if(i <= max_samples){
// 				uint32_t current_time = k_cycle_get_32();
// 				tab5[i] = current_time - lastLog_sem5;
// 				tab5_t[i] = current_time;

// 				lastLog_sem5 = current_time;
// 			}
// 		}	
// 	}
// }

// void thread6_fun(void *p1, void *p2, void *p3){
// 	while(1){
// 		if (k_sem_take(p1, K_FOREVER) != 0) {
// 		printk("Input data not available!\n");
// 		} else {
// 			static int i = 0;
// 			i++;
// 			if(i <= max_samples){
// 				uint32_t current_time = k_cycle_get_32();
// 				tab6[i] = current_time - lastLog_sem6;
// 				tab6_t[i] = current_time;

// 				lastLog_sem6 = current_time;
// 			}
// 			else{
// 				isWorking = false;
// 			}
// 		}	
// 	}
// }


	// k_thread_create(&thread1, thread1, STACK_SIZE, thread1_fun, &semaphore100, NULL, NULL, 0, 0, K_NO_WAIT);
    // k_thread_create(&thread2, thread2, STACK_SIZE, thread2_fun, &semaphore300, NULL, NULL, 0, 0, K_NO_WAIT);
    // k_thread_create(&thread3, thread3, STACK_SIZE, thread3_fun, &semaphore500, NULL, NULL, 0, 0, K_NO_WAIT);
    // k_thread_create(&thread4, thread4, STACK_SIZE, thread4_fun, &semaphore1000, NULL, NULL, 0, 0, K_NO_WAIT);
    // k_thread_create(&thread5, thread5, STACK_SIZE, thread5_fun, &semaphore2000, NULL, NULL, 0, 0, K_NO_WAIT);
    // k_thread_create(&thread6, thread6, STACK_SIZE, thread6_fun, &semaphore5000, NULL, NULL, 0, 0, K_NO_WAIT);