EESchema Schematic File Version 4
LIBS:SolarTracker MK I-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
Title "Top Level"
Date "2019-07-20"
Rev "1.0"
Comp "Open Source Research Center"
Comment1 "Source: http://osrc.rip"
Comment2 "License: CC-BY 4.0"
Comment3 "Author: Tibor Áser Veres"
Comment4 "Project: Solar Tracker MK I  -  Designed partially with off the shelf modules for DIY-ers."
$EndDescr
$Comp
L power:+5V #PWR0102
U 1 1 5D2C0B52
P 5050 850
F 0 "#PWR0102" H 5050 700 50  0001 C CNN
F 1 "+5V" H 5065 1023 50  0000 C CNN
F 2 "" H 5050 850 50  0001 C CNN
F 3 "" H 5050 850 50  0001 C CNN
	1    5050 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 3050 4850 3150
Wire Wire Line
	4950 3050 4950 3150
Wire Wire Line
	4950 3150 4850 3150
Connection ~ 4850 3150
Wire Wire Line
	4850 3150 4850 3250
Wire Wire Line
	5050 850  5050 1050
Wire Wire Line
	5350 2050 6100 2050
Wire Wire Line
	5350 2150 6100 2150
Wire Wire Line
	5350 2250 6100 2250
Wire Wire Line
	6100 2350 5350 2350
$Sheet
S 6100 1950 1100 500 
U 5D3AB2EA
F0 "Custom Circuit Part: A" 50
F1 "CustomCircuitPA.sch" 50
F2 "STop" O L 6100 2250 50 
F3 "SBottom" O L 6100 2350 50 
F4 "SLeft" O L 6100 2050 50 
F5 "SRight" O L 6100 2150 50 
F6 "Override" I R 7200 2300 50 
F7 "TankTemp" O R 7200 2150 50 
F8 "HeadSensor" O R 7200 2050 50 
$EndSheet
Wire Wire Line
	4250 2750 4350 2750
Wire Wire Line
	4150 2650 4350 2650
Wire Wire Line
	4100 2550 4350 2550
Wire Wire Line
	4050 2450 4350 2450
Wire Wire Line
	4350 2350 4000 2350
Wire Wire Line
	3900 2250 4350 2250
Wire Wire Line
	4350 2150 3850 2150
Wire Wire Line
	3850 2150 3850 3050
Wire Wire Line
	3800 2050 4350 2050
Wire Wire Line
	3750 1850 4350 1850
Wire Wire Line
	4350 1650 3700 1650
Connection ~ 3700 1650
Wire Wire Line
	4350 1750 3550 1750
Wire Wire Line
	4350 1950 3600 1950
Wire Wire Line
	8200 3050 8200 3150
Wire Wire Line
	8300 3050 8300 3150
Wire Wire Line
	8300 3150 8200 3150
Connection ~ 8200 3150
Wire Wire Line
	8200 3150 8200 3350
$Comp
L power:+5V #PWR024
U 1 1 5D66405E
P 8100 850
F 0 "#PWR024" H 8100 700 50  0001 C CNN
F 1 "+5V" H 8115 1023 50  0000 C CNN
F 2 "" H 8100 850 50  0001 C CNN
F 3 "" H 8100 850 50  0001 C CNN
	1    8100 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 850  8100 1050
$Sheet
S 6100 3200 1100 1650
U 5D43DE4E
F0 "Custom Interface" 50
F1 "CustomInterface.sch" 50
F2 "Sensitivity" O L 6100 3300 50 
F3 "MinLight" O L 6100 3400 50 
F4 "LRSpeedP" O L 6100 3500 50 
F5 "UDSpeedP" O L 6100 3600 50 
F6 "Difference" O R 7200 3300 50 
F7 "MaxTemp" O R 7200 3400 50 
F8 "PumpSpeedP" O R 7200 3500 50 
F9 "ManUp" O L 6100 4100 50 
F10 "Auto" O L 6100 4550 50 
F11 "ManLeft" O L 6100 4200 50 
F12 "ManDown" O L 6100 4000 50 
F13 "ManRight" O L 6100 3900 50 
F14 "Right" I L 6100 4350 50 
F15 "Up" I L 6100 4650 50 
F16 "Down" I L 6100 4450 50 
F17 "Left" I L 6100 4750 50 
F18 "Sleep" I L 6100 3750 50 
F19 "Pump" I R 7200 3650 50 
$EndSheet
Wire Wire Line
	7700 2450 7800 2450
