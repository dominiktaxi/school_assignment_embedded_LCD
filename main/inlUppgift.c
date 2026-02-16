#include <stdio.h>
#include "lcd-screen.h"

#include "driver/gpio.h"
#include "driver/i2c.h"

#include "application.h"

#define SDA GPIO_NUM_5
#define SCL GPIO_NUM_4 // (SCL)



void app_main(void)
{
   Application app;
   application_init(&app);
   add_company(&app, "akalle");
   add_company(&app, "pelle");
   add_company(&app, "fisk");
   add_company(&app, "abraham");

   sort(&app);
   list_companies(&app);
   list_indexes(&app);
}


//#define I2C_PORT I2C_NUM_0
// static void i2c_master_init(void)
// {
//     i2c_config_t conf =
//     {
//         .mode = I2C_MODE_MASTER,
//         .sda_io_num = SDA,
//         .scl_io_num = SCL,
//         .sda_pullup_en = GPIO_PULLUP_ENABLE,
//         .scl_pullup_en = GPIO_PULLUP_ENABLE,
//         .master.clk_speed = FREQ_HZ
//     };
//     i2c_param_config(I2C_PORT, &conf);
//     i2c_driver_install(I2C_PORT, conf.mode, 0, 0, 0);
// }

// static esp_err_t i2c_probe(uint8_t addr7)
// {
//     void* cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);

//     // address byte = (7-bit address << 1) | R/W
//     // R/W = 0 for write (typical for probing)
//     i2c_master_write_byte(cmd, (addr7 << 1) | 0, true);

//     i2c_master_stop(cmd);

//     esp_err_t err = i2c_master_cmd_begin(I2C_PORT, cmd, pdMS_TO_TICKS(100));
//     i2c_cmd_link_delete(cmd);
//     return err;
// }

