//
//  graphicPatternGenerator.h
//  Espill-ilda
//
//  Created by Eduard Frigola on 21/06/2017.
//
//

#ifndef graphicPatternGenerator_h
#define graphicPatternGenerator_h

#include "ofMain.h"
#include "ofxOceanodeNodeModelExternalWindow.h"

enum modeSelectTypes{
    MODE_POINTS,
    MODE_CIRCLES,
    MODE_SQUARES,
    MODE_LINES
};

class graphicPatternGenerator : public ofxOceanodeNodeModelExternalWindow{
public:
    graphicPatternGenerator();
    ~graphicPatternGenerator(){};
    
    void setup();
    
    void update(ofEventArgs &a) override {computePolylines();};
    
    void draw();
    void drawInExternalWindow(ofEventArgs &e) override {draw();};
    
    void mousePressed(ofMouseEventArgs &a) override;
    void mouseReleased(ofMouseEventArgs &a) override;
    void mouseDragged(ofMouseEventArgs &a) override;
    
    vector<pair<ofPolyline, ofColor>> computePolylines();
    
    ofParameterGroup* getGroup(){return parameters;};
    
private:
    void parameterChangedListener(ofAbstractParameter &parameter);
    int pointDraggingIndex;
    ofTrueTypeFont font;
    
    bool someParameterChanged;
    
    template <typename T>
    T getParameterValueForPosition(ofParameter<vector<T>> &param, int index){
        if(param.get().size() == 1 || param.get().size() <= index){
            return param.get()[0];
        }
        else{
            return param.get()[index];
        }
    }
    
    
    ofParameter<vector<ofPoint>> positions;
    ofParameter<int>    positionReplicator;
    ofParameter<float>  scalePositions;
    ofParameter<ofColor> color;
    ofParameter<int> modeSelector;
    ofParameter<int> numVertex;
    ofParameter<bool> toCenterFigure;
    ofParameter<float>  opacity;
    ofParameter<float> size;
    ofParameter<float> rotation;
    ofParameter<float> jitter;
    ofParameter<bool>   refollow;
    ofParameter<float>  refollowIn;
    ofParameter<float>  endFollow;
    ofParameter<float>  offsetFollow;
    ofParameter<int>    divisions;
    ofParameter<float>  divisionSpacing;
    
    ofParameter<vector<float>> scalePositions_vec;
    ofParameter<vector<float>> opacity_vec;
    ofParameter<vector<float>> size_vec;
    ofParameter<vector<float>> rotation_vec;
    ofParameter<vector<float>> jitter_vec;
    ofParameter<vector<bool>>   refollow_vec;
    ofParameter<vector<float>>  refollowIn_vec;
    ofParameter<vector<float>>  endFollow_vec;
    ofParameter<vector<float>>  offsetFollow_vec;
    ofParameter<vector<int>>  divisions_vec;
    ofParameter<vector<float>>  divisionSpacing_vec;
    
    int lastPositionReplicator;
    ofParameter<vector<pair<ofPolyline, ofColor>>> polyLinesOut;
};

#endif /* graphicPatternGenerator_h */
