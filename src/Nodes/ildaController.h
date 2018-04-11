//
//  ildaController.hpp
//  Espill-ilda
//
//  Created by Eduard Frigola on 26/06/2017.
//
//

#ifndef ildaController_h
#define ildaController_h

#include "ofMain.h"
#include "ofxEtherdream.h"
#include "ofxOceanodeNodeModelExternalWindow.h"

class ildaController : public ofxOceanodeNodeModelExternalWindow{
public:
    ildaController();
    ~ildaController(){};
    
    void setup();
    
    void draw(){
        ildaFrame.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    void update(ofEventArgs &a) override{
        setPolylines();
        ildaFrame.update();
        etherdream->setPoints(ildaFrame);
    }
    
    void drawInExternalWindow(ofEventArgs &e) override {draw();};
    
    
    void setPolylines(vector<pair<ofPolyline, ofColor>> polys);
    void setPolylines();
    
    ofxOceanodeAbstractConnection* createConnectionFromCustomType(ofxOceanodeContainer& c, ofAbstractParameter& source, ofAbstractParameter& sink) override;

    
private:
    void parameterChangedListener(ofAbstractParameter &param);
    
    ofxIlda::Frame ildaFrame;
    
    ofxEtherdream* etherdream;
    
    ofParameter<bool>   clear;
    ofParameter<bool>   resetConnection;
    ofParameter<vector<pair<ofPolyline, ofColor>>> in1;
    ofParameter<vector<pair<ofPolyline, ofColor>>> in2;
    ofParameter<vector<pair<ofPolyline, ofColor>>> in3;
    ofParameter<vector<pair<ofPolyline, ofColor>>> in4;
    ofParameter<float>  maxOpacity;
    ofParameter<int> pps;
    ofParameter<bool> capX;
    ofParameter<bool> capY;
    ofParameter<int> blankCount;
    ofParameter<int> endCount;
    ofParameter<bool> flipX;
    ofParameter<bool> flipY;
    ofParameter<int> pointCount;
    ofParameter<int> minimumPointCount;
    //    ofParameter<bool> doSmooth;
    ofParameter<bool> doSpacing;
    ofParameter<int> smoothing;
    ofParameter<float> tolerance;
    ofParameter<ofFloatColor> laserColor;
    ofParameter<glm::vec2> offset;
    ofParameter<glm::vec2> scale;
    
};

#endif /* ildaController_h */
