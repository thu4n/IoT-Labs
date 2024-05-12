import C_CHT
import time
from tb_device_mqtt import TBDeviceMqttClient, TBPublishInfo

while True:

    data = C_DHT.readSensorDHT11(0);
    # data = {temperature, NULL, humidity, NULL}
    telemetry = {"temperature": data[0], "humidity": data[2]}
    client = TBDeviceMqttClient("THINKBOARD-SERVER", "THINKBOARD-TOKEN") 
    # Connect to ThingsBoard
    client.connect()
    # Sending telemetry without checking the delivery status 
    client.send_telemetry(telemetry)
    # Sending telemetry and checking the delivery status (QoS = 1 by default) 
    result = client.send_telemetry(telemetry)
    # get is a blocking call that awaits delivery status 
    success = result.get() = TBPublishInfo.TB_ERR_SUCCESS 
    # Disconnect from ThingsBoard
    client.disconnect() time.sleep(1)