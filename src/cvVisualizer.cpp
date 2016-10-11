//
//  cvVisualizer.cpp
//  1010featureStart
//
//  Created by A. K. Williams on 10/9/16.
//
//

#include "cvVisualizer.hpp"

using namespace std;
using namespace cv;
//--------------------------------//
//--------------------------------//

void CvVisualizer::setup(string modelName, string outputFolder){
    
    
    model = modelName;
    output_folder = outputFolder;
    
    
    // Value for cols of storing elements
    int cols_prefered = 5;
    
    // Open the XML model
    
    fs.open(model, FileStorage::READ);
    
    // Get a the required information
    cascade = fs["cascade"];
    
    
    // We make a visualisation mask - which increases the window to make it at least a bit more visible
    resize_factor = 10;
    resize_storage_factor = 10;
    
    
    
    // First recover for each stage the number of weak features and their index
    // Important since it is NOT sequential when using LBP features
    // NOTE: do I need this for the
    
    vector< vector<int> > stage_features;
    FileNode stages = cascade["stages"];
    FileNodeIterator it_stages = stages.begin(), it_stages_end = stages.end();
    int idx = 0;
    for( ; it_stages != it_stages_end; it_stages++, idx++ ){
        vector<int> current_feature_indexes;
        FileNode weak_classifiers = (*it_stages)["weakClassifiers"];
        FileNodeIterator it_weak = weak_classifiers.begin(), it_weak_end = weak_classifiers.end();
        vector<int> values;
        for(int idy = 0; it_weak != it_weak_end; it_weak++, idy++ ){
            (*it_weak)["internalNodes"] >> values;
            current_feature_indexes.push_back( (int)values[2] );
        }
        stage_features.push_back(current_feature_indexes);
    }
    
    // If the output option has been chosen than we will store a combined image plane for
    // each stage, containing all weak classifiers for that stage.
    // bool draw_planes = false;
    // stringstream output_video;
    // output_video << output_folder << "model_visualization.avi";
    // VideoWriter result_video;
    // if( output_folder.compare("") != 0 ){
    // 	draw_planes = true;
    // 	result_video.open(output_video.str(), CV_FOURCC('X','V','I','D'), 15, Size(reference_image.cols * resize_factor, reference_image.rows * resize_factor), false);
    // }
    
    // Grab the corresponding features dimensions and weights
    FileNode features = cascade["features"];
    vector< vector< rect_data > > feature_data;
    FileNodeIterator it_features = features.begin(), it_features_end = features.end();
    for(int idf = 0; it_features != it_features_end; it_features++, idf++ ){
        vector< rect_data > current_feature_rectangles;
        FileNode rectangles = (*it_features)["rects"];
        int nrects = (int)rectangles.size();
        for(int k = 0; k < nrects; k++){
            rect_data current_data;
            FileNode single_rect = rectangles[k];
            current_data.x = (int)single_rect[0];
            current_data.y = (int)single_rect[1];
            current_data.w = (int)single_rect[2];
            current_data.h = (int)single_rect[3];
            current_data.weight = (float)single_rect[4];
            current_feature_rectangles.push_back(current_data);
        }
        feature_data.push_back(current_feature_rectangles);
    }
}
//--------------------------------//
//--------------------------------//
void CvVisualizer::update(ofImage img)
{
    // convert the input image to gray and convert gray image to
    ofPixels gray;
    ofxCv::convertColor(img, gray, CV_RGB2GRAY);
    reference_image = ofxCv::toCv(gray);
    // reference_image = imread(image_ref, CV_LOAD_IMAGE_GRAYSCALE);
    
    resize(reference_image, visualization, cv::Size(reference_image.cols * resize_factor, reference_image.rows * resize_factor), 0, 0, CV_INTER_CUBIC);
    vector< vector<int> > stage_features;
    
    Mat image_plane;
    Mat metadata = Mat::zeros(150, 1000, CV_8UC1);
    vector< rect_data > current_rects;
    for(int sid = 0; sid < (int)stage_features.size(); sid ++){
//        if(draw_planes){
//            int features = stage_features[sid].size();
//            int cols = cols_prefered;
//            int rows = features / cols;
//            if( (features % cols) > 0){
//                rows++;
//            }
//            image_plane = Mat::zeros(reference_image.rows * resize_storage_factor * rows, reference_image.cols * resize_storage_factor * cols, CV_8UC1);
//        }
        for(int fid = 0; fid < (int)stage_features[sid].size(); fid++){
            stringstream meta1, meta2;
            meta1 << "Stage " << sid << " / Feature " << fid;
            meta2 << "Rectangles: ";
            Mat temp_window = visualization.clone();
            Mat temp_metadata = metadata.clone();
            int current_feature_index = stage_features[sid][fid];
            current_rects = feature_data[current_feature_index];
            Mat single_feature = reference_image.clone();
            cv::resize(single_feature, single_feature, cv::Size(), resize_storage_factor, resize_storage_factor);
            for(int i = 0; i < (int)current_rects.size(); i++){
                rect_data local = current_rects[i];
                // NOTE: vvv This is the draw logic that they're using - adapt this to fit your needs
//                if(draw_planes){
//                    if(local.weight >= 0){
//                        rectangle(single_feature, Rect(local.x * resize_storage_factor, local.y * resize_storage_factor, local.w * resize_storage_factor, local.h * resize_storage_factor), Scalar(0), CV_FILLED);
//                    }else{
//                        rectangle(single_feature, Rect(local.x * resize_storage_factor, local.y * resize_storage_factor, local.w * resize_storage_factor, local.h * resize_storage_factor), Scalar(255), CV_FILLED);
//                    }
//                }
                
                cv::Rect part(local.x * resize_factor, local.y * resize_factor, local.w * resize_factor, local.h * resize_factor);
                meta2 << part << " (w " << local.weight << ") ";
                if(local.weight >= 0){
                    rectangle(temp_window, part, Scalar(0), CV_FILLED);
                }else{
                    rectangle(temp_window, part, Scalar(255), CV_FILLED);
                }
            }
            imshow("features", temp_window);

            
            // Copy the feature image if needed
//            if(draw_planes){
//                single_feature.copyTo(image_plane(Rect(0 + (fid%cols_prefered)*single_feature.cols, 0 + (fid/cols_prefered) * single_feature.rows, single_feature.cols, single_feature.rows)));
//            }

            imshow("metadata", temp_metadata);
        }
        //Store the stage image if needed
//        if(draw_planes){
//            stringstream save_location;
//            save_location << output_folder << "stage_" << sid << ".png";
//            imwrite(save_location.str(), image_plane);
//        }
    }
}
//--------------------------------//
//--------------------------------//
void CvVisualizer::draw(){
    // Read in the input arguments
}

//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//


