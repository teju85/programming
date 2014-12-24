#!/bin/bash
# COMMENTS:
#   Simple script to download all slides for a talk from slideshare.net
# USAGE:
#   


link=$1
outdir='output-output'
tmp="/tmp/$$-slideshare"

echo "Downloading from the link: $link ..."
wget --header="User-Agent: Mozilla/5.0 (Windows NT 6.0)" -O $tmp "$link"

echo "Creating the output directory ..."
mkdir -p $outdir

echo "Getting image links from the page ..."
cwd=`pwd`
cd $outdir
for image in `grep 'data-full' $tmp | sed -e 's/.*data-full="//' -e 's/".*//'`; do
    out=`basename $image | sed -e 's/\?.*//'`
    wget -O $out $image
done
cd $cwd

echo "Getting the title of the page ..."
title=`grep '<title>' $tmp | sed -e 's/<title>//' -e 's/<\/title>//' -e 's/  //g' | head -n1`
echo "Title='$title' ..."

echo "Cleaning up ..."
rm -f $tmp

echo
echo "You will find the slides under the dir: $outdir

Optional:
If you want to convert these images into a pdf file, follow the steps below:
1. Install Cute PDF Writer, if you haven't done already.
2. Go to the above output directory and select all the files.
3. Right click -> 'Print'
4. In the preview window, just cross-check the order of the slides.
5. Click on 'Print'
6. Choose a destination for this pdf file.
"
