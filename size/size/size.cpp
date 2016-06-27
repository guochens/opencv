#include "stdafx.h" 
#include<iostream>    
#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp> 

using namespace std;
//���ؿ���̨����  
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  

int main()
{
	const char *pstrImageName = "timg.jpg";
	const char *pstrSaveImageName = "���˴�ʦ��001����ͼ.jpg";
	const char *pstrWindowsSrcTitle = "ԭͼ";
	const char *pstrWindowsDstTitle = "����ͼ";

	double fScale = 0.5;      //���ű���  
	CvSize czSize;              //Ŀ��ͼ��ߴ�  

								//���ļ��ж�ȡͼ��    
	IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);
	IplImage *pDstImage = NULL;

	//����Ŀ��ͼ���С  
	czSize.width = pSrcImage->width * fScale;
	czSize.height = pSrcImage->height * fScale;

	//����ͼ������  
	pDstImage = cvCreateImage(czSize, pSrcImage->depth, pSrcImage->nChannels);
	cvResize(pSrcImage, pDstImage, CV_INTER_AREA);

	//��������  
	cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsDstTitle, CV_WINDOW_AUTOSIZE);

	//��ָ����������ʾͼ��  
	cvShowImage(pstrWindowsSrcTitle, pSrcImage);
	cvShowImage(pstrWindowsDstTitle, pDstImage);

	//�ȴ������¼�  
	cvWaitKey();

	//����ͼƬ  
	cvSaveImage(pstrSaveImageName, pDstImage);

	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsDstTitle);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pDstImage);
	return 0;
}