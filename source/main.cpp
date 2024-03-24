/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"r01lib.h"
#include	"led/PCA9955B.h"
#include	"led/PCA9957.h"
#include	"led/LED.h"
#include	<math.h>

constexpr	double	pi		= 3.14159265359;
constexpr	double	cycle	= 100;

#define	USE_PCA9955B
#ifdef	USE_PCA9955B
I2C			i2c( I2C_SDA, I2C_SCL );	//	SDA, SCL
PCA9955B	ledd( i2c );
#else
SPI			spi( D11, D12, D13, D10 );	//	MOSI, MISO, SCLK, CS
PCA9957		ledd( spi );
#endif


#ifdef	USE_PCA9955B
LED		leds[]	= {
		LED( ledd,  0 ), LED( ledd,  1 ), LED( ledd,  2 ), LED( ledd,  3 ),
		LED( ledd,  4 ), LED( ledd,  5 ), LED( ledd,  6 ), LED( ledd,  7 ),
		LED( ledd,  8 ), LED( ledd,  9 ), LED( ledd, 10 ), LED( ledd, 11 ),
		LED( ledd, 12 ), LED( ledd, 13 ), LED( ledd, 14 ), LED( ledd, 15 )
};

int main(void)
{
	PRINTF("\r***** Hello, PCA9955B! *****\r\n");
	I2C_device::scan( i2c, 124 ); //  Scan stop at 124
	ledd.begin( 1.0, PCA9955B::ARDUINO_SHIELD );

	double	sin0, sin1, sin2, white, cycle_pi;
	cycle_pi	= pi / cycle;

	int count	= 0;

	while ( true )
	{
		if ( !(count++ % 3) )
			white	= 1.0;

		for ( int i = 0; i < cycle; i++ )
		{
			sin0	= sin( (i + 0 * cycle / 3) * cycle_pi );
			sin1	= sin( (i + 1 * cycle / 3) * cycle_pi );
			sin2	= sin( (i + 2 * cycle / 3) * cycle_pi );
			leds[  0 ]	= leds[  3 ]	= leds[  6 ]	= sin0 * sin0;
			leds[  1 ]	= leds[  4 ]	= leds[  7 ]	= sin1 * sin1;
			leds[  2 ]	= leds[  5 ]	= leds[  8 ]	= sin2 * sin2;

			leds[  9 ]	= leds[ 10 ]	= leds[ 11 ]	= white;
			leds[ 12 ]	= leds[ 13 ]	= leds[ 14 ]	= white;
			leds[ 15 ]									= white;
			
			white	*= 0.9;

			wait( 0.01 );
		}
	}
}

#else  // USE_PCA9955B

LED		leds[]	= {
		LED( ledd,  0 ), LED( ledd,  1 ), LED( ledd,  2 ), LED( ledd,  3 ),
		LED( ledd,  4 ), LED( ledd,  5 ), LED( ledd,  6 ), LED( ledd,  7 ),
		LED( ledd,  8 ), LED( ledd,  9 ), LED( ledd, 10 ), LED( ledd, 11 ),
		LED( ledd, 12 ), LED( ledd, 13 ), LED( ledd, 14 ), LED( ledd, 15 ),
		LED( ledd, 16 ), LED( ledd, 17 ), LED( ledd, 18 ), LED( ledd, 19 ),
		LED( ledd, 20 ), LED( ledd, 21 ), LED( ledd, 22 ), LED( ledd, 23 )
};

int main(void)
{
	PRINTF("\r***** Hello, PCA9957! *****\r\n");
	ledd.begin( 1.0, PCA9957::ARDUINO_SHIELD );

	double	sin0, sin1, sin2, white, cycle_pi;
	cycle_pi	= pi / cycle;

	int count	= 0;

	while ( true )
	{
		if ( !(count++ % 3) )
			white	= 1.0;

		for ( int i = 0; i < cycle; i++ )
		{
			sin0	= sin( (i + 0 * cycle / 3) * cycle_pi );
			sin1	= sin( (i + 1 * cycle / 3) * cycle_pi );
			sin2	= sin( (i + 2 * cycle / 3) * cycle_pi );
			leds[  0 ]	= leds[  3 ]	= leds[  6 ]	= leds[  9 ]	= sin0 * sin0;
			leds[  1 ]	= leds[  4 ]	= leds[  7 ]	= leds[ 10 ]	= sin1 * sin1;
			leds[  2 ]	= leds[  5 ]	= leds[  8 ]	= leds[ 11 ]	= sin2 * sin2;

			leds[ 12 ]	= leds[ 13 ]	= leds[ 14 ]	= leds[ 15 ]	= white;
			leds[ 16 ]	= leds[ 17 ]	= leds[ 18 ]	= leds[ 19 ]	= white;
			leds[ 20 ]	= leds[ 21 ]	= leds[ 22 ]	= leds[ 23 ]	= white;

			white	*= 0.9;

			wait( 0.01 );
		}
	}
}

#endif // USE_PCA9955B
