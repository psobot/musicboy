EESchema Schematic File Version 4
LIBS:cart-cache
EELAYER 26 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "STM32 Game Boy Cartridge"
Date "2018-09-22"
Rev "9"
Comp "Peter Sobot"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32F4:STM32F446ZETx U1
U 1 1 5BA71464
P 5500 2800
F 0 "U1" V 5454 -840 50  0000 R CNN
F 1 "STM32F446ZETx" V 5545 -840 50  0000 R CNN
F 2 "Package_QFP:LQFP-144_20x20mm_P0.5mm" H 4500 -600 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00141306.pdf" H 5500 2800 50  0001 C CNN
F 4 "STM32F446ZET6" V 5500 2800 50  0001 C CNN "SKU"
	1    5500 2800
	0    1    1    0   
$EndComp
$Comp
L Regulator_Linear:MIC5219-3.3 U2
U 1 1 5BA71DF4
P 8300 6050
F 0 "U2" H 8300 6392 50  0000 C CNN
F 1 "MIC5219-3.3" H 8300 6301 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 8300 6375 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/devicedoc/mic5219.pdf" H 8300 6050 50  0001 C CNN
F 4 "MIC5219YM5-TR" H 8300 6050 50  0001 C CNN "SKU"
	1    8300 6050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 5BA71EC5
P 7700 5950
F 0 "#PWR0101" H 7700 5800 50  0001 C CNN
F 1 "+5V" H 7715 6123 50  0000 C CNN
F 2 "" H 7700 5950 50  0001 C CNN
F 3 "" H 7700 5950 50  0001 C CNN
	1    7700 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 5950 8000 5950
$Comp
L power:GND #PWR0102
U 1 1 5BA71F39
P 7700 6550
F 0 "#PWR0102" H 7700 6300 50  0001 C CNN
F 1 "GND" H 7705 6377 50  0000 C CNN
F 2 "" H 7700 6550 50  0001 C CNN
F 3 "" H 7700 6550 50  0001 C CNN
	1    7700 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5BA72029
P 7700 6250
F 0 "C1" H 7815 6296 50  0000 L CNN
F 1 "1uF" H 7815 6205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7738 6100 50  0001 C CNN
F 3 "~" H 7700 6250 50  0001 C CNN
	1    7700 6250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5BA7209D
P 8000 6400
F 0 "C2" H 8115 6446 50  0000 L CNN
F 1 "100nF" H 8115 6355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 8038 6250 50  0001 C CNN
F 3 "~" H 8000 6400 50  0001 C CNN
	1    8000 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 5950 7700 6100
Connection ~ 7700 5950
Wire Wire Line
	7700 6400 7700 6550
Wire Wire Line
	8000 6550 7700 6550
Connection ~ 7700 6550
Connection ~ 8000 6550
Wire Wire Line
	8300 6550 8300 6350
Wire Wire Line
	8000 6550 8300 6550
Wire Wire Line
	8000 6250 8000 6050
Connection ~ 8000 5950
Connection ~ 8000 6050
Wire Wire Line
	8000 6050 8000 5950
$Comp
L Device:C C3
U 1 1 5BA72208
P 8700 6200
F 0 "C3" H 8815 6246 50  0000 L CNN
F 1 "470pF" H 8815 6155 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 8738 6050 50  0001 C CNN
F 3 "~" H 8700 6200 50  0001 C CNN
	1    8700 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 6550 8700 6550
Wire Wire Line
	8700 6550 8700 6350
Connection ~ 8300 6550
Wire Wire Line
	8600 6050 8700 6050
$Comp
L power:GND #PWR0104
U 1 1 5BA72DBD
P 10100 3200
F 0 "#PWR0104" H 10100 2950 50  0001 C CNN
F 1 "GND" H 10105 3027 50  0000 C CNN
F 2 "" H 10100 3200 50  0001 C CNN
F 3 "" H 10100 3200 50  0001 C CNN
	1    10100 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 3300 1650 3300
