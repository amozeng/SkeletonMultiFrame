#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // 2 kinects ver.
//    string filePath = "1-062.csv"; // missing Toe R
//    string filePath = "1-065.csv";
//    string filePath = "1-083.csv";
//    string filePath = "5-079.csv";
//    string filePath = "5-168-1.csv";
//    string filePath = "5-173.csv";
//    string filePath = "5-178-2.csv";

    // 1 kinect ver.
//    string filePath = "1-062-1kinect.csv";
//    string filePath = "1-065-1kinect.csv";
//    string filePath = "5-079-1kinect.csv";
//    string filePath = "5-168-1-1kinect.csv";
//    string filePath = "5-173-1kinect.csv";
//    string filePath = "5-178-1-1kinect.csv";
//    string filePath = "5-178-2-1kinect.csv";

    
    // 1 kinect sequence 0-390-1-1.csv:  1~17
    string filePath = "0-390-1-1-17.csv";


    
    export_file_name = filePath.substr(0, filePath.find("."));
    
    //Load file placed in bin/data
    ofFile file(filePath);
    
    if(!file.exists()){
        ofLogError("The file " + filePath + " is missing");
    }
    ofBuffer buffer(file);
    
    //Read file line by line
    int counter = 0;
    

    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        lineCount++;
    }
    
    for (int i = 0; i < lineCount; i++) {
        std::vector<ofSpherePrimitive> joints;
        frames.push_back(joints);
    }
    
    
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        
        //std::vector<ofSpherePrimitive> joints;

        if(counter > 0) {
            
            int index = counter - 1;
            std::vector<ofSpherePrimitive>& joints = frames[index];
            
            string line = *it;
            //Split line into strings
            vector<string> words = ofSplitString(line, ",");
            
            
            // set position & rotation
            for (int i = 0; i < words.size(); i++){
                int q = i / 7;
                int r = i % 7;
                
                if(r == 2) {
//                    if (q == 9) { // TOE LEFT
//
////                    if (q == 9 || q == 13) {  // BOTH TOES
//                        ofSpherePrimitive sphere;
//                        sphere.setPosition(0, 0, 0);
//
//                        joints.push_back(sphere);
//                    }
                    
                    
                    float x = ofToFloat(words[i]);
                    float y = ofToFloat(words[i+1]);
                    float z = ofToFloat(words[i+2]);
                    
                    float rx = ofToFloat(words[i+3]);
                    float ry = ofToFloat(words[i+4]);
                    float rz = ofToFloat(words[i+5]);
                    
                    glm::vec3 rot = glm::vec3(rx, ry, rz);
                    
                    ofSpherePrimitive sphere;
                    sphere.setPosition(x, y, z);
                    sphere.setOrientation(rot);
                    
                    joints.push_back(sphere);
                    
                    
                    
                }
            }
            
            // set parent
            {
                //            1    Spine    Waist    0
                joints[1].setParent(joints[0]);
                //            2    Chest    Spine    1
                joints[2].setParent(joints[1]);
                //            3    Neck    Chest    2
                joints[3].setParent(joints[2]);
                //            4    Head    Neck    3
                joints[4].setParent(joints[3]);
                //            5    Head Tip    Head    4
                joints[5].setParent(joints[4]);
                //            6    UpperLeg L    Waist    0
                joints[6].setParent(joints[0]);
                //            7    LowerLeg L    UpperLeg L    6
                joints[7].setParent(joints[6]);
                //            8    Foot L    LowerLeg L    7
                joints[8].setParent(joints[7]);
                //            9    Toes L    Foot L    8
                joints[9].setParent(joints[8]);
                //            10    UpperLeg R    Waist    0
                joints[10].setParent(joints[0]);
                //            11    LowerLeg R    UpperLeg R    10
                joints[11].setParent(joints[10]);
                //            12    Foot R    LowerLeg R    11
                joints[12].setParent(joints[11]);
                //            13    Toes R    Foot R    12
                joints[13].setParent(joints[12]);
                //            14    Collar L    Chest    2
                joints[14].setParent(joints[2]);
                //            15    UpperArm L    Collar L    14
                joints[15].setParent(joints[14]);
                //            16    ForeArm L    UpperArm L    15
                joints[16].setParent(joints[15]);
                //            17    Hand L    ForeArm L    16
                joints[17].setParent(joints[16]);
                //            18    FingerTip L    Hand L    17
                joints[18].setParent(joints[17]);
                //            19    Collar R    Chest    2
                joints[19].setParent(joints[2]);
                //            20    UpperArm R    Collar R    19
                joints[20].setParent(joints[19]);
                //            21    ForeArm R    UpperArm R    20
                joints[21].setParent(joints[20]);
                //            22    Hand R    ForeArm R    21
                joints[22].setParent(joints[21]);
                //            23    FingerTip R    Hand R    22
                joints[23].setParent(joints[22]);
            }
            
            //break;
            frames.push_back(joints);
        }
        counter++;
    }
    
    gui.setup();
    gui.add(radius.setup("radius", 5.0, 0.01, 10.0));
    gui.add(scale.setup("scale", 250.0, 1.0, 1000.0));
    gui.add(label_offset.setup("label_offset", 0.05, 0.00, 0.2));
    gui.add(opacity.setup("opacity", 50, 1, 255));
    gui.add(resolution.setup("resolution", 2, 1, 10));
    gui.add(eachSkeleton.setup("eachSkeleton",
                           {0, 0, 0},
                           {0, 0, 0},
                           {200, 10, 500}));
    gui.add(allSkeleton.setup("allSkeleton",
                           {0, 0, 0},
                           {-3000, -300, -5000},
                           {3000, 300, 1000}));
    gui.add(framePos.setup("framePos",
                           {0, -50, 0},
                           {-500, -1000, -500},
                           {500, 1000, 500}));
    gui.add(showJointName.set("showJointName", false));
    gui.add(showFrameIndex.set("showFrameIndex", true));
    
    gui.add(axisSize.setup("axisSize", 1, 1, 100));

    gui.add(indexInterval.setup("indexInterval", 30, 1, 30));
    gui.add(frameMin.setup("frameMin", 1, 1, 600));
    gui.add(frameMax.setup("frameMax", 600, 1, 600));
    gui.add(narrowDown.set("narrowDown", false));
    textParameter.addListener(this, &ofApp::onTextChange);
    gui.add(textParameter.set("text", "default"));


}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    camera.begin();
    ofDrawAxis(axisSize);
    
    ofPushMatrix();   // scale
    ofScale(scale);
    
    
    if(showSelectedSkeletonONLY) {
        
        // draw 1 frame
        ofSetColor(0);
        std::vector<ofSpherePrimitive>& joints = frames[export_frame_index];
        drawSkeleton(joints);
   
    }else{
        
        //draw all frames
        ofPushMatrix();  // each frame
        ofTranslate(allSkeleton->x/scale, allSkeleton->y/scale, allSkeleton->z/scale);
        
        // PICK FRAME
        int beginFrame;
        int endFrame;
        if(narrowDown) {
            beginFrame = frameMin;
            endFrame = frameMax;
        }else{
            beginFrame = 0;
            endFrame = frames.size();
        }
        for(int j = beginFrame; j < endFrame; j = j + indexInterval)
        {
        

            std::vector<ofSpherePrimitive>& joints = frames[j];
            
            ofTranslate(eachSkeleton->x/scale, eachSkeleton->y/scale, eachSkeleton->z/scale);
            if(showFrameIndex) {
                ofDrawBitmapString(j, framePos->x/scale, framePos->y/scale, framePos->z/scale);
            }
            ofSetColor(0, opacity);
            drawSkeleton(joints);
        }
        ofPopMatrix(); // each frame
    }
    
    
    ofPopMatrix();  // scale
    
    camera.end();
    
    gui.draw();
    ofDrawBitmapString(input_text, 10, ofGetHeight()-40, 0);
    ofDrawBitmapString(export_notice, 10, ofGetHeight()-20, 0);

}


