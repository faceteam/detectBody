---
title: 行人检测-ccv计算机视觉库应用 #文章页面上的显示名称，可以任意修改，不会出现在URL中
date: 2016-05-06 20:30:16 #文章生成时间，一般不改，当然也可以任意修改
categories: 目标检测 #分类
tags: [ccv,行人检测] #文章标签，可空，多标签请用格式，注意:后面有个空格
description: 应用计算机视觉库ccv进行行人检测。
---

## 目标

从静态图片中检测行人，对所有存在的行人进行定位。

## 数据

测试数据[INRIA Person Dataset](http://pascal.inrialpes.fr/data/human/)。

## 算法

ccv是一个开源的计算机视觉库，基于C语言开发，是一种以应用驱动的算法库。此处使用DPM模型进行行人检测，参考[这里](http://libccv.org/doc/doc-dpm/)。该算法文献出自于[The original paper refers to: Object Detection with Discriminatively Trained Part-Based Models, Pedro F. Felzenszwalb, Ross B. Girshick, David McAllester and Deva Ramanan]

## 使用方法

1,下载ccv
	git clone https://github.com/liuliu/ccv.git
2,下载依赖库（在linux等环境下使用）
	sudo apt-get install clang libjpeg-dev libpng-dev libfftw3-dev libgsl0-dev libblas-dev liblinear-dev libblas-dev
3，配置编译
	cd lib
	./configure force
	cd ../bin
	make
第3步将在bin中生成许多可执行文件。
4，使用DPM模型检测图片中a.png中的行人，执行过程中会输出行人检测的结果。
	./dpmdetect ./a.png ../samples/pedestrian.m output.png
5，或检测一批图片，重定向输出到result.txt中
	./dpmdetect filelist.txt ../samples/pedestrian.m > result.txt

## 结果可视化

以上面第5步为例，filelist.txt存储了INRIA数据集中的Test/pos中所有图片的路径，共计288张图片。详见[这里](https://github.com/faceteam/detectBody)。

输出result.txt存储了行人检测的结果，示例如下：
	Test/pos/crop_000001.png 173 78 188 564 0.830314 8
	| 149 112 112 112 0.156994
	| 205 373 112 112 0.071194
	| 149 261 93 149 0.042143
	| 280 261 93 149 -0.178776
	| 187 504 93 131 0.511169
	| 224 504 93 131 0.601668
	| 187 56 93 149 0.529543
	| 243 56 93 149 0.806625
对检测到的每一个行人，均给出上述9行信息。第一行指出图片路径，行人位置，置信度，身体部分个数。余下每一行表示各个部分的位置及置信度。

使用[本项目](https://github.com/faceteam/detectBody)，将result.txt中的结果可视化在图片上，示例如:
![可视化结果][检测结果]
[检测结果]: img/crop_000001.png

## 计算环境

Linux OpenCV
