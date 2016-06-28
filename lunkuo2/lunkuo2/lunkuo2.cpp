#include "stdafx.h" 
#include<iostream>    
#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp> 

using namespace std;
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  
IplImage *g_pGrayImage = NULL;
const char *pstrWindowsBinaryTitle = "��ֵͼ";
const char *pstrWindowsOutLineTitle = "����ͼ";
CvSeq *g_pcvSeq = NULL;

void on_trackbar(int pos)
{
	// תΪ��ֵͼ  
	IplImage *pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);
	cvThreshold(g_pGrayImage, pBinaryImage, pos, 255, CV_THRESH_BINARY);
	// ��ʾ��ֵͼ  
	cvShowImage(pstrWindowsBinaryTitle, pBinaryImage);

	CvMemStorage* cvMStorage = cvCreateMemStorage();
	// �������������ؼ�⵽�������ĸ���  
	cvFindContours(pBinaryImage, cvMStorage, &g_pcvSeq);

	IplImage *pOutlineImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 3);
	int _levels = 5;
	cvZero(pOutlineImage);
	cvDrawContours(pOutlineImage, g_pcvSeq, CV_RGB(255, 0, 0), CV_RGB(0, 255, 0), _levels);
	cvShowImage(pstrWindowsOutLineTitle, pOutlineImage);

	cvReleaseMemStorage(&cvMStorage);
	cvReleaseImage(&pBinaryImage);
	cvReleaseImage(&pOutlineImage);
}

int main(int argc, char** argv)
{
	const char *pstrWindowsSrcTitle = "ԭͼ(http://blog.csdn.net/MoreWindows)";
	const char *pstrWindowsToolBarName = "��ֵ��";

	// ���ļ��м���ԭͼ  
	IplImage *pSrcImage = cvLoadImage("timg.jpg", CV_LOAD_IMAGE_UNCHANGED);
	// ��ʾԭͼ  
	cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	cvShowImage(pstrWindowsSrcTitle, pSrcImage);

	// תΪ�Ҷ�ͼ  
	g_pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pSrcImage, g_pGrayImage, CV_BGR2GRAY);

	// ������ֵͼ������ͼ����  
	cvNamedWindow(pstrWindowsBinaryTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsOutLineTitle, CV_WINDOW_AUTOSIZE);


	// ������    
	int nThreshold = 0;
	cvCreateTrackbar(pstrWindowsToolBarName, pstrWindowsBinaryTitle, &nThreshold, 254, on_trackbar);

	on_trackbar(1);

	cvWaitKey(0);

	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsBinaryTitle);
	cvDestroyWindow(pstrWindowsOutLineTitle);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&g_pGrayImage);
	return 0;
}