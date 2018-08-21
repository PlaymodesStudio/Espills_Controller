//
//  strobeLightController.cpp
//  Espills_controller
//
//  Created by Eduard Frigola on 14/08/2018.
//

#include "strobeLightController.h"

void strobeLightController::setup(){
    parameters->add(fader.set("Fader", 0, 0, 1));
    parameters->add(red.set("Red", 1, 0, 1));
    parameters->add(green.set("Green", 1, 0, 1));
    parameters->add(strobeRate.set("Strobe Rate", 0, 0, 1));
    parameters->add(strobeWidth.set("Pulse Width", 1, 0, 1));
    
    
}
