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
LIBS:FermentationChamberController-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "jeu. 02 avril 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 4250 2950 3    60   ~ 0
1(Tx)
Text Label 4150 2950 3    60   ~ 0
0(Rx)
Text Label 4050 2950 3    60   ~ 0
Reset
Text Label 3850 2950 3    60   ~ 0
2
Text Label 3750 2950 3    60   ~ 0
3(**)
Text Label 3650 2950 3    60   ~ 0
4
Text Label 3550 2950 3    60   ~ 0
5(**)
Text Label 3450 2950 3    60   ~ 0
6(**)
Text Label 3350 2950 3    60   ~ 0
7
Text Label 3250 2950 3    60   ~ 0
8
Text Label 3150 2950 3    60   ~ 0
9(**)
Text Label 3050 2950 3    60   ~ 0
10(**/SS)
Text Label 2950 2950 3    60   ~ 0
11(**/MOSI)
Text Label 2850 2950 3    60   ~ 0
12(MISO)
Text Label 2850 4800 3    60   ~ 0
13(SCK)
Text Label 3150 4800 3    60   ~ 0
A0
Text Label 3250 4800 3    60   ~ 0
A1
Text Label 3350 4800 3    60   ~ 0
A2
Text Label 3450 4800 3    60   ~ 0
A3
Text Label 3550 4800 3    60   ~ 0
A4
Text Label 3650 4800 3    60   ~ 0
A5
Text Label 3750 4800 3    60   ~ 0
A6
Text Label 3850 4800 3    60   ~ 0
A7
Text Label 3050 4800 3    60   ~ 0
AREF
Text Label 4050 4800 3    60   ~ 0
Reset
Text Label 4400 4500 0    60   ~ 0
Vin
$Comp
L CONN_01X15 P1
U 1 1 56D73FAC
P 3550 3800
F 0 "P1" H 3550 4600 50  0000 C CNN
F 1 "Digital" V 3650 3800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15_Pitch2.54mm" H 3550 3800 50  0001 C CNN
F 3 "" H 3550 3800 50  0000 C CNN
	1    3550 3800
	0    1    1    0   
$EndComp
$Comp
L CONN_01X15 P2
U 1 1 56D740C7
P 3550 4200
F 0 "P2" H 3550 5000 50  0000 C CNN
F 1 "Analog" V 3650 4200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15_Pitch2.54mm" H 3550 4200 50  0001 C CNN
F 3 "" H 3550 4200 50  0000 C CNN
	1    3550 4200
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR01
U 1 1 56D7422C
P 2750 3500
F 0 "#PWR01" H 2750 3250 50  0001 C CNN
F 1 "GND" H 2750 3350 50  0000 C CNN
F 2 "" H 2750 3500 50  0000 C CNN
F 3 "" H 2750 3500 50  0000 C CNN
	1    2750 3500
	0    1    1    0   
$EndComp
$Comp
L GND #PWR02
U 1 1 56D746ED
P 2750 4500
F 0 "#PWR02" H 2750 4250 50  0001 C CNN
F 1 "GND" H 2750 4350 50  0000 C CNN
F 2 "" H 2750 4500 50  0000 C CNN
F 3 "" H 2750 4500 50  0000 C CNN
	1    2750 4500
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR03
U 1 1 56D747E8
P 4400 4600
F 0 "#PWR03" H 4400 4450 50  0001 C CNN
F 1 "+5V" H 4400 4740 28  0000 C CNN
F 2 "" H 4400 4600 50  0000 C CNN
F 3 "" H 4400 4600 50  0000 C CNN
	1    4400 4600
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR04
U 1 1 56D74854
P 4400 4700
F 0 "#PWR04" H 4400 4550 50  0001 C CNN
F 1 "+3.3V" H 4400 4840 28  0000 C CNN
F 2 "" H 4400 4700 50  0000 C CNN
F 3 "" H 4400 4700 50  0000 C CNN
	1    4400 4700
	0    1    1    0   
