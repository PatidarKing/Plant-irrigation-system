<?php
$conn = new mysqli("localhost", "root", "", "irrigation");
$result = $conn->query("SELECT * FROM sensor_data ORDER BY id DESC LIMIT 1");
$row = $result->fetch_assoc();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Smart Irrigation Dashboard</title>
</head>
<body>
    <h2>Latest Sensor Data</h2>
    <ul>
        <li>Moisture: <?php echo $row['moisture']; ?></li>
        <li>pH Value: <?php echo $row['ph']; ?></li>
        <li>Temperature: <?php echo $row['temperature']; ?> °C</li>
        <li>Humidity: <?php echo $row['humidity']; ?> %</li>
        <li>Motor Status: <?php echo $row['motor_status'] ? "ON" : "OFF"; ?></li>
    </ul>
</body>
</html>
