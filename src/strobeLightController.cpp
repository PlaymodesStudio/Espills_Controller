//
//  strobeLightController.cpp
//  Espills_controller
//
//  Created by Eduard Frigola on 14/08/2018.
//

#include "strobeLightController.h"

void strobeLightController::setup(){
    parameters->add(numElements.set("Num Elements", 4, 0, 1000));
    parameters->add(red.set("Red", {1}, {0}, {1}));
    parameters->add(green.set("Green", {1}, {0}, {1}));
    parameters->add(blue.set("Blue", {1}, {0}, {1}));
    parameters->add(amber.set("Amber", {0}, {0}, {1}));
    parameters->add(saturate.set("Saturate", {0}, {0}, {1}));
    parameters->add(fader.set("Fader", {1}, {0}, {1}));
    parameters->add(strobeRate.set("Zoom", {0}, {0}, {1}));
    parameters->add(strobeWidth.set("Tilt", {1}, {0}, {1}));
    parameters->add(masterFader.set("Master Fader", 1, 0, 1));
    parameters->add(output.set("Output", {0}, {0}, {1}));
}

void strobeLightController::update(ofEventArgs &e){
    auto getValueForPosition([&](ofParameter<vector<float>> &p, int pos) -> float{
        if(pos < p->size()){
            return p->at(pos);
        }
        return p->at(0);
    });
    
    int elementSize = 5;
    vector<float> tempOutput;
    tempOutput.resize(numElements*elementSize, 0);
    for(int i = 0; i < numElements; i++){
        float posSaturate = getValueForPosition(saturate, i);
        float posFader = getValueForPosition(fader, i);
        
        float red_ = ((getValueForPosition(red, i) * (1-posSaturate)) + (1 * posSaturate)) * posFader * masterFader;
        float green_ = ((getValueForPosition(green, i) * (1-posSaturate)) + (1 * posSaturate)) * posFader * masterFader;
        float blue_ = ((getValueForPosition(blue, i) * (1-posSaturate)) + (1 * posSaturate)) * posFader * masterFader;
        float white_ = 0;
        
        rgbToRgbw(red_, green_, blue_, white_, false);
        
        tempOutput[(i*elementSize)+0] = red_;
        tempOutput[(i*elementSize)+1] = green_;
        tempOutput[(i*elementSize)+2] = blue_;
        tempOutput[(i*elementSize)+3] = white_;
        tempOutput[(i*elementSize)+4] = getValueForPosition(amber, i) * posFader * masterFader;
    }
    output = tempOutput;
}

void strobeLightController::rgbToRgbw(float &r, float &g, float &b, float &w, bool clamp){
    float tM = max(r, max(g, b));
    if(tM == 0){
        return;
    }
    
    //This section serves to figure out what the color with 100% hue is
    float multiplier = 1.0f/tM;
    float hR = r * multiplier;
    float hG = g * multiplier;
    float hB = b * multiplier;
    
    //This calculates the Whiteness (not strictly speaking Luminance) of the color
    float M = max(hR, max(hG, hB));
    float m = min(hR, min(hG, hB));
    float Luminance = ((M + m) / 2.0f - 0.5f) * (2.0f) / multiplier;
    
    if(clamp){
        if(r == g && r == b && g == b){
            Luminance = r;
        }else{
            Luminance = 0;
        }
    }
    
    //Calculate the output values
    w = Luminance;
    r -= Luminance;
    g -= Luminance;
    b -= Luminance;
    return;
}