Wire Wire Line
	1650 3300 1650 3400
$Comp
L power:GND #PWR0105
U 1 1 5BA7AA89
P 1650 3400
F 0 "#PWR0105" H 1650 3150 50  0001 C CNN
F 1 "GND" H 1655 3227 50  0000 C CNN
F 2 "" H 1650 3400 50  0001 C CNN
F 3 "" H 1650 3400 50  0001 C CNN
	1    1650 3400
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Connectors:CONN_05LOCK SWDHDR1
U 1 1 5BA7B065
P 9800 1000
F 0 "SWDHDR1" H 9880 992 50  0000 L CNN
F 1 "for flashing code" H 9880 901 50  0000 L CNN
F 2 "SparkFun:1X05_LOCK" H 9800 1000 50  0001 C CNN
F 3 "~" H 9800 1000 50  0001 C CNN
	1    9800 1000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5BA7D9A2
P 9600 1200
F 0 "#PWR0106" H 9600 950 50  0001 C CNN
F 1 "GND" V 9605 1072 50  0000 R CNN
F 2 "" H 9600 1200 50  0001 C CNN
F 3 "" H 9600 1200 50  0001 C CNN
	1    9600 1200
	0    1    1    0   
$EndComp
Wire Wire Line
	9600 1100 9700 1100
Text GLabel 9600 1100 0    50   Output ~ 0
SWDCLK
Text GLabel 7400 4200 3    50   Input ~ 0
SWDCLK
Wire Wire Line
	7400 4000 7400 4200
Text GLabel 9600 1300 0    50   Output ~ 0
SWDIO
Text GLabel 7500 4200 3    50   Input ~ 0
SWDIO
Wire Wire Line
	9600 1300 9700 1300
Wire Wire Line
	7500 4000 7500 4200
Text GLabel 9600 1400 0    50   Output ~ 0
NRST
Wire Wire Line
	9600 1400 9700 1400
Text GLabel 8800 1600 1    50   Input ~ 0
NRST
$Comp
L power:GND #PWR0107
U 1 1 5BA82367
P 8500 1600
F 0 "#PWR0107" H 8500 1350 50  0001 C CNN
F 1 "GND" H 8505 1427 50  0000 C CNN
F 2 "" H 8500 1600 50  0001 C CNN
F 3 "" H 8500 1600 50  0001 C CNN
	1    8500 1600
	-1   0    0    1   
$EndComp
$Comp
L Winbond:W25Q128JVSIQ U3
U 1 1 5BA841FD
P 8900 5600
F 0 "U3" H 9425 6593 60  0000 C CNN
F 1 "W25Q128JVSIQ" H 9425 6487 60  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9400 5850 60  0001 C CNN
F 3 "" H 9400 5850 60  0001 C CNN
F 4 "Winbond" H 9550 6100 60  0001 C CNN "Manufacturer"
F 5 "128Mb" H 9425 6381 60  0000 C CNN "Value2"
F 6 "W25Q128JVSIQ" H 8900 5600 50  0001 C CNN "SKU"
	1    8900 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5BA842F1
P 10150 5400
F 0 "#PWR0108" H 10150 5150 50  0001 C CNN
F 1 "GND" V 10155 5272 50  0000 R CNN
F 2 "" H 10150 5400 50  0001 C CNN
F 3 "" H 10150 5400 50  0001 C CNN
	1    10150 5400
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR0109
U 1 1 5BA84351
P 10150 5000
F 0 "#PWR0109" H 10150 4850 50  0001 C CNN
F 1 "+3.3V" V 10165 5128 50  0000 L CNN
F 2 "" H 10150 5000 50  0001 C CNN
F 3 "" H 10150 5000 50  0001 C CNN
	1    10150 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	9600 1200 9700 1200