$EndComp
Text Notes 4310 3900 3    60   ~ 0
1
$Comp
L LCD16X2 DS1
U 1 1 591B37D5
P 3500 1150
F 0 "DS1" H 2700 1550 50  0000 C CNN
F 1 "LCD16X2" H 4200 1550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x16_Pitch2.54mm" H 3500 1100 50  0001 C CIN
F 3 "" H 3500 1150 50  0001 C CNN
	1    3500 1150
	1    0    0    -1  
$EndComp
$Comp
L TIP120 Q1
U 1 1 591B3DDF
P 5200 2150
F 0 "Q1" H 5450 2225 50  0000 L CNN
F 1 "TIP120" H 5450 2150 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220_Horizontal" H 5450 2075 50  0001 L CIN
F 3 "" H 5200 2150 50  0001 L CNN
	1    5200 2150
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 591B3E76
P 2950 2100
F 0 "R2" V 3030 2100 50  0000 C CNN
F 1 "1.47K" V 2950 2100 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2880 2100 50  0001 C CNN
F 3 "" H 2950 2100 50  0001 C CNN
	1    2950 2100
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 591B3EE1
P 4150 1850
F 0 "R3" V 4230 1850 50  0000 C CNN
F 1 "220" V 4150 1850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4080 1850 50  0001 C CNN
F 3 "" H 4150 1850 50  0001 C CNN
	1    4150 1850
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 591B3F3C
P 4850 2350
F 0 "R4" V 4930 2350 50  0000 C CNN
F 1 "2K" V 4850 2350 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4780 2350 50  0001 C CNN
F 3 "" H 4850 2350 50  0001 C CNN
	1    4850 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3600 3950 3500
Wire Wire Line
	3950 3500 2750 3500
Wire Wire Line
	4250 3600 4250 2950
Wire Wire Line
	4150 2950 4150 3600
Wire Wire Line
	4050 3600 4050 2950
Wire Wire Line
	3850 2800 3850 3600
Wire Wire Line
	3750 2600 3750 3600
Wire Wire Line
	3650 2250 3650 3600
Wire Wire Line
	3550 2200 3550 3600
Wire Wire Line
	3450 2150 3450 3600
Wire Wire Line
	3350 2100 3350 3600
Wire Wire Line
	3250 2850 3250 3600
Wire Wire Line
	2950 2750 2950 3600
Wire Wire Line
	2850 2700 2850 3600
Wire Wire Line
	2750 4500 4150 4500
Wire Wire Line
	4150 4500 4150 4400
Wire Wire Line
	4250 4400 4250 4500
Wire Wire Line
	4250 4500 4400 4500
Wire Wire Line
	4400 4600 3950 4600
Wire Wire Line
	3950 4600 3950 4400
Wire Wire Line
	4400 4700 2950 4700
Wire Wire Line
	2950 4700 2950 4400
Wire Wire Line
	4050 4800 4050 4400
Wire Wire Line
	3850 4400 3850 4800
Wire Wire Line
	3750 4800 3750 4400
Wire Wire Line
	3650 4800 3650 4400
Wire Wire Line
	3550 4400 3550 4800
Wire Wire Line
	3450 4400 3450 5300
Wire Wire Line
	3350 4400 3350 4900
Wire Wire Line
	3250 4400 3250 5050
Wire Wire Line
	3150 4400 3150 5000
Wire Wire Line
	3050 4800 3050 4400
Wire Wire Line
	2850 4400 2850 5100
Wire Wire Line
	4250 1650 5300 1650
Wire Wire Line
	5300 1650 5300 1950
$Comp
L Earth #PWR05
U 1 1 591B481E
P 5300 2400
F 0 "#PWR05" H 5300 2150 50  0001 C CNN
F 1 "Earth" H 5300 2250 50  0001 C CNN
F 2 "" H 5300 2400 50  0001 C CNN
F 3 "" H 5300 2400 50  0001 C CNN
	1    5300 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2400 5300 2350
