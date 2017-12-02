#Byggscript för att skicka temp o fuktvärden till IoTCS
export IOTCS_OS_NAME="Raspbian GNU/Linux"
export IOTCS_OS_VERSION="8"
gcc -g -I../include -I../lib/arm -I./dht ./dht/pi_2_dht_read.c ./dht/common_dht_read.c ./dht/pi_2_mmio.c test_sensor.c -o test_sensor.out -Wl,-Bstatic -L../lib/arm -ldeviceclient -Wl,-Bdynamic -lssl -lcrypto -lm -lrt -lpthread