void ofApp::keyPressed(int key){
    
    if (key == 's') {
        showSelectedSkeletonONLY = !showSelectedSkeletonONLY;
    }
    
    
    if (key == 'e') {
        // export global position
        // export 1 frame
//        string file_name = "export/" + export_file_name + "/" + export_file_name + "_frame_" + ofToString(export_frame_index) + ".txt";
        string file_name = "export/seq_1/" + export_file_name + "_frame_" + ofToString(export_frame_index) + ".txt";
        ofFile frame(file_name, ofFile::WriteOnly);

        std::vector<ofSpherePrimitive>& joints = frames[export_frame_index];
        for(int i = 0; i < joints.size(); i++)
        {
            ofSpherePrimitive & joint = joints[i];
            glm::vec3 pos = joint.getGlobalPosition();
//            ofTranslate(allSkeleton->x/scale, allSkeleton->y/scale, allSkeleton->z/scale);

            string posX = ofToString(pos.x + allSkeleton->x/scale);
            string posY = ofToString(pos.y + allSkeleton->y/scale);
            string posZ = ofToString(pos.z + allSkeleton->z/scale);
            frame << posX << "," <<
                     posY << "," <<
                     posZ << "," <<
            endl;
        }
        std::cout << file_name << " exported!" <<std::endl;
        ofDrawBitmapString( file_name + " exported!", 10, ofGetHeight()- 10, 0);
        export_notice = file_name + " exported!";
    }
}


