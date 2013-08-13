#!/bin/sh

function rename_raws()
{
    RAWIMG_LIST=$(ls rawimgs/ver*)

    for img in $RAWIMG_LIST ; do
        #echo $img;
        no=$(echo $img| awk -F. '{print $3}')
        #echo $no;
        newname="namefmt/verify.$no.bmp";
        cp -v $img $newname;
    done
}

function test_veri_split()
{
    rm -vf namefmt/*noise*.bmp
    rm -vf namefmt/*canny*.bmp
    SRC_LIST=$(ls namefmt/verify*.bmp|grep -v noise | grep -v canny | head -n 500);
    for img in $SRC_LIST ; do
        ./veridt $img;
        # sleep 1;
    done
}

function opencv_create_examples()
{
    
    true;    
}

function opencv_train()
{
    cd pos
    ls |grep -v txt | awk '{print $1 " 1 0 0 30 30"}' > pos.txt
    pos_num=$(wc -l pos.txt | awk '{print $1}');
    rpos_num=$(($pos_num - 500));
    cd ..

    cd neg
    ls |grep -v txt > neg.txt
    neg_num=$(wc -l neg.txt | awk '{print $1}');
    rneg_num=$(($neg_num - 0));
    cd ..

    rm -vf verify.vec
    opencv_createsamples -info pos/pos.txt -vec verify.vec -num $pos_num -bg neg/neg.txt

    rm -vf trdata/*
    opencv_traincascade -data trdata -vec verify.vec -bg neg/neg.txt -numStages 16 -numPos $rpos_num -numNeg $rneg_num -minHitRate 0.999 

    # 这步可能用到1G的内存。
    # stage可调整，有的可用12,13
    # acceptanceRatio 指的是精度，越小精度越大
    # 在达到0.000412662或者更少的时候，就差不多了
    # 达到了7.83885e-07说明过度训练了。
    # 正样本数量与负样本数量大概在2:1

    true;
}

set -x;

#rename_raws;
test_veri_split;

#opencv_train;