$Comp
L power:+3.3V #PWR0110
U 1 1 5BA85881
P 9600 1000
F 0 "#PWR0110" H 9600 850 50  0001 C CNN
F 1 "+3.3V" V 9615 1128 50  0000 L CNN
F 2 "" H 9600 1000 50  0001 C CNN
F 3 "" H 9600 1000 50  0001 C CNN
	1    9600 1000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9600 1000 9700 1000
$Comp
L SparkFun-Connectors:CONN_06LOCK SPIHDR1
U 1 1 5BA86DEF
P 9950 6450
F 0 "SPIHDR1" H 9870 5925 50  0000 C CNN
F 1 "for flashing audio" H 9870 6016 50  0000 C CNN
F 2 "SparkFun:1X06_LOCK" H 9950 6450 50  0001 C CNN
F 3 "~" H 9950 6450 50  0001 C CNN
	1    9950 6450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0111
U 1 1 5BA8BADD
P 10050 6450
F 0 "#PWR0111" H 10050 6300 50  0001 C CNN
F 1 "+3.3V" V 10065 6578 50  0000 L CNN
F 2 "" H 10050 6450 50  0001 C CNN
F 3 "" H 10050 6450 50  0001 C CNN
	1    10050 6450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5BA8BC00
P 10050 5950
F 0 "#PWR0112" H 10050 5700 50  0001 C CNN
F 1 "GND" V 10055 5822 50  0000 R CNN
F 2 "" H 10050 5950 50  0001 C CNN
F 3 "" H 10050 5950 50  0001 C CNN
	1    10050 5950
	0    -1   -1   0   
$EndComp
Text GLabel 10050 6350 2    50   Output ~ 0
SPI_CLK
Text GLabel 10050 6250 2    50   Output ~ 0
SPI_CS
Text GLabel 10050 6150 2    50   Output ~ 0
SPI_DI
Text GLabel 10050 6050 2    50   Input ~ 0
SPI_DO
Text GLabel 8700 5300 0    50   Output ~ 0
SPI_DO
Text GLabel 8700 5200 0    50   Input ~ 0
SPI_DI
Text GLabel 8700 5100 0    50   Input ~ 0
SPI_CS
Text GLabel 8700 5000 0    50   Input ~ 0
SPI_CLK
$Comp
L Device:C_Small C5
U 1 1 5BA8EC98
P 10100 3100
F 0 "C5" H 10008 3054 50  0000 R CNN
F 1 "100nF" H 10008 3145 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 10100 3100 50  0001 C CNN
F 3 "~" H 10100 3100 50  0001 C CNN
	1    10100 3100
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR0113
U 1 1 5BA900CC
P 10100 3000
F 0 "#PWR0113" H 10100 2850 50  0001 C CNN
F 1 "+3.3V" H 10115 3173 50  0000 C CNN
F 2 "" H 10100 3000 50  0001 C CNN
F 3 "" H 10100 3000 50  0001 C CNN
	1    10100 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5BA90BCA
P 9900 3650
F 0 "#PWR0114" H 9900 3400 50  0001 C CNN
F 1 "GND" H 9905 3477 50  0000 C CNN
F 2 "" H 9900 3650 50  0001 C CNN
F 3 "" H 9900 3650 50  0001 C CNN
	1    9900 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 5BA90BD0
P 9900 3550
F 0 "C4" H 9808 3504 50  0000 R CNN
F 1 "100nF" H 9808 3595 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 9900 3550 50  0001 C CNN
F 3 "~" H 9900 3550 50  0001 C CNN
	1    9900 3550
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR0115
U 1 1 5BA90BD7
P 9900 3450
F 0 "#PWR0115" H 9900 3300 50  0001 C CNN
F 1 "+3.3V" H 9915 3623 50  0000 C CNN
F 2 "" H 9900 3450 50  0001 C CNN
F 3 "" H 9900 3450 50  0001 C CNN
	1    9900 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5BA9107C
