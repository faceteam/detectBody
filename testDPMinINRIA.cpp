#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace boost::algorithm;
using namespace cv;
using namespace std;
int main()
{
	/*
	Test/pos/crop_000001.png 173 78 188 564 0.830314 8
	| 149 112 112 112 0.156994
	| 205 373 112 112 0.071194
	| 149 261 93 149 0.042143
	| 280 261 93 149 -0.178776
	| 187 504 93 131 0.511169
	| 224 504 93 131 0.601668
	| 187 56 93 149 0.529543
	| 243 56 93 149 0.806625
	....
	*/
	ifstream debody("ttresult.txt");
	vector<string> imgspath;
	vector<Rect> imgrect;
	vector<double> bodyconfi;
	vector<int> regionsize;
	vector<vector<double>> parts;
	vector<Rect> heads;
	string outdir = "./outdir";
	ofstream tozj("tozj.txt");
	if (debody.is_open()&&tozj.is_open())
	{
		string line;
		int lineID = 0;
		while (getline(debody, line))
		{
			vector<string> linevec;
			boost::algorithm::split(linevec, line, is_any_of(" "));
			if (lineID % 9 == 0)
			{
				if(linevec.size() != 7)
				{ 
					cerr << "bad check " << lineID << " " << line; 
				}
				if (atof(linevec[5].c_str()) > 1.5)
				{
					//人体检测置信度高于1.5，才输出
					imgspath.push_back(linevec[0]);
					int body_x = atoi(linevec[1].c_str());
					int body_y = atoi(linevec[2].c_str());
					int body_w = atoi(linevec[3].c_str());
					int body_h = atoi(linevec[4].c_str());
					float bodycon = atof(linevec[5].c_str());
					imgrect.push_back(Rect(body_x, body_y, body_w, body_h));
					bodyconfi.push_back(bodycon);

					float a = 0.23;
					int head_x = body_x + a*body_w;
					int head_y = max(0, (int)(body_y - a*body_w));
					int head_w = (1 - 2 * a)*body_w;
					int head_h = head_w;
					Rect head(head_x, head_y, head_w, head_h);
					heads.push_back(head);
					tozj << linevec[0] << " " << body_x << " " << body_y << " " << body_w << " " << body_h << " "
						<< head_x << " " << head_y << " " << head_w << " " << head_h << " " << bodycon << "\n";
				}

			}
			else
			{
				if (linevec.size() != 6){ 
					cerr << "bad check " << lineID << " " << line; 
				}
				vector<double> tmp;
				for (int i = 0; i < 5; i++)
				{
					tmp.push_back(atof(linevec[i+1].c_str()));
				}
				parts.push_back(tmp);
			}
			lineID++;
		}
	}
	debody.close();
	for (int i = 0; i < imgspath.size(); i++)
	{
		string path = imgspath[i];
		Mat img = imread(path);
		rectangle(img, imgrect[i], Scalar(255, 0, 0), img.rows / 300 + 1, 8, 0);
		rectangle(img, heads[i], Scalar(0, 255, 0), img.rows / 300 + 1, 8, 0);
		string tmp = to_string(bodyconfi[i]);
		string tmp1 = tmp.substr(0, tmp.find(".") + 3);
		putText(img, tmp1, Point(imgrect[i].x, imgrect[i].y + 10), 1, 1.0, Scalar(0, 255, 0));
		//for (int j = 0; j < 8; j++)
		//{
		//	rectangle(img, Rect(parts[8 * i + j][0], parts[8 * i + j][1], 
		//		               parts[8 * i + j][2], parts[8 * i + j][3]), 
		//					   Scalar(0, 0, 255), img.rows / 500 + 1, 8, 0);
		//	string tmp = to_string(parts[8 * i + j][4]);
		//	string tmp1 = tmp.substr(0, tmp.find(".") + 2);
		//	putText(img, tmp1, Point(parts[8 * i + j][0], parts[8 * i + j][1] + 10), 1, 1.0, Scalar(255, 255, 0));
		//}
		//string outpath = outdir + "/" + path.substr(path.find_last_of("/"));
		imwrite(path, img);
	}
	return 0;
}