Wire Wire Line
	7800 2350 7650 2350
Wire Wire Line
	7600 2250 7800 2250
Wire Wire Line
	8800 2750 8900 2750
Wire Wire Line
	8900 2750 8900 3650
Wire Wire Line
	9000 2650 9000 3750
Wire Wire Line
	8800 2650 9000 2650
Wire Wire Line
	7800 2150 7200 2150
Wire Wire Line
	7200 2050 7800 2050
Wire Wire Line
	9000 3750 7400 3750
Wire Wire Line
	7400 3750 7400 2300
Wire Wire Line
	7200 2300 7400 2300
$Comp
L Local:LimitSW-HexaLib SW1
U 1 1 5D82E6BD
P 2700 1650
F 0 "SW1" H 3000 1900 50  0000 R CNN
F 1 "Left Limit" H 3000 1450 50  0000 R CNN
F 2 "" H 2700 1650 50  0001 C CNN
F 3 "" H 2700 1650 50  0001 C CNN
	1    2700 1650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3000 1650 3700 1650
Wire Wire Line
	3000 2350 3750 2350
Connection ~ 3750 2350
Wire Wire Line
	3750 2350 3750 1850
Wire Wire Line
	3850 3050 3000 3050
Connection ~ 3850 3050
Wire Wire Line
	3900 3750 3000 3750
Connection ~ 3900 3750
Wire Wire Line
	3900 3750 3900 2250
Wire Wire Line
	2400 3650 2250 3650
Wire Wire Line
	2250 4350 2250 3650
Wire Wire Line
	2150 2950 2150 4350
Wire Wire Line
	2150 2950 2400 2950
Wire Wire Line
	2050 4350 2050 2250
Wire Wire Line
	2050 2250 2400 2250
Wire Wire Line
	1950 1550 1950 4350
Wire Wire Line
	1950 1550 2400 1550
$Comp
L power:+5V #PWR010
U 1 1 5D90BB9F
P 1850 4200
F 0 "#PWR010" H 1850 4050 50  0001 C CNN
F 1 "+5V" H 1865 4373 50  0000 C CNN
F 2 "" H 1850 4200 50  0001 C CNN
F 3 "" H 1850 4200 50  0001 C CNN
	1    1850 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 5350 2900 5450
Wire Wire Line
	2900 5450 2550 5450
Wire Wire Line
	1850 5350 1850 5450
Connection ~ 1850 5450
Wire Wire Line
	1850 5450 1500 5450
Wire Wire Line
	2200 5350 2200 5450
Connection ~ 2200 5450
Wire Wire Line
	2200 5450 1850 5450
Wire Wire Line
	2550 5350 2550 5450
Connection ~ 2550 5450
Wire Wire Line
	2550 5450 2200 5450
Wire Wire Line
	1850 4200 1850 4350
Wire Wire Line
	1500 5350 1500 5450
Wire Wire Line
	7200 3500 7700 3500
Wire Wire Line
	7700 2450 7700 3500
Wire Wire Line
	7650 3400 7200 3400
Wire Wire Line
	7650 2350 7650 3400
Wire Wire Line
	7600 3300 7200 3300
Wire Wire Line
	7600 2250 7600 3300
Wire Wire Line
	5350 2750 5450 2750
Wire Wire Line
	5450 2750 5450 3600
Wire Wire Line
	5450 3600 6100 3600
Wire Wire Line
	6100 3500 5500 3500
Wire Wire Line
	5500 3500 5500 2650
Wire Wire Line
	5350 2650 5500 2650
Wire Wire Line
	5350 2550 5550 2550
Wire Wire Line
	5550 2550 5550 3400
Wire Wire Line
	5550 3400 6100 3400
Wire Wire Line
	6100 3300 5600 3300
Wire Wire Line
	5600 3300 5600 2450
Wire Wire Line
	5600 2450 5350 2450
Wire Wire Line
	4250 3750 6100 3750
Wire Wire Line
	4250 2750 4250 3750
Wire Wire Line
	6100 3900 4150 3900
Wire Wire Line
	4150 2650 4150 3900
Wire Wire Line
	4100 4000 6100 4000
Wire Wire Line
	4100 2550 4100 4000
Wire Wire Line
	6100 4100 4050 4100
