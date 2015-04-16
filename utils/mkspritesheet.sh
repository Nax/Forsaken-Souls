#!/usr/bin/env zsh

# $1 -> Folder
# $2 -> Size
# $3 -> Outfile

rm -rf /tmp/mini;
mkdir /tmp/mini;
rm -rf /tmp/line;
mkdir /tmp/line;

num=0;

for file in $1/Anim*/*.png; do
	convert $file -resize $2x$2 /tmp/mini/img`printf '%08d' $num`.png;
	num=`expr $num + 1`;
done;

sqrt=`ruby -e "p Math::sqrt($num).ceil"`;

used=0;

for i in `seq $sqrt`; do
	arr="";
	for j in `seq $used $(expr $used + $sqrt - 1)`; do
		arr="$arr /tmp/mini/img`printf '%08d' $j`.png"
	done;
	used=`expr $used + $sqrt`;
	convert ${=arr} +append -background none /tmp/line/line`printf '%08d' $i`.png &> /dev/null;
done;

convert /tmp/line/*.png -append -background none $3;
