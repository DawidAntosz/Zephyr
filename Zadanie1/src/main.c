#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#define max_samples 5000

struct AllClocks {
	struct k_timer clock1;
	struct k_timer clock2;
	struct k_timer clock3;
};

struct timer_LogData {
	uint32_t lastLog_time1;
	uint32_t lastLog_time2;
	uint32_t lastLog_time3;
};

struct app_context {
	struct AllClocks clocks;
	struct timer_LogData logs;
};

uint32_t tab1[max_samples];
uint32_t tab1_t[max_samples];
uint32_t tab2[max_samples];
uint32_t tab2_t[max_samples];
uint32_t tab3[max_samples];
uint32_t tab3_t[max_samples];

extern void clock1_function(struct k_timer *timer_id);
extern void clock2_function(struct k_timer *timer_id);
extern void clock3_function(struct k_timer *timer_id);
volatile bool isWorking = true;

int main(void){

	struct app_context ctx;

	k_timer_init(&ctx.clocks.clock1, clock1_function, NULL);
	k_timer_init(&ctx.clocks.clock2, clock2_function, NULL);
	k_timer_init(&ctx.clocks.clock3, clock3_function, NULL);

	ctx.logs.lastLog_time1 = k_uptime_get();
	ctx.logs.lastLog_time2 = k_uptime_get();
	ctx.logs.lastLog_time3 = k_uptime_get();

	k_timer_start(&ctx.clocks.clock1, K_USEC(1000), K_USEC(1000));
	k_timer_start(&ctx.clocks.clock2, K_USEC(500), K_USEC(500));
	k_timer_start(&ctx.clocks.clock3, K_USEC(300), K_USEC(300));

	while(isWorking);
	printk("clk,period,time\r\n");
	for(int i = 0; i<max_samples;i++){
		printk("1,%llu,%llu\r\n", k_cyc_to_us_floor64(tab1[i]), k_cyc_to_us_floor64(tab1_t[i]));
		printk("2,%llu,%llu\r\n", k_cyc_to_us_floor64(tab2[i]), k_cyc_to_us_floor64(tab2_t[i]));
		printk("3,%llu,%llu\r\n", k_cyc_to_us_floor64(tab3[i]), k_cyc_to_us_floor64(tab3_t[i]));
	}

	while (1) {
	/* ===   NOTHING   === */	
	}
}


extern void clock1_function(struct k_timer *timer_id){

	struct app_context *ctx = CONTAINER_OF(timer_id, struct app_context, clocks.clock1);
	uint32_t current_time = k_cycle_get_32();
	static int i = 0;
	tab1[i] = current_time - ctx->logs.lastLog_time1;
	tab1_t[i] = current_time;
	i++;
	if(i == max_samples){
		isWorking = false;
		k_timer_stop(timer_id);
	}
	// printk("1,%d\n",current_time - ctx->logs.lastLog_time1);
	ctx->logs.lastLog_time1 = current_time;
}

extern void clock2_function(struct k_timer *timer_id){

	struct app_context *ctx = CONTAINER_OF(timer_id, struct app_context, clocks.clock2);
	uint32_t current_time = k_cycle_get_32();
	static int i = 0;
	tab2[i] = current_time - ctx->logs.lastLog_time2;
	tab2_t[i] = current_time;
	i++;
	if(i == max_samples){
		k_timer_stop(timer_id);
	}

	// printk("2,%d\n",current_time - ctx->logs.lastLog_time2);
	ctx->logs.lastLog_time2 = current_time;
}

extern void clock3_function(struct k_timer *timer_id){

	struct app_context *ctx = CONTAINER_OF(timer_id, struct app_context, clocks.clock3);
	uint32_t current_time = k_cycle_get_32();

	static int i = 0;
	tab3[i] = current_time - ctx->logs.lastLog_time3;
	tab3_t[i] = current_time;
	i++;
	if(i == max_samples){
		k_timer_stop(timer_id);
	}
	// printk("Clock 3 - Current time: %d ms\n", current_time - ctx->logs.lastLog_time3);
	// printk("3,%d\n",current_time - ctx->logs.lastLog_time3);
	ctx->logs.lastLog_time3 = current_time;
}