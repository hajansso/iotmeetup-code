#include <stdio.h>
#include <unistd.h>
#include "pi_2_dht_read.h"


int main()
{
	printf("Reading sensor\n");
	
	float humidity = 0, temperature = 0;
	
	while (1)
	{
	// int result = pi_2_dht_read(sensortype, pin, &humidity, &temperature);
		int result = pi_2_dht_read(22, 4, &humidity, &temperature);

		printf("result = %i, humidity = %2.2f, temperature= %2.2f\n", result, humidity, temperature);
		
		sleep(5);
	}
	
	return 0;
}