P 10100 2300
F 0 "#PWR0116" H 10100 2050 50  0001 C CNN
F 1 "GND" H 10105 2127 50  0000 C CNN
F 2 "" H 10100 2300 50  0001 C CNN
F 3 "" H 10100 2300 50  0001 C CNN
	1    10100 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C6
U 1 1 5BA91082
P 10100 2200
F 0 "C6" H 10008 2154 50  0000 R CNN
F 1 "100nF" H 10008 2245 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 10100 2200 50  0001 C CNN
F 3 "~" H 10100 2200 50  0001 C CNN
	1    10100 2200
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR0117
U 1 1 5BA91089
P 10100 2100
F 0 "#PWR0117" H 10100 1950 50  0001 C CNN
F 1 "+3.3V" H 10115 2273 50  0000 C CNN
F 2 "" H 10100 2100 50  0001 C CNN
F 3 "" H 10100 2100 50  0001 C CNN
	1    10100 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 5BA919D7
P 9900 2750
F 0 "#PWR0118" H 9900 2500 50  0001 C CNN
F 1 "GND" H 9905 2577 50  0000 C CNN
F 2 "" H 9900 2750 50  0001 C CNN
F 3 "" H 9900 2750 50  0001 C CNN
	1    9900 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C7
U 1 1 5BA919DD
P 9900 2650
F 0 "C7" H 9808 2604 50  0000 R CNN
F 1 "100nF" H 9808 2695 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 9900 2650 50  0001 C CNN
F 3 "~" H 9900 2650 50  0001 C CNN
	1    9900 2650
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR0119
U 1 1 5BA919E4
P 9900 2550
F 0 "#PWR0119" H 9900 2400 50  0001 C CNN
F 1 "+3.3V" H 9915 2723 50  0000 C CNN
F 2 "" H 9900 2550 50  0001 C CNN
F 3 "" H 9900 2550 50  0001 C CNN
	1    9900 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 2300 9100 2400
Connection ~ 9100 2400
Wire Wire Line
	9100 2400 9100 2500
Wire Wire Line
	9100 2400 9550 2400
Wire Wire Line
	9550 2400 9550 2100
Wire Wire Line
	9550 2100 10100 2100
Connection ~ 10100 2100
Wire Wire Line
	9100 2600 9100 2700
Connection ~ 9100 2700
Wire Wire Line
	9100 2700 9100 2800
Wire Wire Line
	9100 2700 9550 2700
Wire Wire Line
	9550 2700 9550 2550
Wire Wire Line
	9550 2550 9900 2550
Connection ~ 9900 2550
Wire Wire Line
	9100 2900 9100 3000
Connection ~ 9100 3000
Wire Wire Line
	9100 3000 9100 3100
Wire Wire Line
	9100 3000 10100 3000
Connection ~ 10100 3000
Wire Wire Line
	9100 3200 9100 3300
Connection ~ 9100 3300
Wire Wire Line
	9100 3300 9100 3400
Wire Wire Line
	9100 3300 9550 3300
Wire Wire Line
	9550 3300 9550 3450
Wire Wire Line
	9550 3450 9900 3450
Connection ~ 9900 3450
$Comp
L Gekkio_Connector_Specialized:GameBoy_Cartridge J1
U 1 1 5BA9D19F
P 3650 5950
F 0 "J1" V 3924 5954 50  0000 C CNN
F 1 "Game Boy GamePak Connector" V 4015 5954 50  0000 C CNN
F 2 "Gameboy:GameBoy_Cartridge_1x32_P1.50mm_Edge" H 3550 4150 50  0001 C CNN
F 3 "" H 3550 5950 50  0001 L CNN
	1    3650 5950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 5BA9D285
