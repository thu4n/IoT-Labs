package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
)

type SensorData struct {
	Error   bool   `json:"error"`
	Message string `json:"message,omitempty"`
	Data    struct {
		Distance float64 `json:"distance"`
		Light    float64 `json:"light"`
	} `json:"data"`
}

func helloHandler(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusOK)
	w.Write([]byte("Hello, world!"))
}

func postHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		// Handle non-POST requests (e.g., return an error)
		w.WriteHeader(http.StatusMethodNotAllowed)
		w.Write([]byte("Method not allowed"))
		return
	}

	// Read the request body
	defer r.Body.Close()
	body, err := io.ReadAll(r.Body)
	if err != nil {
		// Handle error reading request body
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte("Error reading request body"))
		return
	}

	// Process the received data in the body (e.g., parse JSON)
	fmt.Printf("Received data in POST request: %s\n", string(body))

	// Send a response message
	w.WriteHeader(http.StatusOK)
	w.Write([]byte("POST request received!"))
}

func postSensorData(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		// Handle non-POST requests (e.g., return an error)
		w.WriteHeader(http.StatusMethodNotAllowed)
		w.Write([]byte("Method not allowed"))
		return
	}
	defer r.Body.Close()
	body, err := io.ReadAll(r.Body)
	if err != nil {
		// Handle error reading request body
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte("Error reading request body"))
		return
	}
	var sensorData SensorData
	err = json.Unmarshal(body, &sensorData)
	if err != nil {
		// Handle error unmarshalling JSON (optional)
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte("Error parsing JSON data"))
		return
	}

	// check light sensor value
	lightsOn := 0
	if sensorData.Data.Light < 100 {
		lightsOn = 3
	} else if sensorData.Data.Light < 300 {
		lightsOn = 2
	} else if sensorData.Data.Light < 500 {
		lightsOn = 1
	}

	// check distance senor value
	if sensorData.Data.Distance > 6 {
		lightsOn = 0
	}

	fmt.Printf("Received data in POST request: Distance: %.2f, Light: %.2f\n", sensorData.Data.Distance, sensorData.Data.Light)

	responseData := struct {
		LightsOn int `json:"lightsOn"`
	}{
		LightsOn: lightsOn,
	}
	responseJson, _ := json.Marshal(responseData)
	w.WriteHeader(http.StatusOK)
	w.Write(responseJson)
}

func main() {
	http.HandleFunc("/", helloHandler)
	http.HandleFunc("/post", postHandler)
	http.HandleFunc("/sensor", postSensorData)
	fmt.Println("Server listening on port 8080...")
	http.ListenAndServe(":8080", nil)
}