Wire Wire Line
	4050 2450 4050 4100
Wire Wire Line
	4000 4200 6100 4200
Wire Wire Line
	4000 2350 4000 4200
Wire Wire Line
	6100 4350 3900 4350
Wire Wire Line
	3900 3750 3900 4350
Wire Wire Line
	3850 4450 6100 4450
Wire Wire Line
	3850 3050 3850 4450
Wire Wire Line
	6100 4550 3800 4550
Wire Wire Line
	3800 2050 3800 4550
Wire Wire Line
	3750 4650 6100 4650
Wire Wire Line
	3750 2350 3750 4650
Wire Wire Line
	6100 4750 3700 4750
Wire Wire Line
	3700 1650 3700 4750
$Comp
L Motor:Motor_DC M1
U 1 1 5DA01C9A
P 2450 6400
F 0 "M1" V 2745 6350 50  0000 C CNN
F 1 "UDMotor" V 2654 6350 50  0000 C CNN
F 2 "" H 2450 6310 50  0001 C CNN
F 3 "~" H 2450 6310 50  0001 C CNN
	1    2450 6400
	0    -1   -1   0   
$EndComp
$Comp
L Motor:Motor_DC M2
U 1 1 5DA03E96
P 2450 7000
F 0 "M2" V 2745 6950 50  0000 C CNN
F 1 "LRMotor" V 2654 6950 50  0000 C CNN
F 2 "" H 2450 6910 50  0001 C CNN
F 3 "~" H 2450 6910 50  0001 C CNN
	1    2450 7000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2300 6100 2150 6100
Wire Wire Line
	2150 6100 2150 6400
Wire Wire Line
	2150 6400 2250 6400
Wire Wire Line
	2650 6100 2850 6100
Wire Wire Line
	2850 6100 2850 6400
Wire Wire Line
	2850 6400 2750 6400
Wire Wire Line
	1950 7000 2250 7000
Wire Wire Line
	2750 7000 3000 7000
$Sheet
S 6100 5350 1100 800 
U 5DAD4B14
F0 "Custom Circuit Part: B" 50
F1 "CustomCircuitPB.sch" 50
F2 "LRSpeed" I L 6100 5550 50 
F3 "UDSpeed" I L 6100 5450 50 
F4 "LRMotor" O L 6100 5700 50 
F5 "UDMotor" O L 6100 5800 50 
F6 "PSpeed" I R 7200 5550 50 
F7 "Pomp" O R 7200 5650 50 
F8 "PEnable" I R 7200 5450 50 
$EndSheet
$Comp
L Motor:Motor_DC M?
U 1 1 5DAFA334
P 8150 5000
AR Path="/5DAD4B14/5DAFA334" Ref="M?"  Part="1" 
AR Path="/5DAFA334" Ref="M3"  Part="1" 
F 0 "M3" H 8308 4996 50  0000 L CNN
F 1 "12V DC Pump" H 8308 4905 50  0000 L CNN
F 2 "" H 8150 4910 50  0001 C CNN
F 3 "~" H 8150 4910 50  0001 C CNN
	1    8150 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 4600 8150 4800
Wire Wire Line
	8150 5300 8150 5650
Wire Wire Line
	7200 3650 7300 3650
Wire Wire Line
	7300 3650 7300 5450
Wire Wire Line
	7300 5450 7200 5450
Connection ~ 7300 3650
Wire Wire Line
	7300 3650 8900 3650
Wire Wire Line
	7200 5550 9100 5550
Wire Wire Line
	9100 5550 9100 2550
Wire Wire Line
	9100 2550 8800 2550
Text Notes 2250 6650 0    50   ~ 0
12V DC Motors
Wire Wire Line
	1950 5350 1950 7000
Wire Wire Line
	2300 5350 2300 6100
Wire Wire Line
	2650 5350 2650 6100
Wire Wire Line
	3000 5350 3000 7000
Wire Wire Line
	6100 5800 2750 5800
Wire Wire Line
	2400 5800 2400 5350
Wire Wire Line
	2750 5350 2750 5800
Connection ~ 2750 5800
Wire Wire Line
	2750 5800 2400 5800
Wire Wire Line
	2050 5350 2050 5700
Wire Wire Line
	2050 5700 3100 5700
Wire Wire Line
	3100 5700 3100 5350
Connection ~ 3100 5700
Wire Wire Line
	3100 5700 6100 5700