P 2150 5550
F 0 "#PWR0120" H 2150 5300 50  0001 C CNN
F 1 "GND" H 2155 5377 50  0000 C CNN
F 2 "" H 2150 5550 50  0001 C CNN
F 3 "" H 2150 5550 50  0001 C CNN
	1    2150 5550
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR0121
U 1 1 5BA9D2F6
P 5250 5550
F 0 "#PWR0121" H 5250 5400 50  0001 C CNN
F 1 "+5V" H 5265 5723 50  0000 C CNN
F 2 "" H 5250 5550 50  0001 C CNN
F 3 "" H 5250 5550 50  0001 C CNN
	1    5250 5550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 5BAA0E13
P 9600 4100
F 0 "R1" V 9395 4100 50  0000 C CNN
F 1 "10k" V 9486 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9640 4090 50  0001 C CNN
F 3 "~" H 9600 4100 50  0001 C CNN
	1    9600 4100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 5BAA0F8E
P 9750 4100
F 0 "#PWR0122" H 9750 3850 50  0001 C CNN
F 1 "GND" H 9755 3927 50  0000 C CNN
F 2 "" H 9750 4100 50  0001 C CNN
F 3 "" H 9750 4100 50  0001 C CNN
	1    9750 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 2400 1900 2500
Connection ~ 1900 3300
Connection ~ 1900 2500
Connection ~ 1900 2600
Wire Wire Line
	1900 2500 1900 2600
Wire Wire Line
	1900 2600 1900 2700
Connection ~ 1900 2700
Connection ~ 1900 2800
Wire Wire Line
	1900 2700 1900 2800
Wire Wire Line
	1900 2800 1900 2900
Connection ~ 1900 2900
Connection ~ 1900 3000
Wire Wire Line
	1900 2900 1900 3000
Wire Wire Line
	1900 3000 1900 3100
Connection ~ 1900 3100
Connection ~ 1900 3200
Wire Wire Line
	1900 3100 1900 3200
Wire Wire Line
	1900 3200 1900 3300
Text GLabel 2250 5300 1    50   Input ~ 0
VIN
Wire Wire Line
	2250 5300 2250 5550
Wire Wire Line
	9400 4100 9400 4300
Text GLabel 9400 4300 3    50   Output ~ 0
VIN
Wire Wire Line
	8400 4000 8400 4100
