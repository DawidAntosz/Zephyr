#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

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

extern void clock1_function(struct k_timer *timer_id);
extern void clock2_function(struct k_timer *timer_id);
extern void clock3_function(struct k_timer *timer_id);

int main(void){

	struct app_context ctx;

	printk("Clock, current_time\r\n");

	k_timer_init(&ctx.clocks.clock1, clock1_function, NULL);
	k_timer_init(&ctx.clocks.clock2, clock2_function, NULL);
	k_timer_init(&ctx.clocks.clock3, clock3_function, NULL);

	ctx.logs.lastLog_time1 = k_uptime_get();
	ctx.logs.lastLog_time2 = k_uptime_get();
	ctx.logs.lastLog_time3 = k_uptime_get();

	k_timer_start(&ctx.clocks.clock1, K_MSEC(1000), K_MSEC(1000));
	k_timer_start(&ctx.clocks.clock2, K_MSEC(500), K_MSEC(500));
	k_timer_start(&ctx.clocks.clock3, K_MSEC(300), K_MSEC(300));


	while (1) {
	/* ===   NOTHING   === */	
	}
}


extern void clock1_function(struct k_timer *timer_id){

	struct app_context *ctx = CONTAINER_OF(timer_id, struct app_context, clocks.clock1);
	uint32_t current_time = k_uptime_get_32();

	printk("1,%d\n",current_time - ctx->logs.lastLog_time1);
	ctx->logs.lastLog_time1 = current_time;
}

extern void clock2_function(struct k_timer *timer_id){

	struct app_context *ctx = CONTAINER_OF(timer_id, struct app_context, clocks.clock2);
	uint32_t current_time = k_uptime_get_32();

	printk("2,%d\n",current_time - ctx->logs.lastLog_time2);
	ctx->logs.lastLog_time2 = current_time;
}

extern void clock3_function(struct k_timer *timer_id){

	struct app_context *ctx = CONTAINER_OF(timer_id, struct app_context, clocks.clock3);
	uint32_t current_time = k_uptime_get_32();

	// printk("Clock 3 - Current time: %d ms\n", current_time - ctx->logs.lastLog_time3);
	printk("3,%d\n",current_time - ctx->logs.lastLog_time3);
	ctx->logs.lastLog_time3 = current_time;
}