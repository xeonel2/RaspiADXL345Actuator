#rsync -avz -e "ssh -p $rpiPort" pi@0.tcp.ngrok.io:/home/tempworkspace/ .tempworkspace/
scp -P 10640 -r ./publishers pi@0.tcp.ngrok.io:~/tempworkspace/
scp -P 10640 -r ./actuators pi@0.tcp.ngrok.io:~/tempworkspace/
