#!/bin/bash

v=2000000
sd=4
td=10
pi=100


scc=_scc.txt
query=_query.txt
info=_info.txt
queryNum=1000

function tran {
	echo $1
	./temporalChainRank 5 0 ../../random/$1_scc.txt ../../random/$1_query.txt ../../random/$1_info.txt 
	echo 
}
	
varV=(1000000 2000000 4000000 8000000)
for ((i=0;i<4;++i))
do
	v=${varV[$i]}
	let "se=$v*$sd"
	#echo "n=$v sd=$sd td=$td pi=$pi"
	#./GTgraph-rmat -n $v -m $se
	#./change sample.gr syn_power_v$v $td $pi
	tran syn_random_v$v
	
done
v=2000000

varPI=(50 100 150 200)
for ((i=0;i<4;++i))
do
	pi=${varPI[$i]}
	let "se=$v*$sd"
	#echo "n=$v sd=$sd td=$td pi=$pi"
	#./GTgraph-rmat -n $v -m $se
	#./change sample.gr syn_power_pi$pi $td $pi
	tran syn_random_pi$pi
done
pi=100

varSD=(2 4 6 8)
for ((i=0;i<4;++i))
do
	sd=${varSD[$i]}
	let "se=$v*$sd"
	#echo "n=$v sd=$sd td=$td pi=$pi"
	#./GTgraph-rmat -n $v -m $se
	#./change sample.gr syn_power_sd$sd $td $pi
	tran syn_random_sd$sd
done
sd=4

varTD=(5 10 15 20)
for ((i=0;i<4;++i))
do
	td=${varTD[$i]}
	let "se=$v*$sd"
	#echo "n=$v sd=$sd td=$td pi=$pi"
	#./GTgraph-rmat -n $v -m $se
	#./change sample.gr syn_power_td$td $td $pi
	tran syn_random_td$td
done
td=10



