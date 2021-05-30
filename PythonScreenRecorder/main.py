import cv2, numpy, pyautogui, keyboard
filename = "record"
SCREEN_SIZE = (1920, 1080)
vid = cv2.VideoWriter(filename + ".mp4", cv2.VideoWriter_fourcc(*'MP4V'), 20.0, SCREEN_SIZE)

print("Starte Aufnahme")

while True:
    img = pyautogui.screenshot()
    numpy_frame = numpy.array(img)
    frame = cv2.cvtColor(numpy_frame, cv2.COLOR_BGR2RGB)
    vid.write(frame)
    if keyboard.is_pressed('x'):
        print("Stoppe Aufnahme")
        break

cv2.destroyAllWindows()
vid.release()