void ofApp::drawSkeleton(std::vector<ofSpherePrimitive>& joints){
    
    for(int i = 0; i < joints.size(); i++)
    {
        ofSpherePrimitive & joint = joints[i];
        glm::vec3 pos = joint.getPosition();
        joint.set(radius/scale, resolution);
        
        // HIGHLIGHT CERTAIN JOINTS
//        if(i == 3) {
//            ofSetColor(255, 0, 0);
//        }else{
//            ofSetColor(0);
//        }
        
        
        joint.draw();
        if(showJointName){
             ofVec3f labelOffset(0, 0, label_offset);
            ofSetColor(0);
            ofDrawBitmapString(joint_name[i], joint.getGlobalPosition() + labelOffset);
        }
        
    }
    if(joints.size()> 0) {
        //    0    Waist
        //    1    Spine    Waist    0
        ofDrawLine(joints[1].getGlobalPosition(), joints[0].getGlobalPosition());
        //    2    Chest    Spine    1
        ofDrawLine(joints[2].getGlobalPosition(), joints[1].getGlobalPosition());
        //    3    Neck    Chest    2
        ofDrawLine(joints[3].getGlobalPosition(), joints[2].getGlobalPosition());
        //    4    Head    Neck    3
        ofDrawLine(joints[4].getGlobalPosition(), joints[3].getGlobalPosition());
        //    5    Head Tip    Head    4
        ofDrawLine(joints[5].getGlobalPosition(), joints[4].getGlobalPosition());
        //    6    UpperLeg L    Waist    0
        ofDrawLine(joints[6].getGlobalPosition(), joints[0].getGlobalPosition());
        //    7    LowerLeg L    UpperLeg L    6
        ofDrawLine(joints[7].getGlobalPosition(), joints[6].getGlobalPosition());
        //    8    Foot L    LowerLeg L    7
        ofDrawLine(joints[8].getGlobalPosition(), joints[7].getGlobalPosition());
        //    9    Toes L    Foot L    8
        ofDrawLine(joints[9].getGlobalPosition(), joints[8].getGlobalPosition());
        //    10    UpperLeg R    Waist    0
        ofDrawLine(joints[10].getGlobalPosition(), joints[0].getGlobalPosition());
        //    11    LowerLeg R    UpperLeg R    10
        ofDrawLine(joints[11].getGlobalPosition(), joints[10].getGlobalPosition());
        //    12    Foot R    LowerLeg R    11
        ofDrawLine(joints[12].getGlobalPosition(), joints[11].getGlobalPosition());
        //    13    Toes R    Foot R    12
        ofDrawLine(joints[13].getGlobalPosition(), joints[12].getGlobalPosition());
        //    14    Collar L    Chest    2
        ofDrawLine(joints[14].getGlobalPosition(), joints[2].getGlobalPosition());
        //    15    UpperArm L    Collar L    14
        ofDrawLine(joints[15].getGlobalPosition(), joints[14].getGlobalPosition());
        //    16    ForeArm L    UpperArm L    15
        ofDrawLine(joints[16].getGlobalPosition(), joints[15].getGlobalPosition());
        //    17    Hand L    ForeArm L    16
        ofDrawLine(joints[17].getGlobalPosition(), joints[16].getGlobalPosition());
        //    18    FingerTip L    Hand L    17
        ofDrawLine(joints[18].getGlobalPosition(), joints[17].getGlobalPosition());
        //    19    Collar R    Chest    2
        ofDrawLine(joints[19].getGlobalPosition(), joints[2].getGlobalPosition());
        //    20    UpperArm R    Collar R    19
        ofDrawLine(joints[20].getGlobalPosition(), joints[19].getGlobalPosition());
        //    21    ForeArm R    UpperArm R    20
        ofDrawLine(joints[21].getGlobalPosition(), joints[20].getGlobalPosition());
        //    22    Hand R    ForeArm R    21
        ofDrawLine(joints[22].getGlobalPosition(), joints[21].getGlobalPosition());
        //    23    FingerTip R    Hand R    22
        ofDrawLine(joints[23].getGlobalPosition(), joints[22].getGlobalPosition());
    }
    
}

