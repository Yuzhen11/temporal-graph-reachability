#!/bin/bash


#array=("out.amazon-ratings.uniq" "out.elec.uniq" "out.dblp_coauthor.uniq" "out.facebook-wosn-links.uniq" "out.youtube-u-growth.uniq" "out.flickr-growth.uniq")

#1
#array=("out.wikipedia-growth.uniq" "out.edit-frwiki.uniq" "out.edit-dewiki.uniq")

#1
#array=("out.sociopatterns-hypertext.uniq" "out.movielens-10m_ti.uniq" "out.slashdot-threads.uniq" "out.edit-enwikiquote.uniq" "out.epinions.uniq" "out.facebook-wosn-wall.uniq" "out.edit-enwikinews.uniq" "out.enron.uniq" "out.edit-dewiktionary.uniq" "out.stackexchange-stackoverflow.uniq")


#2
#array=("out.citeulike-ut.uniq" "out.bibsonomy-2ut.uniq" "out.wikiconflict.uniq" "out.ca-cit-HepPh.uniq" "out.lastfm_song.uniq") 

#3
#array=("out.delicious-ti.uniq")


#final
#5
#array=("out.amazon-ratings.uniq" "out.bibsonomy-2ut.uniq" "out.ca-cit-HepPh.uniq" "out.citeulike-ut.uniq" "out.dblp_coauthor.uniq")
#5
#array=("out.delicious-ut.uniq" "out.edit-enwiki.uniq" "out.elec.uniq" "out.enron.uniq" "out.epinions.uniq")
#6
#array=("out.facebook-wosn-wall.uniq" "out.flickr-growth.uniq" "out.lastfm_song.uniq" "out.movielens-10m_ti.uniq" "out.munmun_digg_reply.uniq" "out.movielens-10m_rating.uniq")
#6
#array=("out.slashdot-threads.uniq" "out.sociopatterns-hypertext.uniq" "out.stackexchange-stackoverflow.uniq" "out.wikiconflict.uniq" "out.wikipedia-growth.uniq" "out.youtube-u-growth.uniq")


#array=("out.amazon-ratings.uniq" "out.bibsonomy-2ut.uniq" "out.ca-cit-HepPh.uniq" "out.citeulike-ut.uniq" "out.dblp_coauthor.uniq" "out.delicious-ut.uniq"  "out.elec.uniq" "out.enron.uniq" "out.epinions.uniq" "out.facebook-wosn-wall.uniq" "out.flickr-growth.uniq" "out.lastfm_song.uniq" "out.movielens-10m_ti.uniq" "out.munmun_digg_reply.uniq" "out.movielens-10m_rating.uniq" "out.slashdot-threads.uniq" "out.sociopatterns-hypertext.uniq" "out.stackexchange-stackoverflow.uniq" "out.wikiconflict.uniq" "out.wikipedia-growth.uniq" "out.youtube-u-growth.uniq")

#array=("out.amazon-ratings.uniq" "out.ca-cit-HepPh.uniq"  "out.dblp_coauthor.uniq" "out.delicious-ut.uniq"  "out.elec.uniq" "out.enron.uniq" "out.epinions.uniq" "out.facebook-wosn-wall.uniq" "out.flickr-growth.uniq" "out.movielens-10m_rating.uniq" "out.slashdot-threads.uniq"  "out.wikiconflict.uniq" "out.wikipedia-growth.uniq" "out.youtube-u-growth.uniq")

#array=("out.amazon-ratings.uniq")

#array=("out.amazon-ratings.uniq" "out.ca-cit-HepPh.uniq"  "out.dblp_coauthor.uniq" "out.delicious-ut.uniq" "out.enron.uniq" "out.epinions.uniq" "out.flickr-growth.uniq" "out.movielens-10m_rating.uniq" "out.slashdot-threads.uniq"  "out.wikiconflict.uniq" "out.wikipedia-growth.uniq" "out.youtube-u-growth.uniq")

array=("out.enron.uniq")

echo ${#array[@]}
for ((i=0;i<${#array[@]};i++))
do

	file=${array[$i]}
	echo $file
	./temporalChainRank 5 0 ../../temporalDataset/${file}_scc.txt ../../temporalDataset/${file}_query.txt ../../temporalDataset/${file}_info.txt 
	echo 

done

