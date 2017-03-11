
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp" 
#include <iostream>  

#include <stdio.h>
#include <string.h>


using namespace std;
using namespace cv;

int main(int argc, const char* argv[])
{
	vector<Mat> process1_img[3];

	
	char _filepath[256]="/home/beason/prog_imageprocess_hw/prog_imageprocess_hw1/_MG_374";
	char _imgfileextension[16]=".JPG";
	char _input_filename[512];
	char _save_filename[256]="/home/beason/prog_imageprocess_hw1/result.jpg";
	
	Mat input_img[3];
	
	int num_charaters;

	
    /****read 3 image****/
    
    for(int i=0; i<3; i++)
    {
    	num_charaters = sprintf(_input_filename, "%s%d%s", _filepath, i+4, _imgfileextension);
		printf("number of charaters: %d, string: \"%s\"\n", num_charaters, _input_filename);
		
    	input_img[i]=imread(_input_filename, IMREAD_COLOR);
    	
    	if(input_img[i].empty())
    	{
    		printf("No input file\n");	                
        	return -1;
    	}
    	
    	split(input_img[i],process1_img[i]);
    	
    }

	/****average 3 image channel's' pixel intensity ****/
	
	Mat* output_image = new Mat(input_img[0].rows, input_img[0].cols, CV_8UC3);
	
	for(int k=0; k<3; k++)
	{
		uchar* ptr_channel_1 = process1_img[0][k].data;
		uchar* ptr_channel_2 = process1_img[1][k].data;
		uchar* ptr_channel_3 = process1_img[2][k].data;
		
		for(int i=0; i<input_img[0].rows; i++)
		{
			for(int j=0; j<input_img[0].cols; j++)
			{
			
				output_image->at<Vec3b>(i, j)[k] = (ptr_channel_1[i*input_img[0].cols+j] + ptr_channel_2[i*input_img[0].cols+j] + ptr_channel_3[i*input_img[0].cols+j])/3;
				
			}
		}
	
	}


	imshow("Image", *output_image);
	waitKey(0);
	imwrite(_save_filename, *output_image);

	/***free resource***/
	delete output_image;
	
	output_image = NULL;
	
	return 0;

}