Wire Wire Line
	3600 4850 5850 4850
Wire Wire Line
	3600 1950 3600 4850
Wire Wire Line
	3550 4900 5800 4900
Wire Wire Line
	3550 1750 3550 4900
Wire Wire Line
	5850 5450 6100 5450
Wire Wire Line
	5850 4850 5850 5450
Wire Wire Line
	6100 5550 5800 5550
Wire Wire Line
	5800 4900 5800 5550
Wire Wire Line
	8150 5650 7200 5650
$Comp
L power:+5V #PWR051
U 1 1 5DC8E1A2
P 5100 6650
F 0 "#PWR051" H 5100 6500 50  0001 C CNN
F 1 "+5V" H 5115 6823 50  0000 C CNN
F 2 "" H 5100 6650 50  0001 C CNN
F 3 "" H 5100 6650 50  0001 C CNN
	1    5100 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 6750 5100 6750
Wire Wire Line
	5100 6750 5100 6650
Wire Wire Line
	4000 6650 4000 6750
Wire Wire Line
	4550 7150 4550 7300
NoConn ~ 4350 1450
NoConn ~ 4350 1550
NoConn ~ 4750 1050
NoConn ~ 4950 1050
NoConn ~ 5350 1450
NoConn ~ 5350 1550
NoConn ~ 5350 1850
NoConn ~ 7800 1850
NoConn ~ 7800 1550
NoConn ~ 7800 1450
NoConn ~ 8200 1050
NoConn ~ 8400 1050
NoConn ~ 8800 1450
NoConn ~ 8800 1550
NoConn ~ 8800 1650
NoConn ~ 8800 1750
NoConn ~ 8800 1850
NoConn ~ 8800 1950
NoConn ~ 8800 2050
NoConn ~ 8800 2150
NoConn ~ 8800 2250
NoConn ~ 8800 2350
NoConn ~ 8800 2450
NoConn ~ 7800 2550
NoConn ~ 7800 2650
NoConn ~ 7800 2750
NoConn ~ 2400 3850
NoConn ~ 2400 3150
NoConn ~ 2400 2450
NoConn ~ 2400 1750
Wire Wire Line
	4100 6750 4000 6750
$Comp
L Local:12V_Source #PWR0101
U 1 1 5DDEB616
P 8150 4600
F 0 "#PWR0101" H 8150 4850 50  0001 C CNN
F 1 "12V_Source" H 8150 4773 50  0000 C CNN
F 2 "" H 8150 4600 50  0001 C CNN
F 3 "" H 8150 4600 50  0001 C CNN
	1    8150 4600
	1    0    0    -1  
$EndComp
$Comp
L Local:12V_Source #PWR0103
U 1 1 5DDEBA98
P 4000 6650
F 0 "#PWR0103" H 4000 6900 50  0001 C CNN
F 1 "12V_Source" H 4000 6823 50  0000 C CNN
F 2 "" H 4000 6650 50  0001 C CNN
F 3 "" H 4000 6650 50  0001 C CNN
	1    4000 6650
	1    0    0    -1  
$EndComp
$Comp
L Local:12V_Source #PWR0104
U 1 1 5DDEBF47
P 1500 5350
F 0 "#PWR0104" H 1500 5600 50  0001 C CNN
F 1 "12V_Source" H 1500 5523 50  0000 C CNN
F 2 "" H 1500 5350 50  0001 C CNN
F 3 "" H 1500 5350 50  0001 C CNN
	1    1500 5350
	1    0    0    -1  
$EndComp
$Comp
L Local:GND_Source #PWR0107
U 1 1 5DDF6475
P 4550 7300
F 0 "#PWR0107" H 4550 7000 50  0001 C CNN
F 1 "GND_Source" H 4550 7087 50  0000 C CNN
F 2 "" H 4550 7300 50  0001 C CNN
F 3 "" H 4550 7300 50  0001 C CNN
	1    4550 7300
	1    0    0    -1  
$EndComp
Wire Notes Line
	9250 5950 7250 5950
Wire Notes Line
	7250 5950 7250 550 
Wire Notes Line
	7250 550  9250 550 
Wire Notes Line
	9250 550  9250 5950
Text Notes 7300 5900 0    50   ~ 0
Only applicable for hydro-thermic system!
Wire Wire Line
	2600 4150 2600 4050
