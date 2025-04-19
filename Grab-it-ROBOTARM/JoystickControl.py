import pygame
import serial
import time

# Initialize Serial Communication with Arduino
arduino = serial.Serial('COM3', 115200, timeout=0.1) 

# Initialize pygame and the PS4 controller
pygame.init()
pygame.joystick.init()

if pygame.joystick.get_count() == 0:
    print("No controller found.")
    exit()

controller = pygame.joystick.Joystick(0)
controller.init()

# Servo movement variables
claw_rotation = 0
claw_updown = 0
claw_movement = 0
bottom_elbow = 0
middle_elbow = 0
base_rotation = 0

def get_axis_scaled(axis, deadzone=0.1, scale=3):
    value = controller.get_axis(axis)
    if abs(value) < deadzone:
        return 0
    return int(value * scale)

def map_base_rotation(value):
    # Map the input range (-3 to 3) to a symmetric range (-3 to 3)
    if value < 0:
        return int(value * 1.2)  # Scale negative values slightly
    else:
        return int(value * 1.5)  # Scale positive values slightly

while True:
    pygame.event.pump()

    # Read button inputs
    btn_square = controller.get_button(0)  # Square (claw rotate left)
    btn_circle = controller.get_button(2)  # Circle (claw rotate right)
    btn_triangle = controller.get_button(3)  # Triangle (claw up)
    btn_cross = controller.get_button(1)  # Cross (claw down)

    # Read trigger inputs (R2, L2)
    l2_trigger = (controller.get_axis(4) + 1) / 2  # Normalize L2 to 0.0 to 1.0
    r2_trigger = (controller.get_axis(5) + 1) / 2  # Normalize R2 to 0.0 to 1.0

    # Claw Rotation (Square/Circle)
    claw_rotation = -3 if btn_square else (3 if btn_circle else 0)

    # Claw Up/Down (Triangle/Cross)
    claw_updown = -2 if btn_triangle else (2 if btn_cross else 0)

    # Claw Open/Close (L2/R2 Triggers)
    if r2_trigger > 0.1:
        claw_movement = -2  # Close claw
    elif l2_trigger > 0.1:
        claw_movement = 2   # Open claw
    else:
        claw_movement = 0   # Maintain position

    # Base Rotation (Right Joystick X-Axis)
    base_rotation = get_axis_scaled(2)

    # Arm Joints (Joysticks)
    bottom_elbow = get_axis_scaled(1)   # Left Stick Y (Bottom Elbow)
    middle_elbow = get_axis_scaled(3)   # Right Stick Y (Middle Elbow)

    # Send data to Arduino
    data = f"{claw_rotation},{claw_updown},{claw_movement},{bottom_elbow},{middle_elbow},{base_rotation}\n"
    arduino.write(data.encode())

    time.sleep(0.05)
