# ESPHome devices [![CI](https://github.com/DanNixon/esphome_devices/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/DanNixon/esphome_devices/actions/workflows/ci.yml)

Configuration, code and CAD for custom smarthome devices, powered by [ESPHome](https://esphome.io/).

## Boards

|Board|Module|SoC|Buy|Notes|
|-----|------|---|---|-----|
|[LILYGO T-Internet POE](https://www.lilygo.cc/products/t-internet-poe)|[ESP32-WROOM-32E](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32e_esp32-wroom-32ue_datasheet_en.pdf)|[ESP32-D0WD-V3](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)|[AliExpress](https://www.aliexpress.com/item/4001122992446.html)||
|DOIT ESP32 DevKit USB-C|[ESP32-WROOM-32](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf)|[ESP32-D0WDQ6](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)|[AliExpress](https://www.aliexpress.com/item/1005005495948290.html)||
|WeMos D1 Mini|TODO|[ESP8266](https://www.espressif.com/sites/default/files/documentation/esp8266-technical_reference_en.pdf)|TODO||

## Peripherals

|Type|Part|ESPHome|Buy|Notes|
|----|----|-------|---|-----|
|Temperature sensor|DS18B20|[`dallas`](https://esphome.io/components/sensor/dallas)|[AliExpress](https://www.aliexpress.com/item/1783091649.html)||
|VOC and NOx sensor|SGP41|[`sgp4x`](https://esphome.io/components/sensor/sgp4x)|[AliExpress](https://www.aliexpress.com/item/4000037083952.html)||
|CO2 sensor|SenseAir S8|[`senseair`](https://esphome.io/components/sensor/senseair)|[AliExpress](https://www.aliexpress.com/item/1005004123170360.html)|[datasheet](https://rmtplusstoragesenseair.blob.core.windows.net/docs/publicerat/PSP107.pdf)|
|Particulate matter sensor|PMS5003|[`pmsx003`](https://esphome.io/components/sensor/pmsx003)|[AliExpress](https://www.aliexpress.com/item/32944660534.html)||
|Temperature and humidity sensor|AHT20|[`aht10`](https://esphome.io/components/sensor/aht10)|[AliExpress](https://www.aliexpress.com/item/4000052449080.html)||
|Light sensor|BH1750|[`bh1750`](https://esphome.io/components/sensor/bh1750)|[AliExpress](https://www.aliexpress.com/item/1005001621873442.html)||
|IO expander|SX1509|[`sx1509`](https://esphome.io/components/sx1509)|[AliExpress](https://www.aliexpress.com/item/1005003891847975.html)||
