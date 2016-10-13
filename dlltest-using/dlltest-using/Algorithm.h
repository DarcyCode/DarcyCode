#pragma once
#include <opencv.hpp>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <stack>
// test
#define PI 3.1415926

using namespace cv;
using namespace std;

// get pixel by mouse selection
//************************************
// Method:    GetLocPixel
// FullName:  GetLocPixel
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Mat img
//************************************
void GetLocPixel(Mat img);
//************************************
// Method:    on_Mouse
// FullName:  on_Mouse
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int event
// Parameter: int x
// Parameter: int y
// Parameter: int flags
// Parameter: void * param
//************************************
void on_Mouse(int event, int x, int y, int flags, void *param);

//************************************
// Method:    colorDetect. Extracting pixels whose values are between minTh and maxTh, something like inRange(), difference is the hue.
// FullName:  colorDetect
// Access:    public 
// Returns:   cv::Mat
// Qualifier:
// Parameter: Mat src, U8CX
// Parameter: Vec3b minTh
// Parameter: Vec3b maxTh
//************************************
Mat colorDetect(Mat src, Vec3b minTh, Vec3b maxTh = Vec3b(255, 255, 255));
Mat Get1ChannelMasks(Mat src, uchar minTh, uchar maxTh);

/*-------fourier-mellin transform-----------*/
Point phaseCorr(const Mat& src1, const Mat& src2);

Mat fft2(const Mat& src, int nonzerorows);
Mat shift2center(const Mat& src);
Mat highpass_filter(int height, int width);
bool imrotate(const Mat& img, Mat &Res, float angle);

void getphaseCorrMaxval_loc(InputArray _src1, InputArray _src2, double& maxval, Point& maxloc);
void magSpectrums( InputArray _src, OutputArray _dst);
void divSpectrums( InputArray _srcA, InputArray _srcB, OutputArray _dst, int flags, bool conjB);
void fftShift(InputOutputArray _out);
// flags is remap border type
void LogPolarTrans(const Mat& src, Mat& dst, Point center, int flags);

//************************************
// Method:    Fourier-Mellin transform
// FullName:  FMTmatch
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Mat img1
// Parameter: Mat img2
// Parameter: Point2f * offset
// Parameter: double * theta
// Parameter: double * scale
//************************************
void FMTmatch(const Mat& img1, const Mat& img2, Point2f* offset, double* theta = 0, double* scale = 0);
void FMTmatchDemo();

/*快速去雾*/
Mat FastHazeRemoval(const Mat& src, float rho1, int windowssize = 101);
Mat SpitMinChn(const Mat& src);		// 图像预处理，完成单通道到三通道的转换
Mat CreatTable(float invA);		// Create Mat-Table for look-up
Mat LookUpTable(const Mat& src1, const Mat& src2, const Mat& Table); // Gray image LUT by Mat-Table
Mat LookUpTableC3(const Mat& src1, const Mat& src2, const Mat& Table);	// RGB images LUT by MT
void FastHazeRemovalDemo();

//************************************
// Method:    CylinderExpansion
// FullName:  CylinderExpansion
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Mat src
// Parameter: Mat& dst, 
// Parameter: int R, radius of cylinder
//************************************
void CylinderExpansion(InputArray _src, OutputArray _dst, int R);
void CylinderExpansionNremap(InputArray _src, OutputArray _dst, int R);
void CylinderExpansionTest();

//************************************
// Method:    利用Hu矩进行匹配，目前是失败的
// FullName:  matchHuMoments
// Access:    public 
// Returns:   Point
// Qualifier: 
// Parameter: Mat src
// Parameter: Mat tem
// Parameter: int thresh
//************************************
Point matchHuMoments(Mat src, Mat tem, int thresh);
Mat generateMask(int radius);

//************************************
// Method:    利用中值滤波去除背景
// FullName:  removeBackground
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Mat src
// Parameter: Mat & res
// Parameter: int ksize
// Parameter: bool IsAbs
//************************************
void removeBackground(Mat src, Mat& res, int ksize = 15, bool IsAbs = false);

//************************************
// Method:    通过形状角检测图像中的圆
// FullName:  ShapeAngleCircles
// Access:    public 
// Returns:   void
// Qualifier:
// Input: Mat src
// Output: vector<vector<Point>>& circles
// Input: double threshold, shape angle threshold in rad
// Input: int threLength, length of contours threshold
// Input: int thresCanny, up threshold of canny edge detection
//************************************
void ShapeAngleCircles(Mat src, vector<vector<Point>>& circles, double threshold = 0.2, int threLength = 500, int thresCanny = 200);
// 根据圆上点的位置计算圆心和半径，当前使用的是计算所有圆上点的平均值作为圆心，所有点到圆心的距离的平均值作为半径
void CalCirclePara(vector<vector<Point>> circles, vector<Point>& centers, vector<int>& radius);
// shape angle circles demo
void ShapeAngleCirclesDemo();
// DropFall
//************************************
// Method:    DropFallBegPt
// FullName:  DropFallBegPt
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const Mat & src, input source image
// Parameter: Point & beg, output begin point
//************************************
void DropFallBegPt(const Mat &src, vector<Point> &beg);

void FindDropFallPath(const Mat &src, vector<Point> &beg, vector<vector<Point>> &Path);
void FindDropFallPathDemo();
void FindDropFall1Path(const Mat &src, const Point &beg, vector<Point> &OnePath);
void FindDropFall1PathDemo();

//************************************
// Method:    DrawDropFallPath
// FullName:  DrawDropFallPath
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Mat & srcdst, input&output image
// Parameter: const vector<vector<Point>> & Path, input path
// Parameter: uchar linecolor, input linecolor within [0, 255]
//************************************
void DrawDropFallPath(Mat &srcdst, const vector<vector<Point>> &Path, uchar linecolor);
void DrawDropFallPathDemo();

