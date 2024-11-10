// Function to smoothly transition background color based on sensor value
function getSensorBoxHue(value) {
    // Calculate the HSL value for smooth color transition
    let hue = 120;  // Default for green (HSL: green is 120 degrees)
    
    if (value > 30 && value <= 65) {
        // Transition from green to yellow to red
        hue = 120 - (value - 30) * 3; // Reducing the hue from 120 (green) to 0 (red)
    } 
    else if (value > 65) {
        hue = 0; // Red (0 degrees in the hue spectrum)
    }

    // Set the saturation and lightness for better smoothness
    let saturation = 50;  // Full saturation (vivid colors)
    let lightness = 50;    // Medium lightness (balanced brightness)

    // Convert HSL to RGB and apply it as the background color
    // $('#sensor_card').css('border-color', `hsl(${hue}, ${saturation}%, ${lightness}%)`);
    return `hsl(${hue}, ${saturation}%, ${lightness}%)`;
}

function setupSensorsElements(sensor_array) {
    // For each sensor, add color, and values from passed array
    for (let i = 0; i < sensor_array.length; i++) {
        sensor_json = sensor_array[i]

        // Reference the sensor card in html
        sensor_card = $(`#sensor_card${i}`)

        // Update Titles
        sensor_card.find('.card-title').text(`${sensor_json['name']}`)

        // Update Values
        sensor_card.find('#humidity').text(`Humidity: ${sensor_json['humidity']}`)

        // Get values and calculate colors to update fields
        humidity_color = getSensorBoxHue(`${sensor_array[i]['humidity']}`)

        // Update colors
        sensor_card.css('background-color', humidity_color)
    }

}

// function fetchData() {
//     fetch('http://127.0.0.1:5000/refresh_values_')  // Flask server URL
//         .then(response => response.json())   // Parse JSON response
//         .then(data => {
//             setupSensorsElements(data);
//         })
//         .catch(error => console.error('Error:', error));
//     }