$Comp
L Earth #PWR06
U 1 1 591B4871
P 2750 1700
F 0 "#PWR06" H 2750 1450 50  0001 C CNN
F 1 "Earth" H 2750 1550 50  0001 C CNN
F 2 "" H 2750 1700 50  0001 C CNN
F 3 "" H 2750 1700 50  0001 C CNN
	1    2750 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 1650 2750 1700
$Comp
L +5V #PWR07
U 1 1 591B4919
P 2850 1700
F 0 "#PWR07" H 2850 1550 50  0001 C CNN
F 1 "+5V" H 2850 1840 50  0000 C CNN
F 2 "" H 2850 1700 50  0001 C CNN
F 3 "" H 2850 1700 50  0001 C CNN
	1    2850 1700
	-1   0    0    1   
$EndComp
Wire Wire Line
	2850 1650 2850 1700
Wire Wire Line
	2950 1650 2950 1950
$Comp
L Earth #PWR08
U 1 1 591B4B94
P 2950 2250
F 0 "#PWR08" H 2950 2000 50  0001 C CNN
F 1 "Earth" H 2950 2100 50  0001 C CNN
F 2 "" H 2950 2250 50  0001 C CNN
F 3 "" H 2950 2250 50  0001 C CNN
	1    2950 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1650 3050 2700
Wire Wire Line
	3050 2700 2850 2700
Wire Wire Line
	5000 2150 4850 2150
Wire Wire Line
	4850 2150 4850 2200
Wire Wire Line
	4850 2500 4850 5100
Wire Wire Line
	4850 5100 2850 5100
$Comp
L Earth #PWR09
U 1 1 591B5084
P 3150 1700
F 0 "#PWR09" H 3150 1450 50  0001 C CNN
F 1 "Earth" H 3150 1550 50  0001 C CNN
F 2 "" H 3150 1700 50  0001 C CNN
F 3 "" H 3150 1700 50  0001 C CNN
	1    3150 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 1650 3150 1700
Wire Wire Line
	3250 1650 3250 2750
Wire Wire Line
	3250 2750 2950 2750
Wire Wire Line
	3750 1650 3750 2100
Wire Wire Line
	3750 2100 3350 2100
Wire Wire Line
	3850 1650 3850 2150
Wire Wire Line
	3850 2150 3450 2150
Wire Wire Line
	3950 1650 3950 2200
Wire Wire Line
	3950 2200 3550 2200
Wire Wire Line
	4050 1650 4050 2250
Wire Wire Line
	4050 2250 3650 2250
Wire Wire Line
	4150 1650 4150 1700
$Comp
L +5V #PWR010
U 1 1 591BA361
P 4150 2000
F 0 "#PWR010" H 4150 1850 50  0001 C CNN
F 1 "+5V" H 4150 2140 50  0000 C CNN
F 2 "" H 4150 2000 50  0001 C CNN
F 3 "" H 4150 2000 50  0001 C CNN
	1    4150 2000
	-1   0    0    1   
$EndComp
$Comp
L Rotary_Encoder_Switch SW1
U 1 1 591BA40F
P 6100 1200
F 0 "SW1" H 6100 1460 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 6100 940 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 6000 1360 50  0001 C CNN
F 3 "" H 6100 1460 50  0001 C CNN
	1    6100 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 5300 5150 5300
Wire Wire Line
	5150 5300 5150 2650
Wire Wire Line
	5150 2650 6650 2650
Wire Wire Line
	6650 2650 6650 1300
Wire Wire Line
	6650 1300 6400 1300
