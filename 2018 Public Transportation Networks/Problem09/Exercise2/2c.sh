#!/bin/bash
echo "" > "./results.out"
iterations=200;
a=50;
b=0;
bound=500;
for T in `seq 1 $iterations`
do
	cS1=$(( RANDOM%a + b ))
	cS2=$(( RANDOM%a + b ))
	cA1=$(( RANDOM%a + b ))
	cA2=$(( RANDOM%a + b ))
	cB1=$(( RANDOM%a + b ))
	cB2=$(( RANDOM%a + b ))
	cC1=$(( RANDOM%a + b ))
	cC2=$(( RANDOM%a + b ))
	cD1=$(( RANDOM%a + b ))
	cD2=$(( RANDOM%a + b ))
	cE1=$(( RANDOM%a + b ))
	cE2=$(( RANDOM%a + b ))
	cT1=$(( RANDOM%a + b ))
	cT2=$(( RANDOM%a + b ))

	b11=$(( RANDOM%a + b ))
	b21=$(( RANDOM%a + b ))
	b31=$(( RANDOM%a + b ))
	b41=$(( RANDOM%a + b ))
	b51=$(( RANDOM%a + b ))
	b12=$(( RANDOM%a + b ))
	b22=$(( RANDOM%a + b ))
	b32=$(( RANDOM%a + b ))
	b42=$(( RANDOM%a + b ))
	b52=$(( RANDOM%a + b ))

	uS=$(( RANDOM%a + b ))
	uA=$(( RANDOM%a + b ))
	uB=$(( RANDOM%a + b ))
	uC=$(( RANDOM%a + b ))
	uD=$(( RANDOM%a + b ))
	uE=$(( RANDOM%a + b ))
	uT=$(( RANDOM%a + b ))
	
	echo "Maximize" > "./test.lp"

	echo "$cS1 S1 + $cS2 S2 + $cA1 A1 + $cA2 A2 + $cB1 B1 + $cB2 B2 + $cC1 C1 + $cC2 C2 + $cD1 D1 + $cD2 D2 + $cE1 E1 + $cE2 E2 + $cT1 T1 + $cT2 T2" >> "./test.lp"

	echo "Subject To" >> "./test.lp"

	echo "S1-A1-B1 <= $b11" >> "./test.lp"
	echo "A1-C1-D1 <= $b21" >> "./test.lp"
	echo "B1+C1-E1 <= $b31" >> "./test.lp"
	echo "D1+E1-T1 <= $b41" >> "./test.lp"

	echo "S2-A2-B2 <= $b12" >> "./test.lp"
	echo "A2-C2-D2 <= $b22" >> "./test.lp"
	echo "B2+C2-E2 <= $b32" >> "./test.lp"
	echo "D2+E2-T2 <= $b42" >> "./test.lp"

	echo "S1+S2 <= $uS" >> "./test.lp"
	echo "A1+A2 <= $uA" >> "./test.lp"
	echo "B1+B2 <= $uB" >> "./test.lp"
	echo "C1+C2 <= $uC" >> "./test.lp"
	echo "D1+D2 <= $uD" >> "./test.lp"
	echo "E1+E2 <= $uE" >> "./test.lp"
	echo "T1+T2 <= $uT" >> "./test.lp"

	echo "Bounds" >> "./test.lp"
	echo "-$bound <= S1 <= +$bound" >> "./test.lp"
	echo "-$bound <= A1 <= +$bound" >> "./test.lp"
	echo "-$bound <= B1 <= +$bound" >> "./test.lp"
	echo "-$bound <= C1 <= +$bound" >> "./test.lp"
	echo "-$bound <= D1 <= +$bound" >> "./test.lp"
	echo "-$bound <= E1 <= +$bound" >> "./test.lp"
	echo "-$bound <= T1 <= +$bound" >> "./test.lp"

	echo "-$bound <= S2 <= +$bound" >> "./test.lp"
	echo "-$bound <= A2 <= +$bound" >> "./test.lp"
	echo "-$bound <= B2 <= +$bound" >> "./test.lp"
	echo "-$bound <= C2 <= +$bound" >> "./test.lp"
	echo "-$bound <= D2 <= +$bound" >> "./test.lp"
	echo "-$bound <= E2 <= +$bound" >> "./test.lp"
	echo "-$bound <= T2 <= +$bound" >> "./test.lp"

	echo "End" >> "./test.lp"
	echo "read ./test.lp optimize write solution ./test.sol" | scip -q
	echo "C: $cS1 $cS2 $cA1 $cA2 $cB1 $cB2 $cC1 $cC2 $cD1 $cD2 $cE1 $cE2 $cT1 $cT2" >> "./results.out"
	echo "B: $b11 $b21 $b31 $b41 $b12 $b22 $b32 $b42" >> "./results.out"
	echo "U: $uS $uA $uB $uC $uD $uE $uT" >> "./results.out"
	cat "./test.sol" >> "./results.out"
done
rm "./test.lp"
rm "./test.sol"
