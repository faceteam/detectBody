#include <string>
#include <vector>

#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include"filesystem.h"

using namespace std;
using namespace cv;

int main()
{
	string testDir = "E:/teamPro/detectBody/build/test";
	vector<string> pics;
	FileSystem::readDir(testDir, "jpg", pics);
	string resultDir = "E:/teamPro/detectBody/build/testresult";
	if (!FileSystem::isExists(resultDir))
	{
		FileSystem::makeDir(resultDir);
	}
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	for (int i = 0; i < pics.size(); i++)
	{
		Mat tmpsrc = imread(testDir + "/" + pics[i]);
		vector<Rect> bodyrects,rectfilter;
		hog.detectMultiScale(tmpsrc, bodyrects, 0, Size(4, 4), Size(20, 20), 1.05, 2);
		for (int s = 0; s < bodyrects.size(); s++)
		{
			Rect rtmp(bodyrects[s].x, bodyrects[s].y, bodyrects[s].width, bodyrects[s].height);
			rtmp.x += rtmp.width*0.1;
			rtmp.y += rtmp.height*0.1;
			rtmp.width = rtmp.width*0.8;
			rtmp.height = rtmp.height*0.8;
			rectangle(tmpsrc, rtmp, Scalar(255, 0, 0), 2, 8, 0);
		}
		//size_t j;
		//for (size_t w = 0; w < bodyrects.size(); w++)
		//{
		//	Rect r = bodyrects[w];
		//	//下面的这个for语句是找出所有没有嵌套的矩形框r,并放入found_filtered中,如果有嵌套的
		//	//话,则取外面最大的那个矩形框放入found_filtered中
		//	for ( j = 0; j <bodyrects.size(); j++)
		//		if (j != w && (r&bodyrects[j]) == r)
		//			break;
		//	if (j == bodyrects.size())
		//		rectfilter.push_back(r);
		//}
		//for (int s = 0; s < rectfilter.size(); s++)
		//{
		//	Rect rtmp(rectfilter[s].x, rectfilter[s].y, rectfilter[s].width, rectfilter[s].height);
		//	rtmp.x += rtmp.width*0.1;
		//	rtmp.y += rtmp.height*0.1;
		//	rtmp.width = rtmp.width*0.8;
		//	rtmp.height = rtmp.height*0.8;
		//	rectangle(tmpsrc, rtmp, Scalar(255, 0, 0), 2, 8, 0);
		//}
		string savepath = resultDir + "/" + pics[i];
		imwrite(savepath, tmpsrc);
	}

	return 0;
}