void ofApp::draw20JointSkeleton(std::vector<ofSpherePrimitive>& joints){
    ofSetColor(0, 0, 255);
    
    for(int i = 0; i < joints.size(); i++)
    {
        if( i == 4 || i == 5 || i == 14 || i == 19) {
            ofSetColor(0, opacity);
        }else{
            ofSetColor(0, 200);
        }
        ofSpherePrimitive & joint = joints[i];
        glm::vec3 pos = joint.getPosition();
        joint.set(radius/scale, resolution);
        joint.draw();
        if(showJointName){
            ofDrawBitmapString(joint_name[i], joint.getPosition() + glm::vec3(0, 0, -0.02));
        }
    }
    if(joints.size()> 0) {
        //    1    Spine    Waist    0
            ofDrawLine(joints[1].getPosition(), joints[0].getPosition());
        //    2    Chest    Spine    1
            ofDrawLine(joints[2].getPosition(), joints[1].getPosition());
        //    6    UpperLeg L    Waist    0
            ofDrawLine(joints[6].getPosition(), joints[0].getPosition());
        //    7    LowerLeg L    UpperLeg L    6
            ofDrawLine(joints[7].getPosition(), joints[6].getPosition());
        //    8    Foot L    LowerLeg L    7
            ofDrawLine(joints[8].getPosition(), joints[7].getPosition());
        //    9    Toes L    Foot L    8
            ofDrawLine(joints[9].getPosition(), joints[8].getPosition());
        //    10    UpperLeg R    Waist    0
            ofDrawLine(joints[10].getPosition(), joints[0].getPosition());
        //    11    LowerLeg R    UpperLeg R    10
            ofDrawLine(joints[11].getPosition(), joints[10].getPosition());
        //    12    Foot R    LowerLeg R    11
            ofDrawLine(joints[12].getPosition(), joints[11].getPosition());
        //    13    Toes R    Foot R    12
            ofDrawLine(joints[13].getPosition(), joints[12].getPosition());
        //    15    UpperArm L    Collar L    14
            ofDrawLine(joints[15].getPosition(), joints[2].getPosition());
        //    16    ForeArm L    UpperArm L    15
            ofDrawLine(joints[16].getPosition(), joints[15].getPosition());
        //    17    Hand L    ForeArm L    16
            ofDrawLine(joints[17].getPosition(), joints[16].getPosition());
        //    18    FingerTip L    Hand L    17
            ofDrawLine(joints[18].getPosition(), joints[17].getPosition());
        //    20    UpperArm R    Collar R    19
            ofDrawLine(joints[20].getPosition(), joints[19].getPosition());
        //    21    ForeArm R    UpperArm R    20
            ofDrawLine(joints[21].getPosition(), joints[20].getPosition());
        //    22    Hand R    ForeArm R    21
            ofDrawLine(joints[22].getPosition(), joints[21].getPosition());
        //    23    FingerTip R    Hand R    22
            ofDrawLine(joints[23].getPosition(), joints[22].getPosition());
    }
    
}

void ofApp::onTextChange(std::string &text){
    ofLogNotice() << "text changed " << text;
    int input_index = ofToInt(text);
    if(input_index < 300 && input_index)
    {
        export_frame_index = ofToInt(text);
        input_text = text;
    }
    ofLogNotice() << "export_frame_index: " << export_frame_index;
}
