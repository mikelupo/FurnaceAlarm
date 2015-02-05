/**
 *  FurnaceAlarmDeviceType
 *
 *  Copyright 2015 michael lupo
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License. You may obtain a copy of the License at:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 *  on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 *  for the specific language governing permissions and limitations under the License.
 *
 */
metadata {
	definition (name: "FurnaceAlarmDeviceType", namespace: "mikelupo", author: "michael lupo") {
		capability "Switch"
        
        command: "sendAlarm"
        command: "sendBackToNormal"
	}


	simulator {
		// status messages
		status "ping": "catchall: 0104 0000 01 01 0040 00 6A67 00 00 0000 0A 00 0A70696E67"
		status "hello": "catchall: 0104 0000 01 01 0040 00 0A21 00 00 0000 0A 00 0A48656c6c6f20576f726c6421"
		}

		tiles {
		
        standardTile("button", "device.relayswitch", width: 2, height: 2, canChangeIcon: true) {
			state "on", label: 'Alarm', action: "switch.off", icon: "st.switches.switch.on", 
            	backgroundColor: "#79b821"
			state "off", label:'Normal', action: "switch.on", icon:"st.switches.switch.off", 
            	backgroundColor:"#ffffff"
		}
        

		main (["button"])
		details(["button"])
	}
}


// parse events into attributes
def parse(String description) {
    log.debug "Parsing ${description}"
    def name = null
    def value = zigbee.parse(description)?.text
    log.debug "Value is ${value}"

    def result = [
            value: value,
            name: value != "ping" ? name : null
    ]
    log.debug result
    return result

}

// handle commands
def on() {
	log.debug "Executing 'on'"
	// TODO: handle 'on' command by sending the SMS/PUSH event from here.
}

def off() {
	log.debug "Executing 'off'"
	// TODO: handle 'off' command by sending the SMS/PUSH event from here.
}