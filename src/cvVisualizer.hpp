//
//  cvVisualizer.hpp
//  1010featureStart
//
//  Created by A. K. Williams on 10/9/16.
//
// USAGE:
// ./visualise_models -model <model.xml> -image <ref.png> -data <output folder>
// based on the classifier visualization code by Steben Puttemans in OpenCv Blueprints https://github.com/OpenCVBlueprints/OpenCVBlueprints/blob/d4f20feb0bf39004b208eef80c3b66e0c04d2815/chapter_5/source_code/visualize_models/visualize_models.cpp
//

#ifndef cvVisualizer_hpp
#define cvVisualizer_hpp

#include "ofMain.h"
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "ofxCv.h"

#include <typeinfo>
#include <fstream>
#include <iostream>



class CvVisualizer : public ofBaseApp {
public:
    void setup(string modelName);
    void update(ofImage img);
    void draw();
    void drawStage(int stage_num);
    int numStages();
    
    cv::FileStorage fs;
    cv::FileNode cascade,stages,features, feature_trees;
    
    string output_folder;
    string image_ref;
    int resize_width;
    int resize_height;
    struct rect_data {
        int x;
        int y;
        int w;
        int h;
        int weight;
    };
    vector< vector< rect_data > > stage_feature_data;
    vector< vector<  vector< rect_data > > > all_stages;
    cv::Mat reference_image, visualization;
    
    const int x=0;
    const int y=1;
    const int w=2;
    const int h=3;
    const int wt=4;
    
};

#endif /* cvVisualizer_hpp */
