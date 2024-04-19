using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Web;
using System.Windows.Forms;
using MQTTnet;
using MQTTnet.Client;
using MQTTnet.Packets;
using Newtonsoft.Json;


namespace mqtt_client
{
    public partial class MainForm : Form
    {
        private IMqttClient mqttClient;
        private string broker = "broker.hivemq.com";
        private string valueTopic = "cl21/2/nhom2/dht/value";
        private string detectTopic = "cl21/2/nhom2/dht/detected";

        public class SensorData
        {
            public double temperature { get; set; }
            public double humidity { get; set; }
        }

        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
         
        }

        private async void connectBtn_Click(object sender, EventArgs e)
        {
            if(brokerTB.Text.Length == 0)
            {
                MessageBox.Show("Bruh, you need to enter the broker's URL");
                return;
            }
            if(subscribeTB.Text.Length == 0)
            {
                MessageBox.Show("Bruh, you need to enter the topic that you want to subscribe to");
                return;
            }
            if (publishTB.Text.Length == 0)
            {
                MessageBox.Show("Bruh, you need to enter the topic that you want to publish to");
                return;
            }

            await ConnectToBroker();

            broker = brokerTB.Text;
            valueTopic = subscribeTB.Text;
            detectTopic = publishTB.Text;

            await Subscribe();
        }

        private async Task ConnectToBroker()
        {
            try
            {
                mqttClient = new MqttFactory().CreateMqttClient();

                var options = new MqttClientOptionsBuilder()
                    .WithTcpServer(broker)
                    .Build();

                // Setup message handling before connecting so that queued messages
                // are also handled properly. When there is no event handler attached all
                // received messages get lost.
                mqttClient.ApplicationMessageReceivedAsync += e =>
                {
                    Console.WriteLine($"Received message on topic '{e.ApplicationMessage.Topic}': {Encoding.UTF8.GetString(e.ApplicationMessage.Payload)}");
                    return Task.CompletedTask;
                };

                await mqttClient.ConnectAsync(options);

                MessageBox.Show("Connected to MQTT broker!");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Connection error: " + ex.Message);
            }
        }

        private async Task Subscribe()
        {
            if (mqttClient == null || !mqttClient.IsConnected)
            {
                MessageBox.Show("Please connect to the broker first!");
                return;
            }

            try
            {
                var mqttSubscribeOptions = new MqttFactory().CreateSubscribeOptionsBuilder()
                    .WithTopicFilter(
                        f =>
                        {
                            f.WithTopic(valueTopic);
                        }
                    ).Build();
                await mqttClient.SubscribeAsync(mqttSubscribeOptions, CancellationToken.None);
                Console.WriteLine("MQTT client subscribed to topic.");

                // Add task for receiving messages
                mqttClient.ApplicationMessageReceivedAsync += OnMessageReceived;

            }
            catch (Exception ex)
            {
                MessageBox.Show("Subscription error: " + ex.Message);
            }
        }

        private async Task Publish(string payload)
        {
            if (mqttClient == null || !mqttClient.IsConnected)
            {
                MessageBox.Show("Please connect to the broker first!");
                return;
            }

            try
            {
                var msg = new MqttApplicationMessageBuilder()
                    .WithTopic(detectTopic)
                    .WithPayload(payload)
                    .Build();

                await mqttClient.PublishAsync(msg, CancellationToken.None);
                Console.WriteLine("MQTT application message is published.");
                await OnMessagePublished(payload);

            }
            catch (Exception ex)
            {
                MessageBox.Show("Subscription error: " + ex.Message);
            }
        }

        private Task OnMessagePublished(string payload)
        {
            string message = payload;
            // Update textbox on the UI thread to avoid cross-threading issues
            if (pubNotiTB.InvokeRequired)
            {
                pubNotiTB.Invoke(new Action<string>(updatePubNotiTB), message);
            }
            else
            {
                updatePubNotiTB(message);
            }
            return Task.CompletedTask;
        }

        private async Task OnMessageReceived(MqttApplicationMessageReceivedEventArgs e)
        {
            string jsonString = Encoding.UTF8.GetString(e.ApplicationMessage.Payload);
            string message = "";
            double temperature = 25;
            double humidity = 40;
            bool alarm = false;

            try
            {
                SensorData data = JsonConvert.DeserializeObject<SensorData>(jsonString);
                temperature = data.temperature;
                humidity = data.humidity;
                message = "Temperate: " + temperature + ", Humidity: " + humidity + "\n";

                //Check values for anomaly
                if(temperature < 25 || temperature > 27 || humidity < 40 || humidity > 70)
                {
                    alarm = true;
                }
            }
            catch (JsonException ex)
            {
                // Handle JSON deserialization errors (e.g., invalid format)
                Console.WriteLine("Error deserializing JSON: " + ex.Message);
            }

            // Update textbox on the UI thread to avoid cross-threading issues
            if (subRcvTB.InvokeRequired)
            {
                subRcvTB.Invoke(new Action<string>(updateSubRcvTB), message);
            }
            else
            {
                updateSubRcvTB(message);
            }

            if(alarm)
            {
                await Publish("1");
            }
            else
            {
                await Publish("0");
            }
        }

        private void updateSubRcvTB(string msg)
        {
            subRcvTB.Text += msg + System.Environment.NewLine;
        }

        private void updatePubNotiTB(string msg)
        {
            pubNotiTB.Text += msg + System.Environment.NewLine;
        }

        private void brokerTB_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
