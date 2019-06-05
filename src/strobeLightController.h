//
//  strobeLightController.h
//  Espills_controller
//
//  Created by Eduard Frigola on 14/08/2018.
//

#ifndef strobeLightController_h
#define strobeLightController_h

#include "ofxOceanodeNodeModel.h"

class strobeLightController : public ofxOceanodeNodeModel{
public:
    strobeLightController() : ofxOceanodeNodeModel("StrobeLight Controller"){};
    ~strobeLightController(){};
    
    void setup() override;
    void update(ofEventArgs &e) override;
    
    void presetRecallBeforeSettingParameters(ofJson &json) override{
        amber = vector<float>(1, 0);
    }
    
private:
    
    void rgbToRgbw(float &r, float &g, float &b, float &w, bool clamp = false);
    
    ofParameter<int> numElements;
    ofParameter<vector<float>> red;
    ofParameter<vector<float>> green;
    ofParameter<vector<float>> blue;
    ofParameter<vector<float>> amber;
    ofParameter<vector<float>> saturate;
    ofParameter<vector<float>> fader;
    ofParameter<float> masterFader;
    ofParameter<vector<float>> strobeRate;
    ofParameter<vector<float>> strobeWidth;
    ofParameter<vector<float>> output;
    
};

#endif /* strobeLightController_h */
