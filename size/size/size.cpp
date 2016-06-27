#include "stdafx.h" 
#include<iostream>    
#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp> 

using namespace std;
//隐藏控制台窗口  
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  

int main()
{
	const char *pstrImageName = "timg.jpg";
	const char *pstrSaveImageName = "冲浪大师赛001缩放图.jpg";
	const char *pstrWindowsSrcTitle = "原图";
	const char *pstrWindowsDstTitle = "缩放图";

	double fScale = 0.5;      //缩放倍数  
	CvSize czSize;              //目标图像尺寸  

								//从文件中读取图像    
	IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);
	IplImage *pDstImage = NULL;

	//计算目标图像大小  
	czSize.width = pSrcImage->width * fScale;
	czSize.height = pSrcImage->height * fScale;

	//创建图像并缩放  
	pDstImage = cvCreateImage(czSize, pSrcImage->depth, pSrcImage->nChannels);
	cvResize(pSrcImage, pDstImage, CV_INTER_AREA);

	//创建窗口  
	cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsDstTitle, CV_WINDOW_AUTOSIZE);

	//在指定窗口中显示图像  
	cvShowImage(pstrWindowsSrcTitle, pSrcImage);
	cvShowImage(pstrWindowsDstTitle, pDstImage);

	//等待按键事件  
	cvWaitKey();

	//保存图片  
	cvSaveImage(pstrSaveImageName, pDstImage);

	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsDstTitle);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pDstImage);
	return 0;
}