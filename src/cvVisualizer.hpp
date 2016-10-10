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

#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "ofxCv.h"

#include <fstream>
#include <iostream>



class CvVisualizer : public ofBaseApp {
public:
    struct rect_data{
        int x;
        int y;
        int w;
        int h;
        float weight;
    };
    void setup(string modelName, string outputFolder);
    void update(ofImage img);
    void draw();
    //    vector<Rect> current_rect;
    
    cv::FileStorage fs;
    cv::FileNode cascade,stages,features;
    
    string model;
    string output_folder;
    string image_ref;
    int resize_factor;
    int resize_storage_factor;
    
    vector< vector< rect_data > > feature_data;
    cv::Mat reference_image, visualization;
    
    
};

#endif /* cvVisualizer_hpp */