$Comp
L +5V #PWR011
U 1 1 591BA55B
P 6450 1100
F 0 "#PWR011" H 6450 950 50  0001 C CNN
F 1 "+5V" H 6450 1240 50  0000 C CNN
F 2 "" H 6450 1100 50  0001 C CNN
F 3 "" H 6450 1100 50  0001 C CNN
	1    6450 1100
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 1100 6450 1100
$Comp
L R R6
U 1 1 591BA5F0
P 6800 1300
F 0 "R6" V 6880 1300 50  0000 C CNN
F 1 "10K" V 6800 1300 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6730 1300 50  0001 C CNN
F 3 "" H 6800 1300 50  0001 C CNN
	1    6800 1300
	0    1    1    0   
$EndComp
$Comp
L GND #PWR012
U 1 1 591BA655
P 7000 1300
F 0 "#PWR012" H 7000 1050 50  0001 C CNN
F 1 "GND" H 7000 1150 50  0000 C CNN
F 2 "" H 7000 1300 50  0001 C CNN
F 3 "" H 7000 1300 50  0001 C CNN
	1    7000 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7000 1300 6950 1300
$Comp
L GND #PWR013
U 1 1 591BA8F3
P 5750 1200
F 0 "#PWR013" H 5750 950 50  0001 C CNN
F 1 "GND" H 5750 1050 50  0000 C CNN
F 2 "" H 5750 1200 50  0001 C CNN
F 3 "" H 5750 1200 50  0001 C CNN
	1    5750 1200
	0    1    1    0   
$EndComp
Wire Wire Line
	5800 1200 5750 1200
Wire Wire Line
	3750 2600 4750 2600
Wire Wire Line
	4750 2600 4750 1300
Wire Wire Line
	4750 1300 5800 1300
Wire Wire Line
	3250 2850 3700 2850
Wire Wire Line
	3700 2850 3700 2500
Wire Wire Line
	3700 2500 4650 2500
Wire Wire Line
	4650 2500 4650 1100
Wire Wire Line
	4650 1100 5800 1100
$Comp
L Screw_Terminal_1x02 J1
U 1 1 591BAA85
P 1000 6500
F 0 "J1" H 1000 6750 50  0000 C TNN
F 1 "Screw_Terminal_1x02" V 850 6500 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_WAGO-804_RM5mm_2pol" H 1000 6275 50  0001 C CNN
F 3 "" H 975 6500 50  0001 C CNN
	1    1000 6500
	0    -1   -1   0   
$EndComp
$Comp
L Screw_Terminal_1x02 J2
U 1 1 591BADC2
P 1850 6500
F 0 "J2" H 1850 6750 50  0000 C TNN
F 1 "Screw_Terminal_1x02" V 1700 6500 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_WAGO-804_RM5mm_2pol" H 1850 6275 50  0001 C CNN
F 3 "" H 1825 6500 50  0001 C CNN
	1    1850 6500
	0    -1   -1   0   
$EndComp
$Comp
L Screw_Terminal_1x02 J3
U 1 1 591BAE99
P 2700 6500
F 0 "J3" H 2700 6750 50  0000 C TNN
F 1 "Screw_Terminal_1x02" V 2550 6500 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_WAGO-804_RM5mm_2pol" H 2700 6275 50  0001 C CNN
F 3 "" H 2675 6500 50  0001 C CNN
	1    2700 6500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3050 2850 3050 3600
Wire Wire Line
	1750 2850 3050 2850
Wire Wire Line
	1750 2850 1750 6300
Wire Wire Line
	1950 6300 1950 5800
Wire Wire Line
	1950 5800 1750 5800
Connection ~ 1750 5800
$Comp
L R R1
U 1 1 591BB000
P 1900 5550
F 0 "R1" V 1980 5550 50  0000 C CNN
F 1 "4.7K" V 1800 5550 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1830 5550 50  0001 C CNN
F 3 "" H 1900 5550 50  0001 C CNN
	1    1900 5550
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR014
U 1 1 591BB0B3
P 2150 5550
F 0 "#PWR014" H 2150 5400 50  0001 C CNN
F 1 "+5V" H 2150 5690 50  0000 C CNN
F 2 "" H 2150 5550 50  0001 C CNN
F 3 "" H 2150 5550 50  0001 C CNN
	1    2150 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 5550 2050 5550
