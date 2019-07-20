EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title "High Current Circuits"
Date "2019-07-20"
Rev "1.0"
Comp "Open Source Research Center"
Comment1 "Source: http://osrc.rip"
Comment2 "License: CC-BY 4.0"
Comment3 "Author: Tibor Áser Veres"
Comment4 "Project: Solar Tracker3S MK I - Designed partially with off the shelf modules for DIY-ers."
$EndDescr
Text HLabel 10400 4100 2    50   Input ~ 0
Speed
Text HLabel 9300 3700 1    50   Output ~ 0
LRMotor
Text HLabel 7100 3700 1    50   Output ~ 0
UDMotor
Text HLabel 4950 4100 2    50   Input ~ 0
PSpeed
Text HLabel 3450 2800 1    50   Output ~ 0
Pomp
Text HLabel 2100 4100 0    50   Input ~ 0
PEnable
$Comp
L Transistor_BJT:BC847 Q5
U 1 1 5DAE6D05
P 2950 4100
F 0 "Q5" H 3141 4146 50  0000 L CNN
F 1 "BC847" H 3141 4055 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3150 4025 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC847SERIES_BC848SERIES_BC849SERIES_BC850SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541d4630a1657" H 2950 4100 50  0001 L CNN
	1    2950 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 5DAE7309
P 2400 4100
F 0 "R15" V 2193 4100 50  0000 C CNN
F 1 "1K" V 2284 4100 50  0000 C CNN
F 2 "" V 2330 4100 50  0001 C CNN
F 3 "~" H 2400 4100 50  0001 C CNN
	1    2400 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 4450 3050 4300
Wire Wire Line
	2550 4100 2750 4100
Wire Wire Line
	2250 4100 2100 4100
$Comp
L Relay:RT314A12 K1
U 1 1 5DAEA218
P 3250 3200
F 0 "K1" H 2821 3154 50  0000 R CNN
F 1 "RT314A12" H 2821 3245 50  0000 R CNN
F 2 "Relay_THT:Relay_SPDT_Schrack-RT1-16A-FormC_RM5mm" H 4800 3150 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=RT1_bistable&DocType=DS&DocLang=English" H 3700 3350 50  0001 C CNN
	1    3250 3200
	1    0    0    1   
$EndComp
Wire Wire Line
	3050 3500 3050 3900
Wire Wire Line
	3050 2800 3050 2900
Wire Wire Line
	3450 2900 3450 2800
$Comp
L Device:R R16
U 1 1 5DB9AC9D
P 4650 4100
F 0 "R16" V 4443 4100 50  0000 C CNN
F 1 "1K" V 4534 4100 50  0000 C CNN
F 2 "" V 4580 4100 50  0001 C CNN
F 3 "~" H 4650 4100 50  0001 C CNN
	1    4650 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 4100 4950 4100
$Comp
L Transistor_FET:IRLIZ44N Q6
U 1 1 5DB9C299
P 4100 4100
F 0 "Q6" H 4305 4146 50  0000 L CNN
F 1 "IRLIZ44N" H 4305 4055 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220F-3_Vertical" H 4350 4025 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irliz44n.pdf" H 4100 4100 50  0001 L CNN
	1    4100 4100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3550 3500 3550 3700
Wire Wire Line
	3550 3700 4000 3700
Wire Wire Line
	4000 3700 4000 3900
Wire Wire Line
	4000 4300 4000 4450
Wire Wire Line
	4300 4100 4500 4100
Text Notes 4150 4300 0    50   ~ 0
Heat sink required!
$Comp
L Device:R R17
U 1 1 5DBAC028
P 7750 4100
F 0 "R17" V 7543 4100 50  0000 C CNN
F 1 "1K" V 7634 4100 50  0000 C CNN
F 2 "" V 7680 4100 50  0001 C CNN
F 3 "~" H 7750 4100 50  0001 C CNN
	1    7750 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	7900 4100 8050 4100
$Comp
L Transistor_FET:IRLIZ44N Q7
U 1 1 5DBAC02F
P 7200 4100
F 0 "Q7" H 7405 4146 50  0000 L CNN
F 1 "IRLIZ44N" H 7405 4055 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220F-3_Vertical" H 7450 4025 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irliz44n.pdf" H 7200 4100 50  0001 L CNN
	1    7200 4100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7100 3700 7100 3900
Wire Wire Line
	7100 4300 7100 4450
Wire Wire Line
	7400 4100 7600 4100
