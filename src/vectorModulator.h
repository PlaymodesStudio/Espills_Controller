//
//  vectorModulator.h
//  Espills_controller
//
//  Created by Eduard Frigola Bagué on 30/08/2018.
//

#ifndef vectorModulator_h
#define vectorModulator_h

#include "ofxOceanodeNodeModel.h"

class vectorModulator : public ofxOceanodeNodeModel{
public:
    vectorModulator() : ofxOceanodeNodeModel("Vector Modulator"){};
    ~vectorModulator(){};
    
    void setup() override{
        parameters->add(source.set("Source", {0}, {0}, {1}));
        parameters->add(modulator.set("Modulator", {0.5}, {0}, {1}));
        parameters->add(amount.set("Amount", {0}, {0}, {1}));
        parameters->add(output.set("Output", {0}, {0}, {1}));
        
        listeners.push(source.newListener(this, &vectorModulator::computeOutput));
        listeners.push(modulator.newListener(this, &vectorModulator::computeOutput));
    }
    
private:
    void computeOutput(vector<float> &vf){
        vector<float> tempOut(source->size());
        for (int i = 0; i < source->size(); ++i) {
            float amountForItem = 1.0;
            if(amount->size() == 1){
                amountForItem = amount->at(0);
            }else if(amount->size() == source->size()){
                amountForItem = amount->at(i);
            }
            
            float modulatorForItem = 0.5;
            if(modulator->size() == 1){
                modulatorForItem = modulator->at(0);
            }else if(modulator->size() == source->size()){
                modulatorForItem = modulator->at(i);
            }
            
            
            tempOut[i] = ofClamp(source->at(i) + (modulatorForItem-0.5) * amountForItem, 0, 1);
        }
        output = tempOut;
    }
    
    ofEventListeners listeners;
    
    ofParameter<vector<float>> source;
    ofParameter<vector<float>> modulator;
    ofParameter<vector<float>> amount;
    ofParameter<vector<float>> output;
};

#endif /* vectorModulator_hpp */
