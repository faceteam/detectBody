//#include <string>
//#include <vector>
//
//#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
//#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
//#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
//#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/objdetect/objdetect.hpp>
//
//#include"filesystem.h"
//
//using namespace std;
//using namespace cv;
//
//int main(int argc, char* argv)
//{
//	CascadeClassifier cc("haarcascade_upperbody.xml");
//	string dir = "./cam";
//	vector<string> imgpaths;
//	FileSystem::readDirwithpath(dir, "jpg", imgpaths);
//	string outdir = "./camout";
//	if (!FileSystem::isExists(outdir))
//	{
//		FileSystem::makeDir(outdir);
//	}
//	for (int i = 0; i < imgpaths.size(); i++)
//	{
//		string imgname = imgpaths[i].substr(imgpaths[i].find_last_of("/"));
//		Mat src = imread(imgpaths[i]);
//		vector<Rect> rects;
//		cc.detectMultiScale(src, rects, 1.1, 2, 0, Size(30, 10), Size(src.rows, src.cols));
//		for (int j = 0; j < rects.size(); j++)
//		{
//			rectangle(src, rects[j], Scalar(250, 60, 60), src.rows / 500 + 1, 8);
//		}
//		string outpath = outdir + imgname;
//		imwrite(outpath,src);
//	}
//	return 0;
//}