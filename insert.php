<?php
$conn = new mysqli("localhost", "root", "", "irrigation");

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $moisture = $_POST["moisture"];
    $ph = $_POST["ph"];
    $temp = $_POST["temp"];
    $humidity = $_POST["humidity"];
    $motor = $_POST["motor"];

    $stmt = $conn->prepare("INSERT INTO sensor_data (moisture, ph, temperature, humidity, motor_status) VALUES (?, ?, ?, ?, ?)");
    $stmt->bind_param("iiiii", $moisture, $ph, $temp, $humidity, $motor);
    $stmt->execute();
    echo "Data stored";
}
?>
