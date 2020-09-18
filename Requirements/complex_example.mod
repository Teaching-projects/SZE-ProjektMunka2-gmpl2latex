#######################
## SETS ###############
#######################

set Resources; #!< The set of resources
set Products; #!< The set of products

#######################
## PARAMETERS #########
#######################

#! The available amount for resource <r>
#! mu: l
param stock{r in Resources};

#! The profit gained by selling a portion of product <p>
#! mu: HUF/pcs
param price{p in Products}

#! The amount of resource <r> needed to produce one portion of product <p>
#! mu: l/pcs
param need{p in Products, r in Resources};

#######################
## VARIABLES ##########
#######################

#! The number of portions we produce of product <p>
#! mu: pcs
var produce{p in Products} >= 0; 


#######################
## CONSTRAINTS ########
#######################

#! This equation ensures that the amount of resouce <r> required to produce all of the products is within the available stock.

s.t. Resource_Need{r in Resources}:  
    sum{p in Products} produce[p] * need[p,r] <= stock[r];


#######################
## OBJECTIVE ##########
#######################

#! The objective is to maximize the profit.

maximize Profit:
    sum{p in Products} produce[p] * price[p];
