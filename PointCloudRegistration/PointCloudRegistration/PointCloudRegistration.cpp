// �������̨Ӧ�ó������ڵ㡣
//�ص���Microsoft���ŵ�����
//
// Created by �쿭 on 17/4/4.
//
#include "stdafx.h"

#include "PairAlign.h"
#include "config.h"

#include <pcl/visualization/cloud_viewer.h>  
#include <iostream>  
#include <pcl/io/io.h>  
#include <pcl/io/pcd_io.h>  

#include <cv.h>
#include <highgui.h>

int _tmain(int argc, char** argv)
{
	Get_extrinsic();
	Get_ConfigArgv();
	std::vector<PCD, Eigen::aligned_allocator<PCD> > data; //ģ��
	loadData2(horizontalScanNum, horizontalFileName , data); //��ȡpcd�ļ����ݣ����������	
	HorizontalAccurateRegistration(data);

	VerticalAccurateRegistration(data);
	//AccurateRegistration2(data);//��ϸƴ��

	return 0;
}

/*������־�������ȡ����*/