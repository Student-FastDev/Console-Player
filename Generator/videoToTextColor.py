import numpy as np
import cv2
import pickle
import sys

aspectRatio = 16 / 9
widthSize = 80
heightSize = int(widthSize / (2 * aspectRatio))
charSet = " ,(S#g@@g#S(, "

def setColor(bgColor, fgColor):
    # Ustawia kolor tla i koloru tekstu na podstawie podanych wartości
    return "\u001b[48;5;%s;38;5;%sm" % (bgColor, fgColor)

blackColor = setColor(16, 16)

lerpedData = pickle.load(open("color.pkl", "rb"))
lookupTable = np.load("LUT.npy")

def convertImage(image):
    # Konwertuje obrazek na dane ASCII z kolorami
    frameData = []
    
    for row in image:
        lineData = ""
        for color in row:
            color = np.round(color).astype(int)
            blue, green, red = color[0], color[1], color[2]
            
            idx = lookupTable[blue, green, red]
            bgColor, fgColor, lerpValue, rgbData = lerpedData[idx]
            char = charSet[lerpValue]
            
            lineData += f"{setColor(bgColor, fgColor)}{char}"
        
        lineData += blackColor + "\\n"
        frameData.append(lineData)
    
    return frameData

if len(sys.argv) == 2:
    # Otwiera plik wideo i przetwarza klatki na dane ASCII
    videoCapture = cv2.VideoCapture(sys.argv[1])
    frameCollection = []
    frameCounter = 0

    while videoCapture.isOpened():
        ret, frame = videoCapture.read()
        if frame is None:
            break

        print(f"Processing frame {frameCounter}")
        
        resizedImage = cv2.resize(frame, (widthSize, heightSize))
        asciiFrame = convertImage(resizedImage)
        frameCollection.append(asciiFrame)

        frameCounter += 1
    
    videoCapture.release()

    # Zapisuje przetworzone klatki do pliku nagłówkowego
    with open("data.h", "w") as file:
        file.write("#ifndef DATA_H\n")
        file.write("#define DATA_H\n\n")
        file.write(f"const int heightSize = {heightSize};\n")
        file.write(f"const char *frames[{len(frameCollection)}][{heightSize}] = {{\n")
        
        for i, frame in enumerate(frameCollection):
            file.write("    {\n")
            for line in frame:
                escapedLine = line.replace("\\", "\\\\").replace("\"", "\\\"")
                file.write(f"        \"{escapedLine}\",\n")
            file.write("    }")
            if i < len(frameCollection) - 1:
                file.write(",\n")
            else:
                file.write("\n")
        
        file.write("};\n\n")
        file.write("#endif // DATA_H\n")

else:
    print("Expected video file as argument.")
