var KF >= 0; #! The amount of Kisfroccs we sell
var NF >= 0; #! The amount of Nagyfroccs we sell
var HL >= 0; #! The amount of Hosszulepes we sell


#! This equation enforces that we dont use more than 100 l of wine
s.t. Wine:  
    1*KF + 2*NF + 1*HL <= 100;


#! This is a similar constraint that limits the usage of carbonated water to 150l
s.t. CarbonatedWater:  
    1*KF + 1*NF + 2*HL <= 150;


#! The objective is to maximize the profit with 120 210 and 140 HUF of a price for a portion of Kisfroccs Nagyfroccs Hosszulepes respectively

maximize Profit:
    120*KF + 210*NF + 140*HL;