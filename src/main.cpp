#include <string>
#include <iostream>
#include <io.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define classSum 3//定义目录（分类）数量（目录以数字命名）
#define ImagePath "src\\samples\\" //源文件存储目录。该目录下是以数字命名的文件夹
#define suffix "\\*.png"  //文件后缀
#define imageRows 8    //定义新图片是8*16
#define imageCols 16  
#define resizedPath "src\\samples\\resized\\"//存放新图像的目录。该目录下是以数字命名的文件夹

int main()
{
    for (int i = 0; i < classSum; i++)
	{
		char temp[256];
		int k = 0;
		sprintf_s(temp, "%d", i);//把数字转换成字符，即目录名。
		//sprintf_s(temp,%d,i+65);//若从A开始，i+65.（查ASCII表）
		string path=ImagePath;
		string su=suffix;
		string inPath = path + temp +su;
        cout<<inPath<<endl;
		//用于查找的句柄
		intptr_t handle;
		struct _finddata_t fileinfo;
		//第一次查找
		handle = _findfirst(inPath.c_str(), &fileinfo);
		if (handle == -1)
			cout << "error!" << endl;

		//遍历文件
		do 
		{
			//找到的文件的文件名
			std::string imgname;
			imgname = string(ImagePath )+ temp + "\\" + fileinfo.name;
			string imgrename = string(resizedPath) + temp + "\\" + fileinfo.name;
			Mat src = imread(imgname);
			 if (src.empty())
			 {
			 	std::cout << "can not load image \n" << std::endl;
			 }
			 else
			 {
				 // 将所有图片大小统一转化。
				 resize(src,src, Size(imageRows, imageCols), (0, 0), (0, 0), INTER_AREA);
				 imwrite(imgrename,src);
				 cout<<imgname<<"  has resized"<<endl;
			 }
		} while (!_findnext(handle, &fileinfo));
		_findclose(handle);
	}
	cout << "over!" << endl;
    return 0;
}