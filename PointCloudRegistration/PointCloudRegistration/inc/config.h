
#ifndef CONFIG_H
#define CONFIG_H
#include "Calibrate.h"
#include "PairAlign.h"

extern CvMat extrinsic[12];
extern CvMat translation;//�豸��������

//extrinsic1 ��ʾ��1���豸��2���豸�Ŀռ�任����1T2
extern int horizontalScanNum;//ˮƽ�ɼ����������豸����
extern int verticalScanNum;//��ֱ�ɼ�����������������
extern float risingDistance;//ÿ���ƶ��ľ���
extern std::string horizontalFileName[6][12];
extern std::string verticalFileName[6];
void Get_ConfigArgv();
void Get_extrinsic();

#endif