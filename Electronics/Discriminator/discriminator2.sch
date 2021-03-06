EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:discriminator2-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCP6562 U1
U 1 1 5926BCD2
P 5250 3450
F 0 "U1" H 5400 3750 50  0000 L CNN
F 1 "LTC6702" H 5450 3650 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 5250 3050 50  0001 C CNN
F 3 "" H 5250 3450 50  0001 C CNN
	1    5250 3450
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR2
U 1 1 5926C183
P 5150 3950
F 0 "#PWR2" H 5150 3700 50  0001 C CNN
F 1 "GNDREF" H 5155 3777 50  0000 C CNN
F 2 "" H 5150 3950 50  0001 C CNN
F 3 "" H 5150 3950 50  0001 C CNN
	1    5150 3950
	1    0    0    -1  
$EndComp
$Comp
L VPP #PWR1
U 1 1 5926C5BD
P 5150 1950
F 0 "#PWR1" H 5150 1800 50  0001 C CNN
F 1 "VPP" H 5165 2123 50  0000 C CNN
F 2 "" H 5150 1950 50  0001 C CNN
F 3 "" H 5150 1950 50  0001 C CNN
	1    5150 1950
	1    0    0    -1  
$EndComp
Text Notes 1350 6550 0    60   ~ 0
Window\nLower edge ranges from 0V to 0.33*2.5\nUpper edge ranges from 0V to 0.66*2.5
$Comp
L C C2
U 1 1 5926C967
P 5450 2350
F 0 "C2" H 5565 2396 50  0000 L CNN
F 1 "0.1u" H 5565 2305 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-A_EIA-3216-18_Hand" H 5488 2200 50  0001 C CNN
F 3 "" H 5450 2350 50  0001 C CNN
	1    5450 2350
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5926C9AF
P 5850 2350
F 0 "C3" H 5965 2396 50  0000 L CNN
F 1 "10u" H 5965 2305 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-A_EIA-3216-18_Hand" H 5888 2200 50  0001 C CNN
F 3 "" H 5850 2350 50  0001 C CNN
	1    5850 2350
	1    0    0    -1  
$EndComp
$Comp
L MAX874 U2
U 1 1 5926CB66
P 1650 4350
F 0 "U2" H 1650 4715 50  0000 C CNN
F 1 "MAX6029-2.5V" H 1650 4624 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 1650 4350 50  0001 C CNN
F 3 "" H 1650 4350 50  0001 C CNN
	1    1650 4350
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5926CD6B
P 2550 4250
F 0 "R1" H 2480 4204 50  0000 R CNN
F 1 "100k" H 2480 4295 50  0000 R CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2480 4250 50  0001 C CNN
F 3 "" H 2550 4250 50  0001 C CNN
	1    2550 4250
	-1   0    0    1   
$EndComp
$Comp
L POT_TRIM RV2
U 1 1 5926D3E3
P 2800 4850
F 0 "RV2" H 2730 4896 50  0000 R CNN
F 1 "100k POT_TRIM" H 2730 4805 50  0000 R CNN
F 2 "Potentiometers:Potentiometer_Trimmer_Bourns_3296W" H 2800 4850 50  0001 C CNN
F 3 "" H 2800 4850 50  0001 C CNN
	1    2800 4850
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR4
U 1 1 5926D59F
P 5650 2650
F 0 "#PWR4" H 5650 2400 50  0001 C CNN
F 1 "GNDREF" H 5655 2477 50  0000 C CNN
F 2 "" H 5650 2650 50  0001 C CNN
F 3 "" H 5650 2650 50  0001 C CNN
	1    5650 2650
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5926D683
P 900 4750
F 0 "C1" H 1015 4796 50  0000 L CNN
F 1 "0.1u" H 1015 4705 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 938 4600 50  0001 C CNN
F 3 "" H 900 4750 50  0001 C CNN
	1    900  4750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 IN1
U 1 1 5926D85F
P 3550 4150
F 0 "IN1" H 3469 3925 50  0000 C CNN
F 1 "IN" H 3469 4016 50  0000 C CNN
F 2 "Connectors:1pin" H 3550 4150 50  0001 C CNN
F 3 "" H 3550 4150 50  0001 C CNN
	1    3550 4150
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X01 OUT1
U 1 1 5926D8E1
P 7000 3450
F 0 "OUT1" H 7078 3491 50  0000 L CNN
F 1 "OUT" H 7078 3400 50  0000 L CNN
F 2 "Connectors:1pin" H 7000 3450 50  0001 C CNN
F 3 "" H 7000 3450 50  0001 C CNN
	1    7000 3450
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 Vcc1
U 1 1 5926D97D
P 6150 2050
F 0 "Vcc1" H 6228 2091 50  0000 L CNN
F 1 "Vcc" H 6228 2000 50  0000 L CNN
F 2 "Connectors:1pin" H 6150 2050 50  0001 C CNN
F 3 "" H 6150 2050 50  0001 C CNN
	1    6150 2050
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 GND1
U 1 1 5926DA1B
P 5350 3800
F 0 "GND1" H 5428 3841 50  0000 L CNN
F 1 "GND" H 5428 3750 50  0000 L CNN
F 2 "Connectors:1pin" H 5350 3800 50  0001 C CNN
F 3 "" H 5350 3800 50  0001 C CNN
	1    5350 3800
	1    0    0    -1  
