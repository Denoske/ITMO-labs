import time
import cv2
def video_proc():
    font = cv2.FONT_HERSHEY_SIMPLEX
    org = (50, 50)
    fontScale = 1
    color = (255, 0, 0)
    thickness = 2
    vid = cv2.VideoCapture("C:/Users/DNS/OneDrive/Рабочий стол/ДВБ Практика/ПР2/sample.mp4")
    while True:
        ret, frame = vid.read()
        if not ret:
            break
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray = cv2.GaussianBlur(gray,(7,7), 0)
        ret, thresh = cv2.threshold(gray, 105 , 255 ,cv2.THRESH_BINARY_INV)
        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
        if len(contours) >0:
            c = max(contours, key= cv2.contourArea)
            x,y,w,h = cv2.boundingRect(c)
            cv2.rectangle(frame,(x,y), (x+w,y+h),(0,0,255),2)
            cv2.putText(frame,str(x)+","+str(y),org,font,fontScale,color,thickness,cv2.LINE_AA)
        cv2.imshow('vid',frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        time.sleep(0.1)
    vid.release()
video_proc()
cv2.waitKey(0)
cv2.destroyAllWindows()