Text GLabel 4750 5550 1    50   Output ~ 0
GBADDR0
Text GLabel 4650 5550 1    50   Output ~ 0
GBADDR1
Text GLabel 4550 5550 1    50   Output ~ 0
GBADDR2
Text GLabel 4450 5550 1    50   Output ~ 0
GBADDR3
Text GLabel 4350 5550 1    50   Output ~ 0
GBADDR4
Text GLabel 4250 5550 1    50   Output ~ 0
GBADDR5
Text GLabel 4150 5550 1    50   Output ~ 0
GBADDR6
Text GLabel 4050 5550 1    50   Output ~ 0
GBADDR7
Text GLabel 3950 5550 1    50   Output ~ 0
GBADDR8
Text GLabel 3850 5550 1    50   Output ~ 0
GBADDR9
Text GLabel 3750 5550 1    50   Output ~ 0
GBADDR10
Text GLabel 3650 5550 1    50   Output ~ 0
GBADDR11
Text GLabel 3550 5550 1    50   Output ~ 0
GBADDR12
Text GLabel 3450 5550 1    50   Output ~ 0
GBADDR13
Text GLabel 3350 5550 1    50   Output ~ 0
GBADDR14
Text GLabel 3250 5550 1    50   Output ~ 0
GBADDR15
Text GLabel 3150 5550 1    50   BiDi ~ 0
GBDATA0
Text GLabel 3050 5550 1    50   BiDi ~ 0
GBDATA1
Text GLabel 2950 5550 1    50   BiDi ~ 0
GBDATA2
Text GLabel 2850 5550 1    50   BiDi ~ 0
GBDATA3
Text GLabel 2750 5550 1    50   BiDi ~ 0
GBDATA4
Text GLabel 2650 5550 1    50   BiDi ~ 0
GBDATA5
Text GLabel 2550 5550 1    50   BiDi ~ 0
GBDATA6
Text GLabel 2450 5550 1    50   BiDi ~ 0
GBDATA7
Text GLabel 2350 5550 1    50   Input ~ 0
GBRESET
Text GLabel 4950 5550 1    50   Output ~ 0
GBREAD
Text GLabel 5050 5550 1    50   Output ~ 0
GBWRITE
Text GLabel 5150 5550 1    50   Output ~ 0
GBCLK
Text GLabel 3700 4000 3    50   Input ~ 0
GBADDR0
Text GLabel 3600 4000 3    50   Input ~ 0
GBADDR1
Text GLabel 3500 4000 3    50   Input ~ 0
GBADDR2
Text GLabel 3400 4000 3    50   Input ~ 0
GBADDR3
Text GLabel 3300 4000 3    50   Input ~ 0
GBADDR4
Text GLabel 3200 4000 3    50   Input ~ 0
GBADDR5
Text GLabel 3100 4000 3    50   Input ~ 0
GBADDR6
Text GLabel 3000 4000 3    50   Input ~ 0
GBADDR7
Text GLabel 2500 4000 3    50   Input ~ 0
GBADDR12
Text GLabel 2400 4000 3    50   Input ~ 0
GBADDR13
Text GLabel 2300 4000 3    50   Input ~ 0
GBADDR14
Text GLabel 2200 4000 3    50   Input ~ 0
GBADDR15
Text GLabel 4600 4000 3    50   Input ~ 0
GBADDR8
Text GLabel 4500 4000 3    50   Input ~ 0
GBADDR9
Text GLabel 4400 4000 3    50   Input ~ 0
GBADDR10
Text GLabel 4300 4000 3    50   Input ~ 0
GBADDR11
Text GLabel 2900 1600 1    50   BiDi ~ 0
GBDATA0
Text GLabel 2800 1600 1    50   BiDi ~ 0
GBDATA1
Text GLabel 2700 1600 1    50   BiDi ~ 0
GBDATA2
Text GLabel 2600 1600 1    50   BiDi ~ 0
GBDATA3
Text GLabel 2500 1600 1    50   BiDi ~ 0
GBDATA4
Text GLabel 2400 1600 1    50   BiDi ~ 0
GBDATA5
Text GLabel 2300 1600 1    50   BiDi ~ 0
GBDATA6
Text GLabel 2200 1600 1    50   BiDi ~ 0
GBDATA7
Text GLabel 5400 4000 3    50   Input ~ 0
GBCLK
Text GLabel 5200 4000 3    50   Input ~ 0
GBREAD
Text GLabel 5100 4000 3    50   Input ~ 0
GBWRITE
Text GLabel 7100 1600 1    50   Output ~ 0
GBRESET
Wire Wire Line
	6800 4000 6800 4200
Text GLabel 6800 4200 3    50   Output ~ 0
SPI_CS
Wire Wire Line
	8300 4000 8300 4200
Wire Wire Line
	8200 4000 8200 4200
Wire Wire Line
	8100 4000 8100 4200
Text GLabel 8300 4200 3    50   Output ~ 0
SPI_CLK
Text GLabel 8200 4200 3    50   Input ~ 0
SPI_DO
Text GLabel 8100 4200 3    50   Output ~ 0
SPI_DI
Wire Wire Line
	9100 3500 9100 3400
Connection ~ 9100 3400
$Comp
L power:+3.3V #PWR0103
U 1 1 5BFFA232
P 8100 1600
F 0 "#PWR0103" H 8100 1450 50  0001 C CNN
F 1 "+3.3V" H 8115 1773 50  0000 C CNN
F 2 "" H 8100 1600 50  0001 C CNN
F 3 "" H 8100 1600 50  0001 C CNN
	1    8100 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0123