$EndComp
$Comp
L MCP6562 U1
U 2 1 5926BDA5
P 5700 5100
F 0 "U1" H 6000 5450 50  0000 L CNN
F 1 "LTC6702" H 6100 5350 50  0000 L CNN
F 2 "Housings_SSOP:MSOP-10_3x3mm_Pitch0.5mm" H 5700 4700 50  0001 C CNN
F 3 "" H 5700 5100 50  0001 C CNN
	2    5700 5100
	1    0    0    -1  
$EndComp
$Comp
L VPP #PWR3
U 1 1 5926DC9A
P 5600 4450
F 0 "#PWR3" H 5600 4300 50  0001 C CNN
F 1 "VPP" H 5615 4623 50  0000 C CNN
F 2 "" H 5600 4450 50  0001 C CNN
F 3 "" H 5600 4450 50  0001 C CNN
	1    5600 4450
	1    0    0    -1  
$EndComp
$Comp
L POT_TRIM RV1
U 1 1 5926E59D
P 2550 4550
F 0 "RV1" H 2480 4596 50  0000 R CNN
F 1 "100k POT_TRIM" H 2480 4505 50  0000 R CNN
F 2 "Potentiometers:Potentiometer_Trimmer_Bourns_3296W" H 2550 4550 50  0001 C CNN
F 3 "" H 2550 4550 50  0001 C CNN
	1    2550 4550
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5926EA89
P 6100 5600
F 0 "C4" H 6215 5646 50  0000 L CNN
F 1 "0.1u" H 6215 5555 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-A_EIA-3216-18_Hand" H 6138 5450 50  0001 C CNN
F 3 "" H 6100 5600 50  0001 C CNN
	1    6100 5600
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5926EA8F
P 6500 5600
F 0 "C5" H 6615 5646 50  0000 L CNN
F 1 "10u" H 6615 5555 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-A_EIA-3216-18_Hand" H 6538 5450 50  0001 C CNN
F 3 "" H 6500 5600 50  0001 C CNN
	1    6500 5600
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR5
U 1 1 5926EA95
P 6300 5900
F 0 "#PWR5" H 6300 5650 50  0001 C CNN
F 1 "GNDREF" H 6305 5727 50  0000 C CNN
F 2 "" H 6300 5900 50  0001 C CNN
F 3 "" H 6300 5900 50  0001 C CNN
	1    6300 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 4100 2800 3950
Wire Wire Line
	2550 4100 2800 4100
Connection ~ 2950 4250
Wire Wire Line
	2950 4250 2700 4550
Connection ~ 5150 2450
Wire Wire Line
	1000 2450 5150 2450
Wire Wire Line
	5800 5300 6300 5300
Wire Wire Line
	5800 5450 5800 5300
Connection ~ 6300 5450
Wire Wire Line
	6300 5300 6300 5450
Wire Wire Line
	6100 5450 6500 5450
Connection ~ 6300 5750
Wire Wire Line
	6300 5750 6300 5900
Wire Wire Line
	6100 5750 6500 5750
Connection ~ 5600 5450
Wire Wire Line
	3300 5000 3300 5450
Wire Wire Line
	3300 5450 5800 5450
Wire Wire Line
	4450 5200 5400 5200
Wire Wire Line
	4450 4650 4450 5200
Wire Wire Line
	3050 3350 3050 4250
Wire Wire Line
	4950 3350 3050 3350
Wire Wire Line
	4600 4200 4950 4200
Wire Wire Line
	4600 4150 4600 4200
Wire Wire Line
	3750 4150 4600 4150
Connection ~ 6650 3450
Wire Wire Line
	6650 5100 6650 3450
Wire Wire Line
	6000 5100 6650 5100
Wire Wire Line
	3050 4250 2950 4250
Wire Wire Line
	2950 4250 2550 4400
Wire Wire Line
	2550 4400 2300 4250
Wire Wire Line
	2800 4650 2800 4700
Wire Wire Line
	2550 4700 2800 4650
Wire Wire Line
	1000 2450 1000 4250
Connection ~ 4950 4200
Wire Wire Line
	4950 5000 5400 5000
Wire Wire Line
	5600 4800 5600 4450
Connection ~ 5150 3800
Wire Wire Line
	5150 3800 5150 3800
Connection ~ 5650 2050
Connection ~ 1650 5000
Wire Wire Line
	900  4900 900  5000
Wire Wire Line
	1000 4250 900  4250
Wire Wire Line
	900  4250 900  4600
Connection ~ 5150 2050
Connection ~ 5650 2200
Wire Wire Line
	5650 2050 5650 2200
Wire Wire Line
	5150 2050 5950 2050
Wire Wire Line
	5450 2200 5850 2200
Connection ~ 5650 2500
Wire Wire Line
	5650 2500 5650 2650
Wire Wire Line
	5450 2500 5850 2500
Connection ~ 2800 5000
Wire Wire Line
	1650 5000 1650 4650
Wire Wire Line
	900  5000 3300 5000
Connection ~ 2800 4650
Wire Wire Line
	2800 4650 4450 4650
Wire Wire Line
	2950 4850 2950 4650
Connection ~ 1000 3950
Wire Wire Line
	2800 3950 1000 3950
Connection ~ 2550 4400
Wire Wire Line
	4950 3550 4950 5000
Wire Wire Line
	5150 1950 5150 3150
Wire Wire Line
	5150 3750 5150 3950
Wire Wire Line
	5550 3450 6800 3450
$EndSCHEMATC