Text Notes 7250 4300 0    50   ~ 0
Heat sink required!
$Comp
L Device:R R18
U 1 1 5DBACCC0
P 9950 4100
F 0 "R18" V 9743 4100 50  0000 C CNN
F 1 "1K" V 9834 4100 50  0000 C CNN
F 2 "" V 9880 4100 50  0001 C CNN
F 3 "~" H 9950 4100 50  0001 C CNN
	1    9950 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	10100 4100 10250 4100
$Comp
L Transistor_FET:IRLIZ44N Q8
U 1 1 5DBACCC7
P 9400 4100
F 0 "Q8" H 9605 4146 50  0000 L CNN
F 1 "IRLIZ44N" H 9605 4055 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220F-3_Vertical" H 9650 4025 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irliz44n.pdf" H 9400 4100 50  0001 L CNN
	1    9400 4100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9300 3700 9300 3900
Wire Wire Line
	9300 4300 9300 4450
Wire Wire Line
	9600 4100 9800 4100
Text Notes 9450 4300 0    50   ~ 0
Heat sink required!
Wire Notes Line
	1200 2000 1200 5500
Wire Notes Line
	1200 5500 6000 5500
Wire Notes Line
	6000 5500 6000 2000
Wire Notes Line
	6000 2000 1200 2000
Text Notes 1300 5400 0    50   ~ 0
Only applicable for hydro-thermic system!
Text Notes 600  900  0    50   ~ 0
Implementing PWM speed control is optional but highly recommended, since the controller(s) will turn on PWM after the relays close, and shut down PWM before releasing the relays, to protect contacts from high current DC switching...\nBut why use relays and not H bridges?! Because: A) This allows use of AC motors if required. B) Relay modules are cheaper, and easier to find a good one then approrpiate high current H bridge at the same price.\nC) That's what we both had available.\n(PWM speed control doesn't work with AC motors however the rest of the circuit should!)
Text Notes 6600 5450 0    50   ~ 0
If speed control is not necessary then Q6-8 and R16-18 are not required,\ninstead pin 14 of K1 as well as UDMotor, and LRMotor goes directly to GND.\n\n(In case of using AC motors and pump, NO contacts of the relay module\nas well as pin 1 of the pump goes to live, while pin 14 of K1, UDMotor,\nand LRMotor goes directly to neutral! PWM is only for DC motors!)
NoConn ~ 3350 3500
$Comp
L Local:12V_Source #PWR0130
U 1 1 5DDE5C0C
P 3050 2800
F 0 "#PWR0130" H 3050 3050 50  0001 C CNN
F 1 "12V_Source" H 3050 2973 50  0000 C CNN
F 2 "" H 3050 2800 50  0001 C CNN
F 3 "" H 3050 2800 50  0001 C CNN
	1    3050 2800
	1    0    0    -1  
$EndComp
$Comp
L Local:GND_Source #PWR0134
U 1 1 5DDE96F4
P 3050 4450
F 0 "#PWR0134" H 3050 4150 50  0001 C CNN
F 1 "GND_Source" H 3050 4237 50  0000 C CNN
F 2 "" H 3050 4450 50  0001 C CNN
F 3 "" H 3050 4450 50  0001 C CNN
	1    3050 4450
	1    0    0    -1  
$EndComp
$Comp
L Local:GND_Source #PWR040
U 1 1 5D3705F5
P 4000 4450
F 0 "#PWR040" H 4000 4150 50  0001 C CNN
F 1 "GND_Source" H 4000 4237 50  0000 C CNN
F 2 "" H 4000 4450 50  0001 C CNN
F 3 "" H 4000 4450 50  0001 C CNN
	1    4000 4450
	1    0    0    -1  
$EndComp
$Comp
L Local:GND_Source #PWR042
U 1 1 5D370A55
P 7100 4450
F 0 "#PWR042" H 7100 4150 50  0001 C CNN
F 1 "GND_Source" H 7100 4237 50  0000 C CNN
F 2 "" H 7100 4450 50  0001 C CNN
F 3 "" H 7100 4450 50  0001 C CNN
	1    7100 4450
	1    0    0    -1  
$EndComp
$Comp
L Local:GND_Source #PWR043
U 1 1 5D370EBB
P 9300 4450
F 0 "#PWR043" H 9300 4150 50  0001 C CNN
F 1 "GND_Source" H 9300 4237 50  0000 C CNN
F 2 "" H 9300 4450 50  0001 C CNN
F 3 "" H 9300 4450 50  0001 C CNN
	1    9300 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 4100 8050 4750
Wire Wire Line
	8050 4750 10250 4750
Wire Wire Line
	10250 4100 10250 4750
Wire Wire Line
	10250 4100 10400 4100
Connection ~ 10250 4100
$EndSCHEMATC
