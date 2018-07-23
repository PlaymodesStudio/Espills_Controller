//
//  movingheadController.cpp
//  Espills_controller
//
//  Created by Eduard Frigola Bagué on 02/07/2018.
//

#include "movingheadController.h"

movingheadController::movingheadController() : ofxOceanodeNodeModel("Movinghead Controller"){
    parameters->add(pan.set("Pan", {0}, {0}, {1}));
    parameters->add(tilt.set("Tilt", {0}, {0}, {1}));
    addOutputParameterToGroupAndInfo(output.set("Output", {0}, {0}, {1}));
}

void movingheadController::update(ofEventArgs &a){
    vector<float> tempOutput;
    int maxSize = max(pan.get().size(), tilt.get().size());
    tempOutput.resize(9*maxSize, 0);
//    tempOutput.resize(14*maxSize, 0);
    
    for(int i = 0; i < maxSize; i++){
        int index = i*9;
        if(pan.get().size() > i){
            tempOutput[index] = pan.get()[i];
            tempOutput[index+2] = pan.get()[i]*255 - int(pan.get()[i]*255);
        }
        if(tilt.get().size() > i){
            tempOutput[index+1] = tilt.get()[i];
            tempOutput[index+3] = tilt.get()[i]*255 - int(tilt.get()[i]*255);
        }
//        int index = i*14;
//        if(pan.get().size() > i){
//            tempOutput[index] = pan.get()[i];
//            tempOutput[index+1] = pan.get()[i]*255 - int(pan.get()[i]*255);
//        }
//        if(tilt.get().size() > i){
//            tempOutput[index+2] = tilt.get()[i];
//            tempOutput[index+3] = tilt.get()[i]*255 - int(tilt.get()[i]*255);
//        }
    }
    
    output = tempOutput;
}