Wire Wire Line
	2150 5550 2150 5700
Wire Wire Line
	1100 5700 2600 5700
Wire Wire Line
	1100 5700 1100 6300
Wire Wire Line
	2600 5700 2600 6300
Connection ~ 2150 5700
$Comp
L GND #PWR015
U 1 1 591BB21C
P 900 6200
F 0 "#PWR015" H 900 5950 50  0001 C CNN
F 1 "GND" H 900 6050 50  0000 C CNN
F 2 "" H 900 6200 50  0001 C CNN
F 3 "" H 900 6200 50  0001 C CNN
	1    900  6200
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR016
U 1 1 591BB255
P 2800 6200
F 0 "#PWR016" H 2800 5950 50  0001 C CNN
F 1 "GND" H 2800 6050 50  0000 C CNN
F 2 "" H 2800 6200 50  0001 C CNN
F 3 "" H 2800 6200 50  0001 C CNN
	1    2800 6200
	-1   0    0    1   
$EndComp
Wire Wire Line
	900  6200 900  6300
Wire Wire Line
	2800 6200 2800 6300
Wire Notes Line
	2100 2550 5850 2550
Wire Notes Line
	2100 2550 2100 650 
Wire Notes Line
	2100 650  5450 650 
Wire Notes Line
	5450 650  5450 1800
Wire Notes Line
	5450 1800 5850 1800
Wire Notes Line
	5850 1800 5850 2550
Wire Notes Line
	7300 1750 5500 1750
Wire Notes Line
	5500 1750 5500 700 
Wire Notes Line
	5500 700  7300 700 
Wire Notes Line
	7300 700  7300 1750
Wire Notes Line
	550  6750 3300 6750
Wire Notes Line
	3300 6750 3300 5250
Wire Notes Line
	3300 5250 550  5250
Wire Notes Line
	550  5250 550  6750
Wire Wire Line
	3150 2800 3150 3600
$Comp
L CONN_01X04 J5
U 1 1 591BC121
P 6900 5750
F 0 "J5" H 6900 6000 50  0000 C CNN
F 1 "CONN_01X04" V 7000 5750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 6900 5750 50  0001 C CNN
F 3 "" H 6900 5750 50  0001 C CNN
	1    6900 5750
	1    0    0    -1  
$EndComp
$Comp
L TIP120 Q2
U 1 1 591BC33E
P 5700 5800
F 0 "Q2" H 5950 5875 50  0000 L CNN
F 1 "TIP120" H 5950 5800 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220_Vertical" H 5950 5725 50  0001 L CIN
F 3 "" H 5700 5800 50  0001 L CNN
	1    5700 5800
	0    1    1    0   
$EndComp
$Comp
L CONN_01X04 J4
U 1 1 591BC4F4
P 6900 4400
F 0 "J4" H 6900 4650 50  0000 C CNN
F 1 "CONN_01X04" V 7000 4400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 6900 4400 50  0001 C CNN
F 3 "" H 6900 4400 50  0001 C CNN
	1    6900 4400
	1    0    0    -1  
$EndComp
$Comp
L D D1
U 1 1 591BC636
P 6400 5950
F 0 "D1" H 6400 6050 50  0000 C CNN
F 1 "Diode" H 6400 5850 50  0000 C CNN
F 2 "Diodes_THT:D_DO-15_P10.16mm_Horizontal" H 6400 5950 50  0001 C CNN
F 3 "" H 6400 5950 50  0001 C CNN
	1    6400 5950
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 591BC750
P 5700 5200
F 0 "R5" V 5780 5200 50  0000 C CNN
F 1 "1K" V 5700 5200 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5630 5200 50  0001 C CNN
F 3 "" H 5700 5200 50  0001 C CNN
	1    5700 5200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 591BCA6D