U 1 1 5BFFA630
P 8700 1400
F 0 "#PWR0123" H 8700 1250 50  0001 C CNN
F 1 "+3.3V" H 8715 1573 50  0000 C CNN
F 2 "" H 8700 1400 50  0001 C CNN
F 3 "" H 8700 1400 50  0001 C CNN
	1    8700 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 1600 8700 1400
Connection ~ 9100 2300
Wire Wire Line
	9100 2300 9100 2200
$Comp
L power:GND #PWR0124
U 1 1 5C004705
P 9150 6150
F 0 "#PWR0124" H 9150 5900 50  0001 C CNN
F 1 "GND" H 9155 5977 50  0000 C CNN
F 2 "" H 9150 6150 50  0001 C CNN
F 3 "" H 9150 6150 50  0001 C CNN
	1    9150 6150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C11
U 1 1 5C00470B
P 9150 6050
F 0 "C11" H 9058 6004 50  0000 R CNN
F 1 "2.2uF" H 9058 6095 50  0000 R CNN
F 2 "Capacitors_SMD:C_0603" H 9150 6050 50  0001 C CNN
F 3 "~" H 9150 6050 50  0001 C CNN
	1    9150 6050
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR0125
U 1 1 5C004712
P 9150 5950
F 0 "#PWR0125" H 9150 5800 50  0001 C CNN
F 1 "+3.3V" H 9165 6123 50  0000 C CNN
F 2 "" H 9150 5950 50  0001 C CNN
F 3 "" H 9150 5950 50  0001 C CNN
	1    9150 5950
	1    0    0    -1  
$EndComp
Connection ~ 9150 5950
Wire Wire Line
	8600 5950 9150 5950
$Comp
L Device:C_Small C10
U 1 1 5BFFF7AB
P 8350 950
F 0 "C10" H 8258 904 50  0000 R CNN
F 1 "2.2uF" H 8258 995 50  0000 R CNN
F 2 "Capacitors_SMD:C_0603" H 8350 950 50  0001 C CNN
F 3 "~" H 8350 950 50  0001 C CNN
	1    8350 950 
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C9
U 1 1 5BFFE642
P 8200 1200
F 0 "C9" H 8108 1154 50  0000 R CNN
F 1 "2.2uF" H 8108 1245 50  0000 R CNN
F 2 "Capacitors_SMD:C_0603" H 8200 1200 50  0001 C CNN
F 3 "~" H 8200 1200 50  0001 C CNN
	1    8200 1200
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0126
U 1 1 5C014253
P 8350 850
F 0 "#PWR0126" H 8350 600 50  0001 C CNN
F 1 "GND" H 8355 677 50  0000 C CNN
F 2 "" H 8350 850 50  0001 C CNN
F 3 "" H 8350 850 50  0001 C CNN
	1    8350 850 
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 5C0142D6
P 8200 1100
F 0 "#PWR0127" H 8200 850 50  0001 C CNN
F 1 "GND" H 8205 927 50  0000 C CNN
F 2 "" H 8200 1100 50  0001 C CNN
F 3 "" H 8200 1100 50  0001 C CNN
	1    8200 1100
	-1   0    0    1   
$EndComp
Wire Wire Line
	8200 1600 8200 1300
Wire Wire Line
	8350 1050 8350 1600
Wire Wire Line
	8350 1600 8300 1600
$Comp
L Device:CP1 CP1
U 1 1 5BAA26D0
P 9250 4100
F 0 "CP1" V 9021 4100 50  0000 C CNN
F 1 "47uF" V 9112 4100 50  0000 C CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-A_EIA-3216-18_Hand" H 9250 4100 50  0001 C CNN
F 3 "~" H 9250 4100 50  0001 C CNN
	1    9250 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9400 4100 9450 4100
Wire Wire Line
	8400 4100 9100 4100
Connection ~ 9400 4100
$EndSCHEMATC
