$arduinoPort = "COM3"

while ($true) {
    $currentTime = Get-Date -Format "dd/MM/yyyy - HH:mm"

    # Create a new SerialPort object
    $serialPort = New-Object System.IO.Ports.SerialPort
    $serialPort.PortName = $arduinoPort
    $serialPort.BaudRate = 9600

    $serialPort.Open()

    $serialPort.WriteLine("$currentTime")

    $serialPort.Close()

    Start-Sleep -Seconds 1
}