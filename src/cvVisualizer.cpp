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
// NOTE: for now you need to give the absolute path
void CvVisualizer::setup(string modelName){
    //     Open the XML model
    fs.open(ofToDataPath(modelName), FileStorage::READ);
    string testStr ;
    if(fs.isOpened()){
        testStr = "fs is open";
    }else {
        testStr = "fs is not open";
    }
//    cout << testStr << endl;
    
    //     open the cascade xml - this logic is specially required for opencv cascades
    string tmpName = modelName.substr(0, modelName.length()-4);
    cascade = fs[tmpName];
    int tmp = cascade["size"][0];
//    cout << "tmp is equal to : " << tmp << endl;
    resize_width = tmp;
    resize_height = tmp;
    
    stages = cascade["stages"];
    FileNodeIterator it_stages = stages.begin(), it_stages_end = stages.end();
    
    //     here declare a vector of vv stage feature data rects  that will hopld the data by stage.
    for( int idx = 0; it_stages != it_stages_end; it_stages++, idx++ ){
        vector< vector< rect_data > > stage_feature_data;
        FileNode feature_trees = (*it_stages)["trees"];
        int num_trees = feature_trees.size();
        
        for(int idy = 0; idy < num_trees; idy++ ){
            vector< rect_data > current_feature_rectangles; // create a vector of rect data
            for(int idz = 0; idz < 2; idz++){
                // grab the data for each rect
                FileNode single_rect = feature_trees[idy][0]["feature"]["rects"][idz];
                rect_data current_data;
                current_data.x = (int)single_rect[x] * resize_width;
                current_data.y = (int)single_rect[y] * resize_height;
                current_data.w = (int)single_rect[w] * resize_width;
                current_data.h = (int)single_rect[h] * resize_height;
                current_data.weight = (float)single_rect[wt];
                current_feature_rectangles.push_back(current_data);
            }
            
            stage_feature_data.push_back(current_feature_rectangles);
        }
        all_stages.push_back(stage_feature_data);
    }
//    cout << typeid(stage_feature_data[0][0]).name() << endl;
}
//--------------------------------//
//--------------------------------//
void CvVisualizer::update(ofImage img)
{
    //     convert the input image to gray and convert gray image to
    ofPixels gray;
    ofxCv::convertColor(img, gray, CV_RGB2GRAY);
    reference_image = ofxCv::toCv(gray);
    
}
//--------------------------------//
//--------------------------------//
void CvVisualizer::draw(){
    ofBackground(0);
    
    // Read in the input arguments
    for(int idx = 0; idx < stages.size(); idx++){
        for(int idy = 0; idy < all_stages[idx].size() ; idy++){
            for(int idz = 0; idz < all_stages[idx][idy].size(); idz++){
                ofSetColor(255, 255, 255);
                
                if(all_stages[idx][idy][idz].weight > 0.0){
                    
                    ofFill();
                } else {
                    ofNoFill();
                }
                ofDrawRectangle((float)all_stages[idx][idy][idz].x,(float)all_stages[idx][idy][idz].y,(float)all_stages[idx][idy][idz].w,(float)all_stages[idx][idy][idz].h);
            }
            
        }
        
    }
}

//------------------------------------------------------------------------------------------------//
//--------------------------------//
void CvVisualizer::drawStage(int stage_num){
    ofBackground(0);

        for(int idy = 0; idy < all_stages[stage_num].size() ; idy++){
            for(int idz = 0; idz < all_stages[stage_num][idy].size(); idz++){
                ofSetColor(255, 255, 255);
                if(all_stages[stage_num][idy][idz].weight > 0.0){
                    
                    ofFill();
                } else {
                    ofNoFill();
                }
                ofDrawRectangle((float)all_stages[stage_num][idy][idz].x,(float)all_stages[stage_num][idy][idz].y,(float)all_stages[stage_num][idy][idz].w,(float)all_stages[stage_num][idy][idz].h);
            }
            
        }
        
    }
}
//------------------------------------------------------------------------------------------------//
int CvVisualizer::numStages(){
    return all_stages.size();
}
//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//


