#!/bin/csh

set list = (`ls fitPlots`)

foreach i ($list)
	echo $i
	set firstPart = `echo $i | awk -F "__" '{ print $1 }'`
	set secondPart = `echo $i | awk -F "__" '{ print $2 }'`
	set thirdPart = `echo $i | awk -F "__" '{ print $4 }'`
	set firstParta = `echo $i | awk -F "_" '{ print $1 }'`
	set firstPartb = `echo $firstPart | sed s/"${firstParta}_"/""/g`
	echo "1 = $firstParta et $firstPartb, 2 = $secondPart, 3 = $thirdPart"
	mv fitPlots/$i fitPlots/${firstPartb}_${secondPart}_${thirdPart}_${firstParta}.png
end