P 5400 5900
F 0 "#PWR017" H 5400 5650 50  0001 C CNN
F 1 "GND" H 5400 5750 50  0000 C CNN
F 2 "" H 5400 5900 50  0001 C CNN
F 3 "" H 5400 5900 50  0001 C CNN
	1    5400 5900
	0    1    1    0   
$EndComp
Wire Wire Line
	5400 5900 5500 5900
Wire Wire Line
	5900 5900 6000 5900
Wire Wire Line
	5700 5350 5700 5600
Wire Wire Line
	5700 4900 5700 5050
Wire Wire Line
	5700 4900 5250 4900
Wire Wire Line
	5250 4900 5250 5400
Wire Wire Line
	5250 5400 3750 5400
Wire Wire Line
	3750 5400 3750 5000
Wire Wire Line
	3750 5000 3150 5000
Wire Wire Line
	6700 5700 6000 5700
Wire Wire Line
	6000 5700 6000 2750
Wire Wire Line
	6000 2750 3300 2750
Wire Wire Line
	3300 2750 3300 2800
Wire Wire Line
	3300 2800 3150 2800
Wire Wire Line
	6700 5600 6100 5600
Wire Wire Line
	6100 5600 6100 2800
Wire Wire Line
	6100 2800 3850 2800
$Comp
L +5V #PWR018
U 1 1 591BDC18
P 6700 4550
F 0 "#PWR018" H 6700 4400 50  0001 C CNN
F 1 "+5V" H 6700 4690 50  0000 C CNN
F 2 "" H 6700 4550 50  0001 C CNN
F 3 "" H 6700 4550 50  0001 C CNN
	1    6700 4550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6700 4450 5000 4450
Wire Wire Line
	5000 4450 5000 5050
Wire Wire Line
	5000 5050 3250 5050
Wire Wire Line
	6700 4350 4900 4350
Wire Wire Line
	4900 4350 4900 4900
Wire Wire Line
	4900 4900 3350 4900
$Comp
L GND #PWR019
U 1 1 591BE258
P 6700 4250
F 0 "#PWR019" H 6700 4000 50  0001 C CNN
F 1 "GND" H 6700 4100 50  0000 C CNN
F 2 "" H 6700 4250 50  0001 C CNN
F 3 "" H 6700 4250 50  0001 C CNN
	1    6700 4250
	0    1    1    0   
$EndComp
Wire Notes Line
	7400 4800 6200 4800
Wire Notes Line
	6200 4800 6200 3900
Wire Notes Line
	6200 3900 7400 3900
Wire Notes Line
	7400 3900 7400 4800
Wire Notes Line
	5200 6350 7150 6350
Wire Notes Line
	5200 4850 7150 4850
Wire Notes Line
	7150 4850 7150 6350
Text Notes 3700 650  0    60   ~ 0
LCD 1602
Text Notes 700  5350 0    60   ~ 0
DS18B20 Temperature Sensors
Text Notes 6200 4950 0    60   ~ 0
PC Fan Connection
Text Notes 6250 4000 0    60   ~ 0
Dual Relay Connection
Text Notes 5550 800  0    60   ~ 0
Rotary Encode and Switch Connection
Text Notes 2700 4050 0    60   ~ 0
Arduino Nano
$Comp
L +12V #PWR020
U 1 1 591BFE81
P 6250 5800
F 0 "#PWR020" H 6250 5650 50  0001 C CNN
F 1 "+12V" H 6250 5940 50  0000 C CNN
F 2 "" H 6250 5800 50  0001 C CNN
F 3 "" H 6250 5800 50  0001 C CNN
	1    6250 5800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6250 5800 6700 5800
Connection ~ 6400 5800
Wire Wire Line
	6700 5900 6700 6150
Wire Wire Line
	6700 6150 6000 6150
Wire Wire Line
	6000 6150 6000 5900
Wire Wire Line
	6400 6100 6400 6150
Connection ~ 6400 6150
Wire Notes Line
	5200 6350 5200 4850
Connection ~ 1750 5550
Connection ~ 6650 1300
$EndSCHEMATC