// HUMoments test
void HuMomentsTest();
// opencv HoughCircles Test
void HoughCirclesTest();

// CFS color filling segment, connected-component labelling
enum {Label_TwoPass = 0, Label_SeedFill = 2, Label_SeedFill8C = 3};
void ConnComponetLabel(const Mat& binImage, Mat &LabelImage, int LabelType);
void CCLTwoPass4C(const cv::Mat& _binImg, cv::Mat& _lableImg);
void CCLSeedFill4C(const cv::Mat& _binImg, cv::Mat& _lableImg);
void DrawLabelImage(const Mat& _labelImg, Mat& _colorLabelImg);
void ConnComponetLabelDemo();
void CCLSeedFill8C(const cv::Mat& _binImg, cv::Mat& _lableImg);

//连通域标记算法
//操作对象：图像转换为一维数组，且只能是单字节黑白图像
//来自论文：牛连强, 彭敏, 孙忠礼,张刚. 利用游程集合的标号传播实现快速连通域标记 .
//计算机辅助设计与图形学学报,2015,vol.27,no.1
//算法&程序作者：牛连强(NIU Lianqiang)
//2013.4

/*-----------连通域标号程序未来改写方向--------------
-----------------2016/9/12 reprogram finished----------------
* 1、拆分CCLabeling函数，先提取S、E和Index，为第一个函数
* 2、根据三个结果进行标号和确定需要提取的特征，一般以图像矩表示
* 特征公式参见《快速连通域分析算法及其实现_孔斌》一文
* 3、将minThresh和maxThresh设置成scalar类型或数组型，保存更多参数
*-----------------------------------------------*/
//************************************
// Method:    ExtractRunlength
// FullName:  ExtractRunlength, extract run_length in image
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: uchar * imagedata, first pixel ptr of image 
// Parameter: const long & PixelCount, image's Height * image's Width
// Parameter: long * S, store start number of ith run_length
// Parameter: long * E, store end number of ith run_length
// Parameter: long * rIndex
//************************************
typedef struct
{
	long S;
	long E;
	long rIndex;
} Run_length;
long ExtractRunlength(uchar *imagedata, const long &PixelCount, Run_length *runlength);
void ExtractRunlength(InputArray _src, vector<Run_length> &runlength);
typedef struct
{
	long label;                    // label
	long nPixelCnt;                // area
	long xsum, ysum;               // 1nd image moments
	double x0, y0;                 // gravity point
	long xxsum, xysum, yysum;      // 2nd image moments
	double xx, xy, yy;             // fitting ellipse
	int left, top, right, bottom;  // External rectangle
} FEATURES;

void InitFeature(FEATURES &feature);
// update features by type
void Add2Features(FEATURES &feature1, const FEATURES &feature2, int type);
void Add2Features(FEATURES &feature1, const Run_length &runlength, int width, int type);
// statistical features of connected components
long StatFeatureInfo(uchar *image, int Height, int Width, int type, bool backfill = true);
long StatFeatureInfo(InputOutputArray _src, vector<FEATURES> &Features, int type, bool backfill = true);
void StatFeatureInfoDemo();

// 查找根标号的位置
// 更新路径上的元素标号索引
long findRootIndex(long* labels, long position);
long findRootIndex(vector<long> &labels, long position);
long findRootIndex(FEATURES* labels, long position);
long findRootIndex(vector<FEATURES> &labels, long position);
// 合并两个DCB所在的树
long unionDCBs(long* labels, long pos1, long pos2);
long unionDCBs(vector<long> &labels, long pos1, long pos2);
long unionDCBs(FEATURES *labels, long pos1, long pos2);
long unionDCBs(vector<FEATURES> &labels, long pos1, long pos2);

// 纯数组DCB并查集
// 背景色为0
// image:按行存储的一维图像，每行最后列加一字节存背景
long CCLabeling(unsigned char image[], long width, long height, bool backfill = true);

void CCLabeling(Mat &image, vector<long> &rStart, vector<long> &rEnd, vector<long> &label, vector<long> &index, long &cComponentCount, bool backfill = true);


void CCLabelingDemo();

// select regions whose area larger than threshold
enum 
{
	REGION_SELECT_AREA = 1, 
	REGION_SELECT_WIDTH = 2, 
	REGION_SELECT_HEIGHT = 4, 
	REGION_SELECT_WIDTH_DIV_HEIGHT = 8
};
// use vector edition of CCLabeling.
// In release mode, array&vector editions have the same performance, 
// but vector edition is more safer
void SelectRegion(const Mat& src, Mat &dst, vector<Mat> &Regions, int type, const Scalar& minThresh, const Scalar &maxThresh);
// set Feature.label=0 if out of [minThresh, maxThresh]
void RefineFeatureByArea(vector<FEATURES> &Feature, double minThresh, double maxThresh);
void RefineFeatureByWidth(vector<FEATURES> &Feature, double minThresh, double maxThresh);
void RefineFeatureByHeight(vector<FEATURES> &Feature, double minThresh, double maxThresh);
void RefineFeatureByW_DIV_H(vector<FEATURES> &Feature, double minThresh, double maxThresh);
// the same function with SelectRegion, use the SataFeatureInfo
void SelectShape(InputArray _src, OutputArray _dst, vector<Mat> &Regions, int type, const Scalar& minThresh, const Scalar &maxThresh);
// demo
void SelectRegionDemo();
void SelectShapeDemo();

// to test opencv in-built flood-fill method
// CClabeling is faster than flood-fill using test1.tif
void floodfilltest();