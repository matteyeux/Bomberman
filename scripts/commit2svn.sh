#!/bin/bash
# SVN sucks

rm -rf ~/svn
mkdir -p ~/svn
svn co --username hauteb_m "https://rendu-svn.etna-alternance.net/v2/2021_Bachelor%20-%20Octobre_TIC-DVC3_9_0-5034/Bomberman/hauteb_m/" ~/svn/bomberman

cp -r doxyfile fonts images include Makefile map.txt README.md src ~/svn/bomberman/
cd ~/svn/bomberman && svn add --force * && svn commit -m "update files"
