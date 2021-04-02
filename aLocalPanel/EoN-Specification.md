# EoN - specifications:
#### 1. EoN (Edge of Network) which is installed with fire sensor (fire), solenoid valve, push button, LED for protection purposes.
#### 2. The function of the solenoid valve (as an actuator) to open fire extinguisher media (water, powder, foam, etc.) in this system using pressurized water (so that it is capable of spraying).
#### 3. Sensor provides measurement data to EoN (who in turn acts as controller) if the value exceeds the parameter setting, will give an alarm.
#### 4. This controller can work automatically, manual-local, manual-remote.
#### 5. If an alarm occurs (there is a fire) and the controller works automatically, the actuator works by activating the solenoid valve to drain the extinguisher medium (pressurized water).
#### 6. If the controller operates manually-locally, the actuator works according to the status of the push buttons.
#### 7. If the controller works manually-remote, the actuator works according to the command given from the remote (local panel or via the internet).
#### 8. Installation of sensors, solenoid valve, push button and LED using hard-wire.
#### 9. Communication with the server uses wireless (WIFI / Wireless) with the MQTT (Message Queuing Telemetry Transport) protocol.

## [EoN - Hardware](https://github.com/slametsampon/WFPS/blob/main/EoN/images/EoN-HW.jpg)

## [EoN - Software](https://github.com/slametsampon/WFPS/blob/main/EoN/images/EoN_ClassDiagram.jpg)
## It is part of [WFPS - Wireless Fire Protection System](https://github.com/slametsampon/WFPS)