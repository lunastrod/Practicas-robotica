# stop-bumper

el comando para mover el robot
rostopic pub -r 5 /mobile_base/commands/velocity geometry_msgs/Twist "linear:
  x: 0.3
  y: 0.0
  z: 0.0

cambios de D2

el comando para escuchar el bumper
rostopic echo /mobile_base/events/bumper


Objetivo: hacer que el robot se pare cuando se haya pulsado el bumper
