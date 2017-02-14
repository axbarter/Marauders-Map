!/usr/bin/env python

import subprocess
import time
import explorerhat

occupant = ["Person 1 device","Person 2 device"]

# MAC addresses for our devices - in order of people above
address = ["XX:XX:XX:XX:XX:XX","XX:XX:XX:XX:XX:XX"]

while True:
        print("starting loop")
        output = subprocess.check_output("sudo arp-scan -l", shell=True)
        print ("starting scan")
        for i in range (len(address)):
                if address[i] in output:
                        print address[i]
                        print occupant[i]

                if "XX:XX:XX:XX:XX:XX:XX"  in output:    #Person 1 MAC address
                        explorerhat.output[0].on()

                else:
                        explorerhat.output[0].off()


                if "XX:XX:XX:XX:XX:XX:XX"  in output:     #Person 2 MAC address
                        explorerhat.output[1].on()

                else:
                        explorerhat.output[1].off()
        time.sleep(60)