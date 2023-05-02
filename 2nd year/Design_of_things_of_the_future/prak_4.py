import json, pyttsx3, vosk, pyaudio, requests

tts = pyttsx3.init()
voices = tts.getProperty('voices')
tts.setProperty('voices', 'en')

for voice in voices:
    if voice.name == 'Microsoft David Desktop - English (United States)':
        tts.setProperty('voice', voice.id)
        
model = vosk.Model(r"C:\vosk-model-small-ru-0.4")
record = vosk.KaldiRecognizer(model, 16000) 
pa = pyaudio.PyAudio()
stream = pa.open(
    format=pyaudio.paInt16, 
    channels=1, 
    rate=16000, 
    input=True, 
    frames_per_buffer=8000) 
stream.start_stream()
 
def listen():
    while True:
        data = stream.read(4000, exception_on_overflow=False) 
        if record.AcceptWaveform(data) and len(data) > 0:
            answer = json.loads(record.Result()) 
            if answer['text']:
                yield answer['text']

def speak(say): 
    tts.say(say) 
    tts.runAndWait()
    
f = open('result.txt','w')
print('start') 
pwd = ''
for text in listen():
    if text == 'выйти': 
        f.close()
        quit()
       
    elif text == 'факт':
        req = requests.get("http://numbersapi.com/random/math")
        data = req.text
        print(data, end = '\n')
        speak(data)
        pwd = data + '\n'
        
    elif text == 'шутка':
            req = requests.get('https://v2.jokeapi.dev/joke/Any?type=single&safe-mode')
            data = req.json()
            joke = data['joke']
            print(joke,'\n')
            speak(joke)
            pwd = joke + "\n"
            
    elif text == 'анекдот':
            req = requests.get('https://v2.jokeapi.dev/joke/Any?type=twopart&safe-mode')
            data = req.json()
            setup = data['setup']
            delivery = data['delivery']
            print(setup, '\n')
            speak(setup)
            print(delivery,'\n')
            speak(delivery)
            pwd = setup + "\n"  + delivery + "\n"
            
    elif text == 'сохранить': 
        if pwd:
            f.write(pwd)
            print('Recorded', end='\n')
            speak('recorded')

        else:
            print('Nothing to record')
            speak('nothing to record')

    else:
        print(text)
