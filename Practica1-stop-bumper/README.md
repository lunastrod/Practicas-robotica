# stop-bumper

el comando para mover el robot
rostopic pub -r 5 /mobile_base/commands/velocity geometry_msgs/Twist "linear:
  x: 0.3
  y: 0.0
  z: 0.0

el comando para escuchar el bumper
rostopic echo /mobile_base/events/bumper

Objetivo: hacer que el robot se pare cuando se haya pulsado el bumper




COMANDOS DE PRUEBA
simular eventos de bumper
rostopic pub mobile_base/events/bumper kobuki_msgs/BumperEvent

leer el topic del motor
rostopic echo /mobile_base/commands/velocity

COMANDOS PARA CONECTARSE AL KOBUKI (creo)
sudo apt-get install ros-melodic-kobuki-ftdi
rosrun kobuki_ftdi create_udev_rules