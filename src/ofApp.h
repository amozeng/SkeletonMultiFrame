#pragma once

#include "ofMain.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();
    void keyPressed(int key);
    void onTextChange(std::string & text);

    void drawSkeleton(std::vector<ofSpherePrimitive>& joints);
    void draw20JointSkeleton(std::vector<ofSpherePrimitive>& joints);

    
    bool showSelectedSkeletonONLY = false;
    int export_frame_index = 0;
    
    int lineCount = -1;
    
    string file_name_after;
    string input_text;
    string export_notice;
    
    std::vector<std::vector<ofSpherePrimitive>> frames;
    
    ofxPanel gui;
    ofxFloatSlider radius, scale, label_offset, opacity;
    ofxIntSlider resolution;
    ofxVec3Slider eachSkeleton, allSkeleton, framePos;
    ofParameter<bool> showJointName, showFrameIndex;
    ofxIntSlider axisSize, indexInterval, frameMax, frameMin;
    ofParameter<bool> narrowDown;
    ofParameter<std::string> textParameter;
    ofParameter<std::string> highlightJoint;


    
    ofEasyCam camera;
    
    string export_file_name;
    
    string joint_name[24] = {"0 Waist",
                             "1 Spine",
                             "2 Chest",
                             "3 Neck",
                             "4 Head",
                             "5 Head Tip",
                             "6 UpperLeg L",
                             "7 LowerLeg L",
                             "8 Foot L",
                             "9 Toes L",
                             "10 UpperLeg R",
                             "11 LowerLeg R",
                             "12 Foot R",
                             "13 Toes R",
                             "14 Collar L",
                             "15 UpperArm L",
                             "16 ForeArm L",
                             "17 Hand L",
                             "18 FingerTip L",
                             "19 Collar R",
                             "20 UpperArm R",
                             "21 ForeArm R",
                             "22 Hand R",
                             "23 FingerTip R"
    };
    
};