Wire Wire Line
	2600 4050 2350 4050
Wire Wire Line
	2350 4050 2350 4350
$Comp
L Local:RelayModule(4C) Module3
U 1 1 5DC89925
P 2450 4850
F 0 "Module3" V 2200 4050 50  0000 R CNN
F 1 "RelayModule(4C)" V 2100 4050 50  0000 R CNN
F 2 "" H 2400 5250 50  0001 C CNN
F 3 "" H 2400 5250 50  0001 C CNN
	1    2450 4850
	0    -1   -1   0   
$EndComp
$Comp
L Local:VReg Module4
U 1 1 5DC8D2F4
P 4550 6800
F 0 "Module4" H 5100 6700 50  0000 C CNN
F 1 "VReg (5V@1A capable, any type)" H 5600 6600 50  0000 C CNN
F 2 "" H 4550 6800 50  0001 C CNN
F 3 "" H 4550 6800 50  0001 C CNN
	1    4550 6800
	1    0    0    -1  
$EndComp
$Comp
L Local:Arduino_Nano_V3 Module1
U 1 1 5DE946C8
P 4850 2050
F 0 "Module1" H 5300 3150 50  0000 C CNN
F 1 "Arduino_Nano_V3" H 5450 3050 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 5000 1100 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 4850 1050 50  0001 C CNN
	1    4850 2050
	1    0    0    -1  
$EndComp
$Comp
L Local:Arduino_Nano_V3 Module2
U 1 1 5DE95655
P 8300 2050
F 0 "Module2" H 7950 3150 50  0000 C CNN
F 1 "Arduino_Nano_V3" H 7800 3050 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 8450 1100 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 8300 1050 50  0001 C CNN
	1    8300 2050
	-1   0    0    -1  
$EndComp
$Comp
L Local:GND_Source #PWR01
U 1 1 5D34A3D1
P 2600 4150
F 0 "#PWR01" H 2600 3850 50  0001 C CNN
F 1 "GND_Source" H 2600 3937 50  0000 C CNN
F 2 "" H 2600 4150 50  0001 C CNN
F 3 "" H 2600 4150 50  0001 C CNN
	1    2600 4150
	1    0    0    -1  
$EndComp
$Comp
L Local:GND_Source #PWR03
U 1 1 5D34A88E
P 4850 3250
F 0 "#PWR03" H 4850 2950 50  0001 C CNN
F 1 "GND_Source" H 4850 3037 50  0000 C CNN
F 2 "" H 4850 3250 50  0001 C CNN
F 3 "" H 4850 3250 50  0001 C CNN
	1    4850 3250
	1    0    0    -1  
$EndComp
$Comp
L Local:GND_Source #PWR05
U 1 1 5D34AE2A
P 8200 3350
F 0 "#PWR05" H 8200 3050 50  0001 C CNN
F 1 "GND_Source" H 8200 3137 50  0000 C CNN
F 2 "" H 8200 3350 50  0001 C CNN
F 3 "" H 8200 3350 50  0001 C CNN
	1    8200 3350
	1    0    0    -1  
$EndComp
$Comp
L Local:LimitSW-HexaLib SW2
U 1 1 5D33ADD4
P 2700 2350
F 0 "SW2" H 3000 2600 50  0000 R CNN
F 1 "Up Limit" H 3000 2150 50  0000 R CNN
F 2 "" H 2700 2350 50  0001 C CNN
F 3 "" H 2700 2350 50  0001 C CNN
	1    2700 2350
	-1   0    0    -1  
$EndComp
$Comp
L Local:LimitSW-HexaLib SW3
U 1 1 5D33B492
P 2700 3050
F 0 "SW3" H 3000 3300 50  0000 R CNN
F 1 "Down Limit" H 3000 2850 50  0000 R CNN
F 2 "" H 2700 3050 50  0001 C CNN
F 3 "" H 2700 3050 50  0001 C CNN
	1    2700 3050
	-1   0    0    -1  
$EndComp
$Comp
L Local:LimitSW-HexaLib SW4
U 1 1 5D33BA0B
P 2700 3750
F 0 "SW4" H 3000 4000 50  0000 R CNN
F 1 "Right Limit" H 3000 3550 50  0000 R CNN
F 2 "" H 2700 3750 50  0001 C CNN
F 3 "" H 2700 3750 50  0001 C CNN
	1    2700 3750
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
