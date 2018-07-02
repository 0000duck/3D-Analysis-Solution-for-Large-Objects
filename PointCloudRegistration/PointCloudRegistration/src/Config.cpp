
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include<string>
#include "WriteCvmat.h"
#include "config.h"
#include "Calibrate.h"
#include "PairAlign.h"
#include "pointCloudProcess.h"
//extrinsic1 ��ʾ��1���豸��2���豸�Ŀռ�任����1T2
CvMat extrinsic[12];//[0]:��1�ŵ����ƶ���2��
//Eigen::Matrix4f Eigen_extrinsic[12];
CvMat translation;//�豸��������
//Eigen::Matrix4f Eigen_translation;
int horizontalScanNum;//ˮƽ�ɼ����������豸����
int verticalScanNum;//��ֱ�ɼ�����������������
float risingDistance;//ÿ���ƶ��ľ���
std::string horizontalFileName[6][12];
std::string verticalFileName[6];

void Get_ConfigArgv(){
	CvFileStorage *fs;
	CvFileNode* m;
	fs = cvOpenFileStorage("./config/config.xml", 0, CV_STORAGE_READ);

	board_size.width = cvReadIntByName(fs, 0, "board_width", 0);
	board_size.height = cvReadIntByName(fs, 0, "board_height", 0);
	square_size.width = cvReadRealByName(fs, NULL, "board_width");
	square_size.height = cvReadRealByName(fs, NULL, "board_height");
	total_clude = cvReadIntByName(fs, 0, "cludenum", 0);
	Registration_flag = cvReadIntByName(fs, 0, "Registration_flag",0);
	HorizontalRegistrationModel = cvReadIntByName(fs, NULL, "HorizontalRegistrationModel");
	VerticalRegistrationModel = cvReadIntByName(fs, NULL, "VerticalRegistrationModel");

	Camera_ID == cvReadIntByName(fs, 0, "Camera_ID", 0);
	KSearchnum = cvReadIntByName(fs, 0, "KSearchnum", 0);
	MaxCorrespondenceDistance = cvReadRealByName(fs, NULL, "MaxCorrespondenceDistance"); //��Ӧ��֮��������루0.1��, ����׼�����У����Դ��ڸ���ֵ�ĵ�
	LeafSize = cvReadRealByName(fs, NULL, "LeafSize");
	TransformationEpsilon = cvReadRealByName(fs, NULL, "TransformationEpsilon");//����������
	downsample_flag = cvReadIntByName(fs, NULL, "downsample_flag");
	Cali_Pic_Num = cvReadIntByName(fs, NULL, "Cali_Pic_Num");

	horizontalScanNum = cvReadIntByName(fs, NULL, "horizontalScanNum");
	verticalScanNum = cvReadIntByName(fs, NULL, "verticalScanNum");
	risingDistance = cvReadRealByName(fs, NULL, "risingDistance");

	m= cvGetFileNodeByName(fs, 0, "loadData");
	pCP.LeafSize = cvReadRealByName(fs, m, "LeafSize");
	pCP.MeanK = cvReadIntByName(fs, m, "MeanK");
	pCP.StddevMulThresh=cvReadRealByName(fs, m, "StddevMulThresh");
	pCP.filter_flag = cvReadIntByName(fs, m, "filter_flag");
	pCP.downsample_flag = cvReadIntByName(fs, m, "downsample_flag");

	for (int j = 1; j <= verticalScanNum; j++){
		for (int i = 1; i <= horizontalScanNum; i++){
			horizontalFileName[j - 1][i - 1] = "./OriginalPointCloud/" + std::to_string(j) +"_layer/"+ std::to_string(i) + "_point_cloud.ply";
		}
		verticalFileName[j - 1] = "./HorizontalResult/" + std::to_string(j) + "_layer.ply";
	}
	cvReleaseFileStorage(&fs);
}

void Get_extrinsic(){
	writeCvmat();
	CvFileStorage *fs;
	fs = cvOpenFileStorage("./config/extrinsic.xml", 0, CV_STORAGE_READ);
	translation = *(CvMat *)cvReadByName(fs, NULL, "translation");
	for (int i = 0; i < translation.rows; i++)
	{ 
		for (int j = 0; j < translation.cols; j++)
		{
			printf("mat[%d][%d] = %f\n", i, j, *(translation.data.fl + j + i * translation.rows));
		}
		cout << endl;
	}
	for (int i = 1; i <= 1;i++){
		std::string ex_mat = "extrinsic" + std::to_string(i);
		extrinsic[i-1] = *(CvMat *)cvReadByName(fs, NULL, ex_mat.c_str());
	}
	cvReleaseFileStorage(&fs);	
}