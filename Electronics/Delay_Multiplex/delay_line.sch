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
LIBS:chris
LIBS:onsemi
LIBS:nxp
LIBS:video
LIBS:motors
LIBS:ir
LIBS:nxp_armmcu
LIBS:Lattice
LIBS:mechanical
LIBS:microchip_pic16mcu
LIBS:analog_devices
LIBS:relays
LIBS:motor_drivers
LIBS:switches
LIBS:transf
LIBS:nordicsemi
LIBS:hc11
LIBS:elec-unifil
LIBS:microchip_pic24mcu
LIBS:dc-dc
LIBS:battery_management
LIBS:silabs
LIBS:supertex
LIBS:Zilog
LIBS:stm32
LIBS:Worldsemi
LIBS:microchip_pic32mcu
LIBS:graphic
LIBS:triac_thyristor
LIBS:allegro
LIBS:LEM
LIBS:microchip_pic10mcu
LIBS:gennum
LIBS:stm8
LIBS:actel
LIBS:msp430
LIBS:Oscillators
LIBS:cmos_ieee
LIBS:microchip_dspic33dsc
LIBS:references
LIBS:74xgxx
LIBS:microchip_pic18mcu
LIBS:pspice
LIBS:ESD_Protection
LIBS:ac-dc
LIBS:diode
LIBS:logo
LIBS:Power_Management
LIBS:infineon
LIBS:Xicor
LIBS:brooktre
LIBS:Altera
LIBS:sensors
LIBS:bbd
LIBS:ttl_ieee
LIBS:bosch
LIBS:rfcom
LIBS:intersil
LIBS:powerint
LIBS:microchip_pic12mcu
LIBS:modules
LIBS:RFSolutions
LIBS:maxim
LIBS:leds
LIBS:zetex
LIBS:wiznet
LIBS:ftdi
LIBS:delay_line-cache
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
L DS1100M-500 U1
U 1 1 593325CF
P 5600 3200
F 0 "U1" H 5600 3900 60  0000 C CNN
F 1 "DS1100-500" H 5600 3794 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 5650 3200 60  0001 C CNN
F 3 "" H 5650 3200 60  0001 C CNN
	1    5600 3200
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR01
U 1 1 59332AA7
P 6100 3900
F 0 "#PWR01" H 6100 3650 50  0001 C CNN
F 1 "GNDREF" H 6105 3727 50  0000 C CNN
F 2 "" H 6100 3900 50  0001 C CNN
F 3 "" H 6100 3900 50  0001 C CNN
	1    6100 3900
	1    0    0    -1  
$EndComp
$Comp
L USB_OTG J1
U 1 1 593335EB
P 3550 2850
F 0 "J1" H 3605 3317 50  0000 C CNN
F 1 "USB_OTG" H 3605 3226 50  0000 C CNN
F 2 "Connectors_Molex:USB_Micro-B_Molex_47346-0001" H 3700 2800 50  0001 C CNN
F 3 "" H 3700 2800 50  0001 C CNN
	1    3550 2850
	1    0    0    -1  
$EndComp
$Comp
L SW_DIP_x05 SW1
U 1 1 5933F48E
P 6800 3200
F 0 "SW1" H 6800 3667 50  0000 C CNN
F 1 "SW_DIP_x05" H 6800 3576 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_DIP_x5_W8.61mm_Slide_LowProfile" H 6800 3200 50  0001 C CNN
F 3 "" H 6800 3200 50  0001 C CNN
	1    6800 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 3750 6100 3900
Connection ~ 6100 3750
Connection ~ 5600 3750
Wire Wire Line
	4500 3200 5050 3200
Wire Wire Line
	5050 2700 5600 2700
Wire Wire Line
	3850 2650 5050 2650
Wire Wire Line
	5050 2650 5050 2700
Wire Wire Line
	3450 3750 3450 3250
Connection ~ 4650 3750
Wire Wire Line
	3550 3250 3550 3750
Connection ~ 3550 3750
Wire Wire Line
	6150 3200 6350 3200
Wire Wire Line
	6350 3200 6350 3000
Wire Wire Line
	6350 3000 6500 3000
Wire Wire Line
	6150 3000 6300 3000
Wire Wire Line
	6300 3000 6300 3100
Wire Wire Line
	6300 3100 6500 3100
Wire Wire Line
	6150 3300 6400 3300
Wire Wire Line
	6400 3300 6400 3200
Wire Wire Line
	6400 3200 6500 3200
Wire Wire Line
	6150 3100 6250 3100
Wire Wire Line
	6250 3100 6250 3350
Wire Wire Line
	6250 3350 6500 3350
Wire Wire Line
	6500 3350 6500 3300
Wire Wire Line
	6150 3400 6500 3400
Connection ~ 7100 3300
Connection ~ 7100 3200
Connection ~ 7100 3100
Wire Wire Line
	7100 3000 7100 3400
Wire Wire Line
	7100 3000 7450 3000
$Comp
L CONN_01X01 J2
U 1 1 5937EF55
P 7700 2750
F 0 "J2" H 7778 2791 50  0000 L CNN
F 1 "CONN_01X01" H 7778 2700 50  0000 L CNN
F 2 "Connectors:1pin" H 7700 2750 50  0001 C CNN
F 3 "" H 7700 2750 50  0001 C CNN
	1    7700 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 3000 7450 2750
Wire Wire Line
	7450 2750 7500 2750
Wire Wire Line
	3450 3750 6350 3750
$Comp
L CONN_01X01 J3
U 1 1 5937F1B9
P 4300 3200
F 0 "J3" H 4378 3241 50  0000 L CNN
F 1 "CONN_01X01" H 4378 3150 50  0000 L CNN
F 2 "Connectors:1pin" H 4300 3200 50  0001 C CNN
F 3 "" H 4300 3200 50  0001 C CNN
	1    4300 3200
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X01 J4
U 1 1 5937FD10
P 6550 3750
F 0 "J4" H 6628 3791 50  0000 L CNN
F 1 "CONN_01X01" H 6628 3700 50  0000 L CNN
F 2 "Connectors:1pin" H 6550 3750 50  0001 C CNN
F 3 "" H 6550 3750 50  0001 C CNN
	1    6550 3750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 J5
U 1 1 5937FE2C
P 5250 4000
F 0 "J5" H 5328 4041 50  0000 L CNN
F 1 "CONN_01X01" H 5328 3950 50  0000 L CNN
F 2 "Connectors:1pin" H 5250 4000 50  0001 C CNN
F 3 "" H 5250 4000 50  0001 C CNN
	1    5250 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	5250 3800 5250 3750
Connection ~ 5250 3750
$EndSCHEMATC
